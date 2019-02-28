#ifdef _WIN32
#include "yatools/image/yatools.image.windows.h"

namespace yatools { namespace image {


//-------------------------------------
// �J���[�o�b�t�@�擾
//
ColorBuffer* Windows::GetColorBuffer( HWND hWnd )
{
	/*---- �f�o�C�X�R���e�L�X�g�擾 ----*/
	ColorBuffer* buffer = NULL;
	HDC hDC = GetDC( hWnd );
	if( hDC != NULL )
	{
		RECT rect = { 0 };
		GetWindowRect( hWnd, &rect );
		buffer = GetColorBuffer( hDC, rect.right - rect.left, rect.bottom - rect.top );
	}
	ReleaseDC( hWnd, hDC );
	return buffer;
}


//-------------------------------------
// �J���[�o�b�t�@�擾
//
ColorBuffer* Windows::GetColorBuffer( HDC hDC, uint32 width, uint32 height )
{
	/*---- �r�b�g�}�b�v�����ݒ� ----*/
	BITMAPINFO info;
	BITMAPINFOHEADER header;
	ZeroMemory( &header, sizeof( header ) );
	header.biSize = sizeof( header );
	header.biWidth = width;
	header.biHeight = height;
	header.biPlanes = 1;
	header.biBitCount = 24;
	
	info.bmiHeader = header;
	void* pixcels;


	/*---- �������f�o�C�X�R���e�L�X�g���� ----*/
	// �J���[�o�b�t�@����
	HBITMAP hBitmap = CreateDIBSection( NULL, (LPBITMAPINFO)&info, DIB_RGB_COLORS, &pixcels, NULL, 0 );
	if( hBitmap == NULL )
	{
		return NULL;
	}

	// �R�s�[�p������DC����
	HDC hMemDC = CreateCompatibleDC( hDC );
	if( hMemDC == NULL )
	{
		DeleteObject( hBitmap );
		return NULL;
	}

	// ������DC�Z�b�g�A�b�v
	HBITMAP hOldBitmap = (HBITMAP)SelectObject( hMemDC, hBitmap );


	/*---- ������DC�ɕ��� ----*/
	BitBlt( hMemDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY );


	/*---- ������DC�p�� ----*/
	SelectObject( hMemDC, hOldBitmap );
	DeleteDC( hMemDC );


	/*---- �J���[�o�b�t�@�擾 ----*/
	ColorBuffer* buffer = GetColorBuffer( hBitmap );


	/*---- �r�b�g�}�b�v�p�� ----*/
	DeleteObject( hBitmap );


	return buffer;
}

//-------------------------------------
// �J���[�o�b�t�@�擾
//
ColorBuffer* Windows::GetColorBuffer( HBITMAP hBitmap )
{
	if( hBitmap == NULL )
	{
		return NULL;
	}


	/*---- �r�b�g�}�b�v���擾 ----*/
	BITMAP bitmap;
	GetObject( hBitmap, sizeof( BITMAP ), &bitmap );


	/*---- �J���[�o�b�t�@���� ----*/
	ColorFormat format = ColorFormat::R8G8B8;
	if( bitmap.bmBitsPixel == 32 )
	{
		format = ColorFormat::A8R8G8B8;
	}
	else if( bitmap.bmBitsPixel == 16 )
	{
		format = ColorFormat::R5G6B5;
	}
	else if( bitmap.bmBitsPixel == 8 )
	{
		format = ColorFormat::Gray8;
	}
	ColorBuffer* buffer = ColorBuffer::Create( format, bitmap.bmWidth, bitmap.bmHeight );
	if( buffer != NULL )
	{
		uintptr bits = (uintptr)bitmap.bmBits;
		for( uint32 y = 0; y < (uint32)bitmap.bmHeight; y++ )
		{
			buffer->SetPixels( 0, bitmap.bmHeight - y - 1, bits + (bitmap.bmWidthBytes * y), bitmap.bmWidthBytes );
		}
	}
	return buffer;
}


} }


#endif