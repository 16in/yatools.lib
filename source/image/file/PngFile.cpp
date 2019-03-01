#include <yatools/image/file/yatools.image.file.pngfile.h>
#include <png.h>
#include <string.h>


namespace yatools {	namespace image { namespace file {


/**
* @brief PNGファイル情報取得
* @param[int,out] infomation		PNGファイル情報格納先
* @param[in] buffer					PNGファイルが格納済みのメモリ領域
* @param[in] length					bufferサイズ
* @retval true						取得に成功
* @retval false						取得に失敗
* @details
*	メモリ上に展開されているPNGファイルの情報を取得します。
*/
bool PngFile::GetInfomation( PngInfomation* infomation, uintptr buffer, uint64 length )
{
	/*---- 引数チェック ----*/
	if( infomation == NULL || buffer == NULL )
	{
		return false;
	}

	/*---- ヘッダ部分だけ読み取る ----*/
	png_image image;
	if( !OpenReadPngOnMemory( (uintptr)&image, buffer, length ) )
	{
		return false;
	}


	/*---- 情報コピー ----*/
	SetupInfomation( infomation, (uintptr)&image );


	// ヘッダ内容だけだけど一応開放
	png_image_free( &image );

	return true;
}

//-------------------------------------
// カラーバッファ取得
//
ColorBuffer* PngFile::GetColorBuffer( uintptr buffer, uint64 length )
{
	/*---- 引数チェック ----*/
	if( buffer == NULL )
	{
		return false;
	}


	/*---- ヘッダ部分読み取り ----*/
	png_image image;
	if( !OpenReadPngOnMemory( (uintptr)&image, buffer, length ) )
	{
		return false;
	}


	/*---- 情報コピー ----*/
	PngInfomation infomation;
	SetupInfomation( &infomation, (uintptr)&image );


	/*---- カラーバッファ生成 ----*/
	ColorBuffer* colorBuffer = NULL;
	if( infomation.ColorFormat != ColorFormat::Unknown )
	{
		colorBuffer = ColorBuffer::Create( infomation.ColorFormat, infomation.Width, infomation.Height );
		uint32 stride = PNG_IMAGE_ROW_STRIDE( image );
		uint64 bufferSize = PNG_IMAGE_BUFFER_SIZE( image, stride );
		if( infomation.ColorFormat == Gray16 || !(infomation.Format & (PNG_FORMAT_FLAG_COLORMAP | PNG_FORMAT_FLAG_LINEAR)) )
		{
			if( infomation.Format != PNG_FORMAT_AG && infomation.Format != PNG_FORMAT_GA )
			{
				png_image_finish_read( &image, NULL, (void*)colorBuffer->GetPixelAddress( 0, 0 ), stride, NULL );
			}
			else
			{
				uint8* cbuffer = new uint8[ bufferSize ];
				png_image_finish_read( &image, NULL, cbuffer, stride, NULL );
				for( uint32 y = 0; y < infomation.Height; y++ )
				{
					for( uint32 x = 0; x < infomation.Width; x++ )
					{
						uint64 index = x + (y * infomation.Width);
						ColorA8R8G8B8 color;
						if( infomation.Format == PNG_FORMAT_AG )
						{
							color.Alpha = cbuffer[ index ];
							color.Red = color.Green = color.Blue = cbuffer[ index + 1 ];
						}
						else if( infomation.Format == PNG_FORMAT_GA )
						{
							color.Red = color.Green = color.Blue = cbuffer[ index ];
							color.Alpha = cbuffer[ index + 1 ];
						}
						colorBuffer->SetPixels( x, y, (uintptr)&color, sizeof( color ) );
					}
				}
				delete[] cbuffer;
			}
		}
		else if( infomation.Format & (PNG_FORMAT_FLAG_COLORMAP) )
		{
			uint8* indexBuffer = new uint8[ bufferSize ];
			uint8* colorMap = new uint8[ PNG_IMAGE_COLORMAP_SIZE( image ) ];
			uint32 sampleSize = PNG_IMAGE_SAMPLE_SIZE( image.format );
			png_image_finish_read( &image, NULL, indexBuffer, stride, colorMap );
			for( uint32 y = 0; y < infomation.Height; y++ )
			{
				for( uint32 x = 0; x < infomation.Width; x++ )
				{
					colorBuffer->SetPixels( x, y, (uintptr)(&colorMap[ sampleSize * indexBuffer[ x + (y * infomation.Width) ] ]), sampleSize );
				}
			}
			delete[] indexBuffer;
			delete[] colorMap;
		}
		else if( infomation.Format & (PNG_FORMAT_FLAG_LINEAR) )
		{
			uint8* cbuffer = new uint8[ bufferSize ];
			uint16* c16buffer = (uint16*)cbuffer;
			png_image_finish_read( &image, NULL, cbuffer, stride, NULL );
			uint32 sampleSize = PNG_IMAGE_SAMPLE_SIZE( image.format );

			uint16 a = 1, r = 0, g = 0, b = 0;
			double scale = 1.0 / (double)UINT16_MAX;
			for( uint32 y = 0; y < infomation.Height; y++ )
			{
				for( uint32 x = 0; x < infomation.Width; x++ )
				{
					uint64 index = x + (y * infomation.Width);
					if( image.format == PNG_FORMAT_LINEAR_Y_ALPHA )
					{
						index *= 2;
						r = g = b = c16buffer[ index ];
						a = c16buffer[ index + 1 ];
						colorBuffer->SetPixelColor( x, y, r * scale, g * scale, b * scale, a * scale );
					}
					else
					{
						if( image.format == PNG_FORMAT_LINEAR_RGB )
						{
							index *= 3;
							r = c16buffer[ index ];
							g = c16buffer[ index + 1 ];
							b = c16buffer[ index + 2 ];
						}
						else if( image.format == PNG_FORMAT_LINEAR_RGB_ALPHA )
						{
							index *= 4;
							r = c16buffer[ index ];
							g = c16buffer[ index + 1 ];
							b = c16buffer[ index + 2 ];
							a = c16buffer[ index + 3 ];
						}
					}
				}
			}
			delete[] cbuffer;
		}
	}


	/*---- 開放 ----*/
	png_image_free( &image );

	return colorBuffer;
}

//-------------------------------------
// BMPファイル書き出し
//
uint64 PngFile::WriteFileBuffer( ColorBuffer* colorBuffer, uintptr buffer, uint64 length )
{
	if( colorBuffer != NULL )
	{
		png_image image;
		memset( &image, 0, sizeof( png_image ) );
		image.version = PNG_IMAGE_VERSION;
		image.width = colorBuffer->GetWidth( );
		image.height = colorBuffer->GetHeight( );
		switch( colorBuffer->GetFormat( ) )
		{
		case Gray8:
			image.format = PNG_FORMAT_GRAY;
			break;
		case R8G8B8:
			image.format = PNG_FORMAT_RGB;
			break;
		case A8R8G8B8:
			image.format = PNG_FORMAT_ARGB;
			break;
		case R8G8B8A8:
			image.format = PNG_FORMAT_RGBA;
			break;
		case B8G8R8:
			image.format = PNG_FORMAT_BGR;
			break;
		case A8B8G8R8:
			image.format = PNG_FORMAT_ABGR;
			break;
		case B8G8R8A8:
			image.format = PNG_FORMAT_BGRA;
			break;
		default:
			return 0;
		}
		png_alloc_size_t size = (png_alloc_size_t)length;
		png_image_write_to_memory( &image, (void*)buffer, &size, 0, (const void*)colorBuffer->GetPixelAddress( 0, 0 ), PNG_IMAGE_ROW_STRIDE( image ), NULL );
		return (uint64)size;
	}
	return 0;
}

//-------------------------------------
// 呼び出し開始
//
bool PngFile::OpenReadPngOnMemory( uintptr image, uintptr buffer, uint64 length )
{
	memset( (png_imagep)image, 0, sizeof( png_image ) );
	((png_imagep)image)->version = PNG_IMAGE_VERSION;
	png_image_begin_read_from_memory( (png_imagep)image, (png_const_voidp)buffer, (size_t)length );
	if( PNG_IMAGE_FAILED( *(png_imagep)image ) )
	{
		return false;
	}
	return true;
}

//-------------------------------------
// 情報設定
//
void PngFile::SetupInfomation( PngInfomation* info, uintptr image )
{
	info->Width = ((png_imagep)image)->width;
	info->Height = ((png_imagep)image)->height;
	info->Format = ((png_imagep)image)->format;
	info->Flags = ((png_imagep)image)->flags;
	info->ColorMapCount = ((png_imagep)image)->colormap_entries;
	info->ColorFormat = ColorFormat::Unknown;
	switch( info->Format )
	{
	case PNG_FORMAT_GRAY:
		info->ColorFormat = ColorFormat::Gray8;
		break;
	case PNG_FORMAT_LINEAR_Y:
		info->ColorFormat = ColorFormat::Gray16;
		break;
	case PNG_FORMAT_ARGB:
	case PNG_FORMAT_ARGB_COLORMAP:
	case PNG_FORMAT_AG:
	case PNG_FORMAT_GA:
		info->ColorFormat = ColorFormat::A8R8G8B8;
		break;
	case PNG_FORMAT_RGBA:
	case PNG_FORMAT_RGBA_COLORMAP:
		info->ColorFormat = ColorFormat::R8G8B8A8;
		break;
	case PNG_FORMAT_RGB:
	case PNG_FORMAT_RGB_COLORMAP:
		info->ColorFormat = ColorFormat::R8G8B8;
		break;
	case PNG_FORMAT_ABGR:
	case PNG_FORMAT_ABGR_COLORMAP:
		info->ColorFormat = ColorFormat::A8B8G8R8;
		break;
	case PNG_FORMAT_BGRA:
	case PNG_FORMAT_BGRA_COLORMAP:
		info->ColorFormat = ColorFormat::B8G8R8A8;
		break;
	case PNG_FORMAT_BGR:
	case PNG_FORMAT_BGR_COLORMAP:
		info->ColorFormat = ColorFormat::B8G8R8;
		break;
	case PNG_FORMAT_LINEAR_RGB:
		info->ColorFormat = ColorFormat::RdGdBd;
		break;
	case PNG_FORMAT_LINEAR_RGB_ALPHA:
	case PNG_FORMAT_LINEAR_Y_ALPHA:
		info->ColorFormat = ColorFormat::RdGdBdAd;
		break;
	}
}


} } }