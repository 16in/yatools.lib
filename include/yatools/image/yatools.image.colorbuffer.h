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
			* @name 変換
			* @{
			*/
			/**
			* @brife フォーマット変換
			* @param[in] format				新しいフォーマット
			* @returns						新しいフォーマットに変換されたカラーバッファ
			* @details
			*	新しいフォーマットにカラーバッファを変換します。
			*/
			ColorBuffer* Convert( ColorFormat format );

			/**
			* @}
			*/
			/**
			* @name ピクセル操作
			* @{
			*/

			bool SetPixel( uint32 x, uint32 y, float r, float g, float b, float a = 1.0f );

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
			uint			m_PixelSize;		//!< 1ピクセルあたりのサイズ

		};


	}
}