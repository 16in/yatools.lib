#pragma once

#include "yatools.image.colorbuffer.h"

#ifndef _WIN32
#error This API is Windows only.
#endif
#include <Windows.h>


namespace yatools
{
	namespace image
	{

		/**
		* @class Windows
		* @brief Windows関係
		* @details
		*	Windows特有の形式に関連づいたオブジェクトの制御クラスです。
		*/
		class YATOOLS_IMPORT Windows
		{
		public:

			/**
			* @brief カラーバッファ取得
			* @param[in] hWnd				取得元のウィンドウハンドル
			* @retturns						生成されたカラーバッファ
			* @retval NULL					取得に失敗
			* @details
			*	ウィンドウハンドルで指定されたウィンドウ全体をカラーバッファとして取得します。
			*/
			static ColorBuffer* GetColorBuffer( HWND hWnd );

			/**
			* @brief カラーバッファ取得
			* @param[in] hDc				取得するビットマップが含まれているデバイスコンテキスト
			* @param[in] width, height		横幅、縦幅
			* @returns						生成されたカラーバッファ
			* @retval NULL					取得に失敗
			* @details
			*	デバイスコンテキストのビットマップからカラーバッファを取得します。
			*/
			static ColorBuffer* GetColorBuffer( HDC hDc, uint32 width, uint32 height );

			/**
			* @brief カラーバッファ取得
			* @param[in] hBitMap			取得元のビットマップハンドル
			* @returns						取得されたカラーバッファ
			* @retval NULL					取得に失敗
			* @details
			*	ビットマップハンドルからカラーバッファを取得します。
			*/
			static ColorBuffer* GetColorBuffer( HBITMAP hBitMap );

		};

	}
}