#pragma once

#include "../yatools.image.colorbuffer.h"


namespace yatools
{
	namespace image
	{
		namespace file
		{

#pragma pack( 1 )
			/**
			* @struct BmpHeader
			* @name BMPファイルヘッダ
			* @details
			*	BMPファイルヘッダ構造体です。
			*/
			struct YATOOLS_IMPORT BmpHeader
			{
				union
				{
					uint16 Type;		//!< 'BM'
					char   Kind[ 2 ];	//!< { 'B', 'M' }
				};
				uint32 FileSize;		//!< ファイルサイズ
				uint16 reserve00;		//!< 予約領域
				uint16 reserve01;		//!< 予約領域
				uint32 OffsetImage;		//!< 画像領域オフセット
			};

			/**
			* @struct BmpInfomationHeader
			* @name BMP情報ヘッダ
			* @details
			*	BMP情報ヘッダ構造体です。
			*/
			struct YATOOLS_IMPORT BmpInfomationHeader
			{
				uint32 InfomationSize;	//!< 情報ヘッダサイズ
				int32 Width;			//!< 横幅
				int32 Height;			//!< 縦幅
				uint16 Plane;			//!< プレーン数
				uint16 BitDepth;		//!< ビット深度
				uint32 Compression;		//!< 圧縮形式
				uint32 SizeImage;		//!< 画像サイズ
				int32 BppmWidth;		//!< 水平解像度
				int32 BppmHeight;		//!< 垂直解像度
				uint32 ClrUsed;			//!< 格納パレット数
				uint32 CirImportant;	//!< 重要色数
			};
#pragma pack( )


			/**
			* @class BmpFile
			* @brief BMPファイル
			* @details
			*	BMPファイルクラスです。
			*/
			class YATOOLS_IMPORT BmpFile
			{
			public:
				/**
				* @name バイナリ操作
				* @{
				*/
				/**
				* @brief ファイルヘッダ取得
				* @param[in] buffer					BMPファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							BMPファイルヘッダ構造体
				* @details
				*	ファイルヘッダを取得します。
				*/
				static BmpHeader* GetHeader( uintptr buffer, uint64 length );

				/**
				* @brief 情報ヘッダ取得
				* @param[in] buffer					BMPファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							BMP情報ヘッダ構造体
				* @details
				*	情報ヘッダを取得します。
				*/
				static BmpInfomationHeader* GetInfomationHeader( uintptr buffer, uint64 length );

				/**
				* @brief カラーパレット取得
				* @param[in] buffer					BMPファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							カラーパレット先頭アドレス	\n
				*									存在しない場合はNULL
				* @details
				*	カラーパレットの先頭アドレスを取得します。
				*/
				static uintptr GetColorPalets( uintptr buffer, uint64 length );

				/**
				* @brief 画像フィールド取得
				* @param[in] buffer					BMPファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							画像フィールドの先頭ポインタ
				* @retval NULL						存在しない
				* @details
				*	画像フィールドを取得します。			\n
				*	画像フィールドの情報はヘッダを参照してください。
				*/
				static uintptr GetImageField( uintptr buffer, uint64 length );

				/**
				* @brief カラーバッファ取得
				* @param[in] buffer					BMPファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							生成されたカラーバッファ
				* @retval NULL						生成に失敗
				* @details
				*	画像フィールドをヘッダ情報に従ってカラーバッファ化します。	\n
				*	圧縮形式の場合、この関数は失敗します。
				*/
				static ColorBuffer* GetColorBuffer( uintptr buffer, uint64 length );

				/**
				* @brief BMPファイル書き出し
				* @param[in] colorBuffer			BMPファイルとして書き出すカラーバッファ
				* @param[in, out] buffer			書き出し先メモリ領域	\n
				*									NULLの場合は戻り値が必要な領域サイズを返します。
				* @param[in] length					bufferに格納可能なバイト数
				* @returns							bufferに書き出されたバイト数		\n
				*									bufferがNULLの場合は必要なバイト数
				* @retval 0							colorBufferがBMPファイルに書き出し可能な形式ではない
				* @details
				*	カラーバッファをBMPファイルとしてメモリ領域に書き出します。		\n
				*	書き出し可能なカラーバッファのフォーマットは次のとおりです。	\n
				*	・ColorFormatR8G8B8		\n
				*	・ColorFormatA8R8G8B8	\n
				*	\n
				*	bufferがNULLの場合、ColorBufferの書き出しに必要なバイト数を返します。
				*/
				static uint64 WriteFileBuffer( ColorBuffer* colorBuffer, uintptr buffer, uint64 length );

				/**
				* @}
				*/

			private:
				//! 32bitカラー取得
				static ColorBuffer* GetColorBuffer32( uintptr buffer, uint64 length );

				//! 24bitカラー取得
				static ColorBuffer* GetColorBuffer24( uintptr buffer, uint64 length );

				//! パレットカラー取得
				static ColorBuffer* GetColorBufferPalet( uintptr buffer, uint64 length );

			};

		}
	}
}
