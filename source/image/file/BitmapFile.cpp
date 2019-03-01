#include <yatools/image/file/yatools.image.file.bitmapfile.h>
#include <string.h>


namespace yatools { namespace image { namespace file {


//-------------------------------------
// ファイルヘッダ取得
//
BmpHeader* BmpFile::GetHeader( uintptr buffer, uint64 length )
{
	if( buffer != NULL )
	{
		BmpHeader* header = (BmpHeader*)buffer;
		if( header->Kind[ 0 ] == 'B' && header->Kind[ 1 ] == 'M' )
		{
			return header;
		}
	}
	return NULL;
}

//-------------------------------------
// BMP情報ヘッダ取得
//
BmpInfomationHeader* BmpFile::GetInfomationHeader( uintptr buffer, uint64 length )
{
	if( GetHeader( buffer, length ) != NULL )
	{
		return (BmpInfomationHeader*)(buffer + sizeof( BmpHeader ));
	}
	return NULL;
}

//-------------------------------------
// カラーパレット取得
//
uintptr BmpFile::GetColorPalets( uintptr buffer, uint64 length )
{
	BmpInfomationHeader* infoHeader = GetInfomationHeader( buffer, length );
	if( infoHeader != NULL )
	{
		switch( infoHeader->BitDepth )
		{
		case 1: case 4: case 8:
			return buffer + sizeof( BmpHeader ) + sizeof( BmpInfomationHeader );
		}
	}
	return NULL;
}

//-------------------------------------
// 画像フィールド取得
//
uintptr BmpFile::GetImageField( uintptr buffer, uint64 length )
{
	BmpHeader* header = GetHeader( buffer, length );
	if( header != NULL )
	{
		return buffer + header->OffsetImage;
	}
	return NULL;
}

//-------------------------------------
// カラーバッファ取得
//
ColorBuffer* BmpFile::GetColorBuffer( uintptr buffer, uint64 length )
{
	BmpInfomationHeader* info = GetInfomationHeader( buffer, length );
	if( info != NULL && info->Compression == 0 )
	{
		if( info->BitDepth == 32 )
		{
			return GetColorBuffer32( buffer, length );
		}
		else if( info->BitDepth == 24 )
		{
			return GetColorBuffer24( buffer, length );
		}
		else if( info->BitDepth == 1 || info->BitDepth == 4 || info->BitDepth == 8 )
		{
			return GetColorBufferPalet( buffer, length );
		}
	}
	return NULL;
}

//-------------------------------------
// 32bitカラー取得
//
ColorBuffer* BmpFile::GetColorBuffer32( uintptr buffer, uint64 length )
{
	BmpInfomationHeader* info = GetInfomationHeader( buffer, length );
	uintptr image = GetImageField( buffer, length );
	uint32 width = info->Width < 0 ? -info->Width : info->Width;
	uint32 height = info->Height < 0 ? -info->Height : info->Height;
	ColorBuffer* colorBuffer = ColorBuffer::Create( ColorFormat::B8G8R8A8, width, height );
	if( colorBuffer != NULL )
	{
		if( info->BitDepth == 32 )
		{
			if( info->Width >= 0 )
			{
				if( info->Height < 0 )
				{
					memcpy( (void*)colorBuffer->GetPixelAddress( 0, 0 ), (void*)image, width * height * 4 );
				}
				else
				{
					uint64 lineSize = width * 4;
					for( uint64 y = 0; y < height; y++ )
					{
						memcpy( (void*)colorBuffer->GetPixelAddress( 0, (uint32)(height - y - 1) ), (void*)(image + (lineSize * y)), (size_t)lineSize );
					}
				}
			}
			else
			{
				for( uint64 y = 0; y < height; y++ )
				{
					for( uint64 x = 0; x < width; x++ )
					{
						if( info->Height < 0 )
						{
							colorBuffer->SetPixel( (uint32)x, (uint32)y, image + (uintptr)((x + y * width) * 4), 4 );
						}
						else
						{
							colorBuffer->SetPixel( (uint32)x, (uint32)(height - y - 1), image + (uintptr)((x + y * width) * 4), 4 );
						}
					}
				}
			}
		}
	}
	return colorBuffer;
}

//-------------------------------------
// 24bitカラー取得
//
ColorBuffer* BmpFile::GetColorBuffer24( uintptr buffer, uint64 length )
{
	BmpInfomationHeader* info = GetInfomationHeader( buffer, length );
	uintptr image = GetImageField( buffer, length );
	int width = info->Width < 0 ? -info->Width : info->Width;
	int height = info->Height < 0 ? -info->Height : info->Height;
	ColorBuffer* colorBuffer = ColorBuffer::Create( ColorFormat::B8G8R8, width, height );
	if( colorBuffer != NULL )
	{
		if( info->BitDepth == 24 )
		{
			uint64 lineSize = width * 3;
			lineSize = (lineSize % 4) == 0 ? lineSize : lineSize + (4 - (lineSize % 4));
			if( info->Width >= 0 )
			{
				for( uint64 y = 0; y < height; y++ )
				{
					if( info->Height < 0 )
					{
						colorBuffer->SetPixels( 0, (uint32)y, image + (uintptr)(y * lineSize), width * 3 );
					}
					else
					{
						colorBuffer->SetPixels( 0, (uint32)(height - y - 1), image + (uintptr)(y * lineSize), width * 3 );
					}
				}
			}
			else
			{
				for( uint64 y = 0; y < height; y++ )
				{
					for( uint64 x = 0; x < width; x++ )
					{
						if( info->Height < 0 )
						{
							colorBuffer->SetPixel( (uint32)x, (uint32)y, image + (uintptr)(x * 3 + y * lineSize), 3 );
						}
						else
						{
							colorBuffer->SetPixel( (uint32)x, (uint32)(height - y - 1), image + (uintptr)(x * 3 + y * lineSize), 3 );
						}
					}
				}
			}
		}
	}
	return colorBuffer;
}

//-------------------------------------
// パレットカラー取得
//
ColorBuffer* BmpFile::GetColorBufferPalet( uintptr buffer, uint64 length )
{
	BmpInfomationHeader* info = GetInfomationHeader( buffer, length );
	uintptr image = GetImageField( buffer, length );
	ColorB8G8R8A8* palet = (ColorB8G8R8A8*)GetColorPalets( buffer, length );
	int width = info->Width < 0 ? -info->Width : info->Width;
	int height = info->Height < 0 ? -info->Height : info->Height;
	ColorBuffer* colorBuffer = ColorBuffer::Create( ColorFormat::B8G8R8A8, width, height );
	if( colorBuffer != NULL )
	{
		if( info->BitDepth == 8 )
		{
			int lineSize = (width % 4 == 0) ? width : width + (4 - width % 4);
			for( int y = 0; y < height; y++ )
			{
				uint8* line = (uint8*)(image + (y * lineSize));
				int iy = info->Height < 0 ? y : height - y - 1;
				for( int x = 0; x < width; x++ )
				{
					int ix = info->Width >= 0 ? x : width - x - 1;
					colorBuffer->SetPixel( ix, iy, (uintptr)&palet[ line[ x ] ], 4 );
				}
			}
		}
		else if( info->BitDepth == 4 )
		{
			int hWidth = (width / 2);
			int lineSize = (hWidth % 4 == 0) ? hWidth : hWidth + (4 - hWidth % 4);
			for( int y = 0; y < height; y++ )
			{
				uint8* line = (uint8*)(image + (y * lineSize));
				int iy = info->Height < 0 ? y : height - y - 1;
				for( int x = 0; x < width; x += 2 )
				{
					int ix = info->Width >= 0 ? x : width - x - 1;
					int paletNum = line[ x / 2 ] & 0x0f;
					colorBuffer->SetPixel( ix, iy, (uintptr)&palet[ paletNum ], 4 );

					if( x + 1 < width )
					{
						ix = info->Width >= 0 ? x + 1 : width - x - 2;
						paletNum = (line[ x / 2 ] & 0xf0) >> 4;
						colorBuffer->SetPixel( ix, iy, (uintptr)&palet[ paletNum ], 4 );
					}
				}
			}
		}
		else if( info->BitDepth == 1 )
		{
			int hWidth = (width / 8);
			int lineSize = (hWidth % 4 == 0) ? hWidth : hWidth + (4 - hWidth % 4);
			for( int y = 0; y < height; y++ )
			{
				uint8* line = (uint8*)(image + (y * lineSize));
				int iy = info->Height < 0 ? y : height - y - 1;
				for( int x = 0; x < width; x += 8 )
				{
					for( int i = 0; i < 8; i++ )
					{
						if( x + i < width )
						{
							int ix = info->Width >= 0 ? x + i : width - x - i - 1;
							int paletNum = (line[ x / 8 ] >> i) & 0x01;
							colorBuffer->SetPixel( ix, iy, (uintptr)&palet[ paletNum ], 4 );
						}
					}
				}
			}
		}
	}
	return colorBuffer;
}


//-------------------------------------
// BMPファイル書き出し
//
uint64 BmpFile::WriteFileBuffer( ColorBuffer* colorBuffer, uintptr buffer, uint64 length )
{
	/*---- 引数チェック ----*/
	if( colorBuffer == NULL )
	{
		return 0;
	}


	/*---- カラーバッファコンバート ----*/
	ColorBuffer* originBuffer = colorBuffer;
	switch( colorBuffer->GetFormat( ) )
	{
	case ColorFormat::B8G8R8: break;
	case ColorFormat::Gray8: case ColorFormat::Gray16:
		if( (colorBuffer = colorBuffer->Convert( ColorFormat::B8G8R8 )) == NULL )
		{
			return 0;
		}
		break;
	default:
		if( (colorBuffer = colorBuffer->Convert( ColorFormat::B8G8R8 )) == NULL )
		{
			return 0;
		}
		break;
	}


	/*---- ファイルサイズ計算 ----*/
	uint64 lineSize = colorBuffer->GetWidth( ) * colorBuffer->GetPixelSize( );
	lineSize = (lineSize % 4) == 0 ? lineSize : lineSize + (4 - lineSize % 4);
	uint64 imageSize = colorBuffer->GetHeight( ) * lineSize;
	uint64 bmpsize = sizeof( BmpHeader ) + sizeof( BmpInfomationHeader ) + imageSize;


	/*---- 格納する ----*/
	if( buffer != NULL )
	{
		if( length < bmpsize )
		{
			bmpsize = 0;
		}
		else
		{
			/*-- ヘッダ部分クリア --*/
			memset( (void*)buffer, 0, sizeof( BmpHeader ) + sizeof( BmpInfomationHeader ) );


			/*-- ヘッダ設定 --*/
			BmpHeader* header = (BmpHeader*)buffer;
			header->Kind[ 0 ] = 'B'; header->Kind[ 1 ] = 'M';
			header->FileSize = (uint32)bmpsize;
			header->OffsetImage = sizeof( BmpHeader ) + sizeof( BmpInfomationHeader );


			/*-- 情報ヘッダ設定 --*/
			BmpInfomationHeader* info = (BmpInfomationHeader*)(buffer + sizeof( BmpHeader ));
			info->InfomationSize = (uint32)sizeof( BmpInfomationHeader );
			info->BitDepth = (uint16)colorBuffer->GetPixelSize( ) * 8;
			info->Width = (int32)colorBuffer->GetWidth( );
			info->Height = (int32)colorBuffer->GetHeight( );
			info->Plane = 1;
			info->SizeImage = (uint32)imageSize;


			/*-- 下から格納していく --*/
			uintptr image = buffer + header->OffsetImage;
			memset( (void*)image, 0, (size_t)imageSize );
			for( int y = 0; y < info->Height; y++ )
			{
				memcpy( (void*)(image + (y * lineSize)), (void*)colorBuffer->GetPixelAddress( 0, info->Height - (uint32)y - 1 ), (size_t)lineSize );
			}
		}
	}


	/*---- 内部でコンバートしていたら廃棄 ----*/
	if( originBuffer != colorBuffer )
	{
		colorBuffer->Release( );
	}

	return bmpsize;
}



} } }