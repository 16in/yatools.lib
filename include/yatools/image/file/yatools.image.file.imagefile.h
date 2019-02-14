#pragma once

#include "../yatools.image.colorbuffer.h"


namespace yatools
{
	namespace image
	{
		namespace file
		{

			/**
			* @class ImageFile
			* @brief 画像ファイル
			* @details
			*	画像ファイル基底クラスです。
			*/
			class YATOOLS_IMPORT ImageFile
			{
			public:
				/**
				* @name 取得
				* @{
				*/
				/**
				* @brief カラーバッファ取得
				* @returns						画像ファイル全体を表すカラーバッファ
				* @details
				*	画像ファイルの全体を表すカラーバッファを生成して取得します。
				*/
				virtual ColorBuffer* GetColorBuffer( void ) = 0;

				/**
				* @brief 横幅取得
				* @returns						画像横幅
				* @details
				*	画像ファイルの横幅を取得します。
				*/
				virtual uint32 GetWidth( void ) = 0;

				/**
				* @brief 縦幅取得
				* @returns						画像縦幅
				* @details
				*	画像ファイルの縦幅を取得します。
				*/
				virtual uint32 GetHeight( void ) = 0;

				/**
				* @brief カラーフォーマット取得
				* @returns						カラーフォーマット
				* @details
				*	画像ファイルのカラーフォーマットを取得します。
				*/
				virtual ColorFormat GetFormat( void ) = 0;

				/**
				* @}
				*/


			protected:
				/**
				* @name コンストラクタ/デストラクタ
				* @{
				*/
				/**
				* @brief デフォルトコンストラクタ
				* @details
				*	デフォルトコンストラクタです。
				*/
				ImageFile( void );

				/**
				* @brief コピーコンストラクタ
				* @param[ref] source			コピー元
				* @details
				*	コピーコンストラクタです。
				*/
				ImageFile( ImageFile& source );

				/**
				* @brief デストラクタ
				* @details
				*	デストラクタです。
				*/
				virtual ~ImageFile( void );

				/**
				* @}
				*/

			};

		}
	}
}
