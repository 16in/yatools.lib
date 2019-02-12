#include <yatools/yatools.image.h>


#define YATOOLS_IMAGE_GETCOLORFORMAT_PIXELSIZE( FORMAT ) case ColorFormat::FORMAT: return (uint)sizeof( Color##FORMAT )


namespace yatools { namespace image {

	
//-------------------------------------
// �s�N�Z���J���[�\���֌W
//-------------------------------------

/**
* @fn ulong GetColorFormatPixelSize( ColorFormat format )
* @brief �J���[�t�H�[�}�b�g�s�N�Z���T�C�Y�擾
* @param[in] format				�J���[�t�H�[�}�b�g
* @returns						�J���[�t�H�[�}�b�g��1�s�N�Z��������̃o�C�g��
* @retval 0						�J���[�t�H�[�}�b�g�������ł�
* @details
*	�w�肳�ꂽ�J���[�t�H�[�}�b�g��1�s�N�Z��������̃o�C�g�T�C�Y���擾���܂��B
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
