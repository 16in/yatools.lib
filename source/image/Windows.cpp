#ifdef _WIN32
#include "yatools/image/yatools.image.windows.h"

namespace yatools { namespace image {


//-------------------------------------
// カラーバッファ取得
//
ColorBuffer* Windows::GetColorBuffer( HWND hWnd )
{
	/*---- デバイスコンテキスト取得 ----*/
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
// カラーバッファ取得
//
ColorBuffer* Windows::GetColorBuffer( HDC hDC, uint32 width, uint32 height )
{
	/*---- ビットマップ諸元設定 ----*/
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


	/*---- メモリデバイスコンテキスト生成 ----*/
	// カラーバッファ生成
	HBITMAP hBitmap = CreateDIBSection( NULL, (LPBITMAPINFO)&info, DIB_RGB_COLORS, &pixcels, NULL, 0 );
	if( hBitmap == NULL )
	{
		return NULL;
	}

	// コピー用メモリDC生成
	HDC hMemDC = CreateCompatibleDC( hDC );
	if( hMemDC == NULL )
	{
		DeleteObject( hBitmap );
		return NULL;
	}

	// メモリDCセットアップ
	HBITMAP hOldBitmap = (HBITMAP)SelectObject( hMemDC, hBitmap );


	/*---- メモリDCに複製 ----*/
	BitBlt( hMemDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY );


	/*---- メモリDC廃棄 ----*/
	SelectObject( hMemDC, hOldBitmap );
	DeleteDC( hMemDC );


	/*---- カラーバッファ取得 ----*/
	ColorBuffer* buffer = GetColorBuffer( hBitmap );


	/*---- ビットマップ廃棄 ----*/
	DeleteObject( hBitmap );


	return buffer;
}

//-------------------------------------
// カラーバッファ取得
//
ColorBuffer* Windows::GetColorBuffer( HBITMAP hBitmap )
{
	if( hBitmap == NULL )
	{
		return NULL;
	}


	/*---- ビットマップ情報取得 ----*/
	BITMAP bitmap;
	GetObject( hBitmap, sizeof( BITMAP ), &bitmap );


	/*---- カラーバッファ生成 ----*/
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