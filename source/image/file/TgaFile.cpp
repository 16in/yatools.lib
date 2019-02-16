#include <yatools/image/file/yatools.image.file.tgafile.h>
#include <string.h>


namespace yatools { namespace image { namespace file {


//-------------------------------------
// バイナリ操作
//-------------------------------------
//-------------------------------------
// ファイルヘッダ取得
//
TgaHeader* TgaFile::GetHeader( uintptr buffer, uint64 length )
{
	if( buffer != NULL && length >= sizeof( TgaHeader ) )
	{
		return (TgaHeader*)buffer;
	}
	return NULL;
}

//-------------------------------------
// ファイルフッター取得
//
TgaFooter* TgaFile::GetFooter( uintptr buffer, uint64 length )
{
	TgaHeader* header = GetHeader( buffer, length );

	if( header == NULL )
	{
		return NULL;
	}
	if( length >= sizeof( TgaHeader ) + sizeof( TgaFooter ) )
	{
		TgaFooter* footer = (TgaFooter*)(buffer + (length - sizeof( TgaFooter )));
		if( strcmp( footer->Signature, "TRUEVISION-XFILE.\0" ) == 0 )
		{
			return footer;
		}
	}
	return NULL;
}

//-------------------------------------
// ImageIDフィールド取得
//
uintptr TgaFile::GetImageIdField( uintptr buffer, uint64 length )
{
	TgaHeader* header = GetHeader( buffer, length );
	if( header == NULL || header->IdFieldLength <= 0 )
	{
		return NULL;
	}
	return buffer + sizeof( TgaHeader );
}

//-------------------------------------
// カラーマップフィールド取得
//
uintptr TgaFile::GetColorMapField( uintptr buffer, uint64 length )
{
	TgaHeader* header = GetHeader( buffer, length );
	if( header == NULL || header->ColorMapType == 0 )
	{
		return NULL;
	}
	return (buffer + sizeof( TgaHeader ) + header->ColorMapSpecification.FirstEntryIndex);
}

//-------------------------------------
// 画像フィールド取得
//
uintptr TgaFile::GetImageField( uintptr buffer, uint64 length )
{
	TgaHeader* header = GetHeader( buffer, length );
	if( header == NULL || header->ImageType == 0 )
	{
		return NULL;
	}
	if( header->ColorMapType == 0 )
	{
		return (buffer + sizeof( TgaHeader ) + header->IdFieldLength);
	}
	return (buffer + sizeof( TgaHeader ) + header->IdFieldLength) + ((header->ColorMapSpecification.EntrySize / 8) * header->ColorMapSpecification.Length);
}

//-------------------------------------
// カラーバッファ取得
//
ColorBuffer* TgaFile::GetColorBuffer( uintptr buffer, uint64 length )
{
	TgaHeader* header = GetHeader( buffer, length );
	if( header != NULL )
	{
		ColorBuffer* colorBuffer = NULL;
		if( header->ImageType == TgaImageType::TGA_GRAY_SCALE )
		{
			if( header->ImageSpecification.PixelDepth == 8 )
			{
				colorBuffer = ColorBuffer::Create( ColorFormat::Gray8, header->ImageSpecification.Width, header->ImageSpecification.Height );
			}
			else if( header->ImageSpecification.PixelDepth == 16 )
			{
				colorBuffer = ColorBuffer::Create( ColorFormat::Gray16, header->ImageSpecification.Width, header->ImageSpecification.Height );
			}
		}
		else if( header->ImageType == TgaImageType::TGA_TRUE_COLOR )
		{
			if( header->ImageSpecification.PixelDepth == 16 )
			{
				colorBuffer = ColorBuffer::Create( ColorFormat::A1R5G5B5, header->ImageSpecification.Width, header->ImageSpecification.Height );
			}
			else if( header->ImageSpecification.PixelDepth == 24 )
			{
				colorBuffer = ColorBuffer::Create( ColorFormat::R8G8B8, header->ImageSpecification.Width, header->ImageSpecification.Height );
			}
			else
			{
				colorBuffer = ColorBuffer::Create( ColorFormat::A8R8G8B8, header->ImageSpecification.Width, header->ImageSpecification.Height );
			}
		}
		if( colorBuffer != NULL )
		{
			uint64 pixelSize = header->ImageSpecification.PixelDepth / 8;
			if( header->ImageSpecification.Descriptor.Direction == TGA_IMAGE_LEFT_TOP )
			{
				colorBuffer->SetPixels( 0, 0, GetImageField( buffer, length ), header->ImageSpecification.Width * header->ImageSpecification.Height * pixelSize );
			}
			else if( header->ImageSpecification.Descriptor.Direction == TGA_IMAGE_LEFT_BOTTOM )
			{
				uintptr pixels = GetImageField( buffer, length );
				for( uint32 y = 0; y < header->ImageSpecification.Height; y++ )
				{
					colorBuffer->SetPixels( 0, header->ImageSpecification.Height - y - 1, pixels + (y * header->ImageSpecification.Width * pixelSize), header->ImageSpecification.Width * pixelSize );
				}
			}
			else if( header->ImageSpecification.Descriptor.Direction == TGA_IMAGE_RIGHT_TOP )
			{
				uintptr pixels = GetImageField( buffer, length );
				for( uint32 y = 0; y < header->ImageSpecification.Height; y++ )
				{
					for( uint32 x = 0; x < header->ImageSpecification.Width; x++ )
					{
						colorBuffer->SetPixels( x, y, pixels + (x + y * header->ImageSpecification.Width) * pixelSize, pixelSize );
					}
				}
			}
			else if( header->ImageSpecification.Descriptor.Direction == TGA_IMAGE_RIGHT_BOTTOM )
			{
				uintptr pixels = GetImageField( buffer, length );
				for( uint32 y = 0; y < header->ImageSpecification.Height; y++ )
				{
					for( uint32 x = 0; x < header->ImageSpecification.Width; x++ )
					{
						colorBuffer->SetPixels( x, header->ImageSpecification.Height - y - 1, pixels + (x + y * header->ImageSpecification.Width) * pixelSize, pixelSize );
					}
				}
			}
			return colorBuffer;
		}
	}
	return NULL;
}

//-------------------------------------
// 拡張情報フィールド取得
//
TgaExtension* TgaFile::GetExtensionField( uintptr buffer, uint64 length )
{
	TgaFooter* footer = GetFooter( buffer, length );
	if( footer != NULL && footer->ExtensionOffset > 0 )
	{
		return (TgaExtension*)(buffer + footer->ExtensionOffset);
	}
	return NULL;
}

//-------------------------------------
// 開発者領域フィールド取得
//
uintptr TgaFile::GetDeveloperAreaField( uintptr buffer, uint64 length )
{
	TgaFooter* footer = GetFooter( buffer, length );
	if( footer != NULL && footer->DeveloperAreaOffset > 0 )
	{
		return (buffer + footer->DeveloperAreaOffset);
	}
	return NULL;
}

//-------------------------------------
// TGAファイル書き出し
//
uint64 TgaFile::WriteFileBuffer( ColorBuffer* colorBuffer, uintptr buffer, uint64 length )
{
	uint64 size = 0;
	if( colorBuffer != NULL )
	{
		/*---- 諸情報取得 ----*/
		ColorFormat format = colorBuffer->GetFormat( );
		uint32 width = colorBuffer->GetWidth( ), height = colorBuffer->GetHeight( );
		uint64 pixelSize = GetColorFormatPixelSize( format );


		/*---- ファイルサイズ求める ----*/
		size = sizeof( TgaHeader );
		size += sizeof( TgaFooter );
		size += pixelSize * width * height;
		

		/*---- バッファに格納していく ----*/
		if( buffer != NULL )
		{
			if( length < size )
			{
				return 0;
			}

			// ヘッダ生成
			TgaHeader* header = (TgaHeader*)buffer;
			memset( header, 0, sizeof( TgaHeader ) );
			header->ImageType = (format == ColorFormat::Gray8) ? TGA_GRAY_SCALE : TGA_TRUE_COLOR;
			header->ImageSpecification.Width = width;
			header->ImageSpecification.Height = height;
			header->ImageSpecification.PixelDepth = pixelSize * 8;
			header->ImageSpecification.Descriptor.Direction = TGA_IMAGE_LEFT_TOP;
			
			// フォーマットチェック
			memcpy( (void*)GetImageField( buffer, length ), (void*)colorBuffer->GetPixelAddress( 0, 0 ), pixelSize * width * height );

			// フッター付与
			TgaFooter* footer = (TgaFooter*)(buffer + size - sizeof( TgaFooter ));
			strcpy( footer->Signature, "TRUEVISION-XFILE." );
		}
	}
	return size;
}


} } }
