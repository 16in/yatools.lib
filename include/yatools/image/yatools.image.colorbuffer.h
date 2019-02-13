#pragma once

#include "yatools.image.type.h"


namespace yatools
{
	namespace image
	{

		/**
		* @class ColorBuffer
		* @brief カラーバッファ
		* @details
		*	カラーバッファ管理クラスです。
		*/
		class YATOOLS_IMPORT ColorBuffer
		{
		public:
			/**
			* @name 生成/開放
			* @{
			*/
			/**
			* @brief 生成
			* @param[in] format				カラーバッファフォーマット
			* @param[in] width				横幅
			* @param[in] height				縦幅
			* @returns 生成されたカラーバッファ。失敗時はNULL
			* @details
			*	空のカラーバッファを生成して返します。
			*/
			static ColorBuffer* Create( ColorFormat format, uint32 width, uint32 height );

			/**
			* @brief 生成
			* @param[in] format				カラーバッファフォーマット
			* @param[in] width, height		横幅、縦幅
			* @param[in] buffer				コピー元のカラーバッファ
			* @param[in] length				bufferサイズ
			* @returns 生成されたカラーバッファ。失敗時はNULL
			* @details
			*	カラーバッファを生成して返します。
			*/
			static ColorBuffer* Create( ColorFormat format, uint32 width, uint32 height, uintptr buffer, uint64 length );

			/**
			* @brief 開放
			* @details
			*	カラーバッファを開放します。
			*/
			virtual void Release( );

			/**
			* @}
			*/
			/**
			* @name ピクセル操作
			* @{
			*/
			/**
			* @brief ピクセルサイズ取得
			* @returns						1ピクセル当たりのバイト数
			* @details
			*	カラーバッファの1ピクセル当たりのバイト数を取得します。
			*/
			uint64 GetPixelSize( void );

			/**
			* @brief ピクセル設定
			* @param[in] x, y				座標
			* @param[in] pixel				設定するカラーが格納されている領域の先頭ポインタ
			* @param[in] length				colorが指すポインタの領域サイズ
			* @retval true					設定に成功
			* @retval false					設定に失敗
			* @details
			*	指定座標のピクセルに対してピクセルカラーを設定します。
			*/
			bool SetPixel( uint32 x, uint32 y, uintptr pixel, uint64 length );

			/**
			* @brief ピクセル設定
			* @param[in] x, y				設定開始先頭座標
			* @param[in] pixels				設定するカラーが格納されている領域の先頭ポインタ
			* @param[in] length				ピクセルの設定範囲
			* @retval true					設定に成功
			* @retval false					設定に失敗
			* @details
			*	x, yで指定される座標のピクセルを先頭とし、length/GetPixelSize()個数分のピクセルをpixelsの内容で変更します。
			*/
			bool SetPixels( uint32 x, uint32 y, uintptr pixels, uint64 length );

			/**
			* @brief ピクセルアドレス取得
			* @param[in] x, y				座標
			* @returns						座標のピクセルが格納されている領域の先頭ポインタ
			* @retval NULL					取得に失敗
			* @details
			*	指定座標のピクセルが格納されている領域の先頭ポインタを取得します。	\n
			*	取得に成功した場合、少なくとも「戻り値 + GetPixelSize()」の領域は有効です。
			*/
			uintptr GetPixelAddress( uint32 x, uint32 y );

			/**
			* @brief ピクセルブロック設定
			* @param[in] x, y				ブロック左上座標
			* @param[in] width, height		書き換えブロックサイズ
			* @param[in] blocks				書き換えブロック内容を保持する領域の先頭ポインタ
			* @param[in] length				blocksの領域サイズ
			* @retval true					成功
			* @retval false					失敗
			* @details
			*	カラーバッファ内の矩形領域を設定します。
			*/
			bool SetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height, uintptr blocks, uint64 length );

			/**
			* @brief ピクセルブロック設定
			* @param[in] x, y				ブロック左上座標
			* @param[in] blockBuffer		書き換える内容を保持するカラーバッファ	\n
			*								カラーフォーマットが同一である必要があります。
			* @retval true					成功
			* @retval false					失敗
			* @details
			*	カラーバッファ内の矩形領域を設定します。
			*/
			bool SetPixelBlock( uint32 x, uint32 y, ColorBuffer* blockBuffer );

			/**
			* @brief ピクセルブロック取得
			* @param[in] x, y				取得開始左上座標
			* @param[in] width, height		取得横幅、縦幅
			* @returns						ピクセルブロック全体のカラーバッファ
			* @retval NULL					失敗
			* @details
			*	カラーバッファ内の矩形情報を取得します。
			*/
			ColorBuffer* GetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height );

			/**
			* @brief ピクセルブロック取得
			* @param[in] x, y				取得開始左上座標
			* @param[in] width, height		取得横幅、縦幅
			* @param[in] blockBuffer		ピクセルブロック格納先
			* @param[in] length				blockBufferの長さ	\n
			*								最低でもwidth * height * GetPixelSize()が必要です。
			* @retval true					成功
			* @retval false					失敗
			* @details
			*	カラーバッファ内の矩形情報を取得します。
			*/
			bool GetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height, uintptr blockBuffer, uint64 length );

			/**
			* @}
			*/


		protected:
			/**
			* @name コンストラクタ/デストラクタ
			* @{
			*/
			/**
			* @brief コンストラクタ
			* @details
			*	デフォルトコンストラクタです。
			*/
			ColorBuffer( void );

			/**
			* @biref コピーコンストラクタ
			* @param[ref] source			コピー元
			* @details
			*	コピーコンストラクタです。
			*/
			ColorBuffer( ColorBuffer& source );

			/**
			* @brief デストラクタ
			* @details
			*	デストラクタです。
			*/
			virtual ~ColorBuffer( void );

			/**
			* @}
			*/


		protected:
			ColorFormat		m_Format;			//!< フォーマット
			uint32			m_Width;			//!< 横幅
			uint32			m_Height;			//!< 縦幅
			uintptr			m_Buffer;			//!< バッファ
			uint64			m_BufferSize;		//!< バッファサイズ
			uint64			m_PixelSize;		//!< 1ピクセルあたりのサイズ

		};


	}
}