#pragma once

#include <yatools.type.h>

namespace yatools
{
	namespace image
	{

		/**
		* @name ピクセルカラー構造
		* @{
		*/
		/**
		* @enum ColorFormat
		* @brief カラーフォーマット
		* @details
		*	ピクセル単位でのカラーフォーマットです。
		*/
		enum ColorFormat
		{

			Gray8,		//!< Gray 8bit
			Gray16,		//!< Gray 16bit
			R5G5B5,		//!< Red 5bit, Green 5bit, Blue 5bit
			R5G6B5,		//!< Red 5bit, Green 6bit, Blue 5bit
			R4G4B4,		//!< Red 4bit, Green 4bit, Blue 4bit
			R4G4B4A4,	//!< Red 4bit, Green 4bit, Blue 4bit, Alpha 4bit
			A4R4G4B4,	//!< Alpha 4bit, Red 4bit, Green 4bit, Blue 4bit
			R8G8B8,		//!< Red 8bit, Green 8bit, Blue 8bit
			R8G8B8A8,	//!< Red 8bit, Green 8bit, Blue 8bit, Alpha 8bit
			A8R8G8B8,	//!< Alpha 8bit, Red 8bit, Green 8bit, Blue 8bit

			RsGsBs,		//! Red, Green, Blue single float
			RsGsBsAs,	//! Red, Green, Blue, Alpha single float
			AsRsGsBs,	//! Alpha, Red, Green, Blue single float

			RdGdBd,		//! Red, Green, Blue double float
			RdGdBdAd,	//! Red, Green, Blue, Alpha double float
			AdRdGdBd,	//! Alpha, Red, Green, Blue double float

		};


#pragma pack( 0 )

		//! Gray 8bit
		struct YATOOLS_IMPORT ColorGray8
		{
			uint8 Gray;
		};

		//! Gray 16bit
		struct YATOOLS_IMPORT ColorGray16
		{
			uint16 Gray;
		};

		//! Red 5bit, Green 5bit, Blue 5bit
		struct YATOOLS_IMPORT ColorR5G6B5
		{
			uint8 Red : 5;
			uint8 Green : 5;
			uint8 Blue : 5;
			uint8 reserve : 1;
		};

		//! Red 5bit, Green 6bit, Blue 5bit
		struct YATOOLS_IMPORT ColorR5G6B5
		{
			uint8 Red : 5;
			uint8 Green : 6;
			uint8 Blue : 5;
		};

		//! Red 4bit, Green 4bit, Blue 4bit
		struct YATOOLS_IMPORT ColorR4G4B4
		{
			uint8 Red : 4;
			uint8 Green : 4;
			uint8 Blue : 4;
			uint8 reserve : 4;
		};

		//! Red 4bit, Green 4bit, Blue 4bit, Alpha 4bit
		struct YATOOLS_IMPORT ColorR4G4B4A4
		{
			uint8 Red : 4;
			uint8 Green : 4;
			uint8 Blue : 4;
			uint8 Alpha : 4;
		};

		//! Alpha 4bit, Red 4bit, Green 4bit, Blue 4bit
		struct YATOOLS_IMPORT ColorA4R4G4B4
		{
			uint8 Alpha : 4;
			uint8 Red : 4;
			uint8 Green : 4;
			uint8 Blue : 4;
		};

		//! Red 8bit, Green 8bit, Blue 8bit
		struct YATOOLS_IMPORT ColorR8G8B8
		{
			uint8 Red;
			uint8 Green;
			uint8 Blue;
		};

		//! Red 8bit, Green 8bit, Blue 8bit, Alpha 8bit
		struct YATOOLS_IMPORT ColorR8G8B8A8
		{
			uint8 Red;
			uint8 Green;
			uint8 Blue;
			uint8 Alpha;
		};

		//! Alpha 8bit, Red 8bit, Green 8bit, Blue 8bit
		struct YATOOLS_IMPORT ColorA8R8G8B8
		{
			uint8 Alpha;
			uint8 Red;
			uint8 Green;
			uint8 Blue;
		};

		//! Red, Green, Blue single float
		struct YATOOLS_IMPORT ColorRsGsBs
		{
			float Red;
			float Green;
			float Blue;
		};

		//! Red, Green, Blue, Alpha single float
		struct YATOOLS_IMPORT ColorRsGsBsAs
		{
			float Red;
			float Green;
			float Blue;
			float Alpha;
		};

		//! Alpha, Red, Green, Blue single float
		struct YATOOLS_IMPORT ColorAsRsGsBs
		{
			float Alpha;
			float Red;
			float Green;
			float Blue;
		};

		//! Red, Green, Blue double float
		struct YATOOLS_IMPORT ColorRdGdBd
		{
			double Red;
			double Green;
			double Blue;
		};

		//! Red, Green, Blue, Alpha double float
		struct YATOOLS_IMPORT ColorRdGdBdAd
		{
			double Red;
			double Green;
			double Blue;
			double Alpha;
		};

		//! Alpha, Red, Green, Blue double float
		struct YATOOLS_IMPORT ColorAdRdGdBd
		{
			double Alpha;
			double Red;
			double Green;
			double Blue;
		};

		/**
		* @}
		*/

#pragma pack( )


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


		protected:
			ColorFormat		m_Format;			//!< フォーマット
			uint32			m_Width;			//!< 横幅
			uint32			m_Height;			//!< 縦幅
			byte*			m_Buffer;			//!< バッファ
			uint64			m_BufferSize;		//!< バッファサイズ

		};


	}
}