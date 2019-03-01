#pragma once

#include "../yatools.image.colorbuffer.h"


namespace yatools
{
	namespace image
	{
		namespace file
		{

			/**
			* @struct PngInfomation
			* @brief PNGファイル情報
			* @details
			*	PNGファイルの画像チャンク情報です。
			*/
			struct PngInfomation
			{
				uint32		Width;			//!< 横幅
				uint32		Height;			//!< 縦幅
				ColorFormat	ColorFormat;	//!< カラーバッファの対応フォーマット\nカラーバッファ未対応の場合はUnknown

				// libPngネイティブの値
				uint32		Format;			//!< フォーマット
				uint32		Flags;			//!< ビットマスクフラグ
				uint32		ColorMapCount;	//!< カラーマップ数
			};


			/**
			* @class PngFile
			* @brief PNGファイル
			* @details
			*	PNGファイルクラスです。
			*/
			class PngFile
			{
			public:
				/**
				* @name バイナリ操作
				* @{
				*/
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
				static bool GetInfomation( PngInfomation* infomation, uintptr buffer, uint64 length );

				/**
				* @brief カラーバッファ取得
				* @param[in] buffer					PNGファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							生成されたカラーバッファ
				* @retval NULL						生成に失敗
				* @details
				*	PNG画像をカラーバッファ化します。
				*/
				static ColorBuffer* GetColorBuffer( uintptr buffer, uint64 length );

				/**
				* @brief BMPファイル書き出し
				* @param[in] colorBuffer			PNGファイルとして書き出すカラーバッファ
				* @param[in, out] buffer			書き出し先メモリ領域	\n
				*									NULLの場合は戻り値が必要な領域サイズを返します。
				* @param[in] length					bufferに格納可能なバイト数
				* @returns							bufferに書き出されたバイト数		\n
				*									bufferがNULLの場合は必要なバイト数
				* @retval 0							colorBufferがPNGファイルに書き出し可能な形式ではない
				* @details
				*	カラーバッファをPNGファイルとしてメモリ領域に書き出します。		\n
				*	書き出し可能なカラーバッファのフォーマットは次のとおりです。	\n
				*	・ColorFormatR8G8B8		\n
				*	・ColorFormatA8R8G8B8	\n
				*	\n
				*	bufferがNULLの場合、ColorBufferの書き出しに必要なバイト数を返します。
				*/
				static uint64 WriteFileBuffer( ColorBuffer* colorBuffer, uintptr buffer, uint64 length );

			private:
				//! 呼び出し開始
				static bool OpenReadPngOnMemory( uintptr image, uintptr buffer, uint64 length );

				//! 情報設定
				static void SetupInfomation( PngInfomation* info, uintptr image );

				/**
				* @}
				*/
				

			};


		}
	}
}
