#include <yatools/yatools.image.h>


#define YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( FORMAT ) case ColorFormat::FORMAT: return (uint)sizeof( Color##FORMAT )


namespace yatools { namespace image {

	
//-------------------------------------
// ピクセルカラー構造関係
//-------------------------------------

/**
* @fn ulong GetColorFormatPixelSize( ColorFormat format )
* @brief カラーフォーマットピクセルサイズ取得
* @param[in] format				カラーフォーマット
* @returns						カラーフォーマットの1ピクセルあたりのバイト数
* @retval 0						カラーフォーマットが無効です
* @details
*	指定されたカラーフォーマットの1ピクセルあたりのバイトサイズを取得します。
*/
uint GetColorFormatPixelSize( ColorFormat format )
{
	switch( format )
	{
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( Gray8 );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( Gray16 );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( R5G5B5 );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( R5G6B5 );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( R4G4B4 );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( R4G4B4A4 );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( A4R4G4B4 );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( R8G8B8 );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( R8G8B8A8 );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( A8R8G8B8 );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( RsGsBs );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( RsGsBsAs );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( AsRsGsBs );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( RdGdBd );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( RdGdBdAd );
		YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( AdRdGdBd );
	}
	return 0;
}



} }
