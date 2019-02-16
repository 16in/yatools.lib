#pragma once

#include "../yatools.type.h"


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

			Unknown = 0,	//!< Unknown

			Gray8,			//!< Gray 8bit
			Gray16,			//!< Gray 16bit

			R5G5B5,			//!< Red 5bit, Green 5bit, Blue 5bit
			B5G5R5,			//!< Blue 5bit, Green 5Bit, Red 5bit
			R5G6B5,			//!< Red 5bit, Green 6bit, Blue 5bit
			B5G6R5,			//!< Blue 5bit, Green 6Bit, Red 5bit
			R5G5B5A1,		//!< Red 5bit, Green 5bit, Blue 5bit, Alpha 1bit
			B5G5R5A1,		//!< Blue 5bit, Green 5Bit, Red 5bit, Alpha 1bit
			A1R5G5B5,		//!< Alpha 1bit, Red 5bit, Green 5bit, Blue 5bit
			A1B5G5R5,		//!< Alpha 1bit, Blue 5bit, Green 5Bit, Red 5bit

			R4G4B4,			//!< Red 4bit, Green 4bit, Blue 4bit
			B4G4R4,			//!< Blue 4bit, Green 4bit, Red 4bit
			R4G4B4A4,		//!< Red 4bit, Green 4bit, Blue 4bit, Alpha 4bit
			B4G4R4A4,		//!< Blue 4bit, Green 4bit, Red 4bit, Alpha 4bit
			A4R4G4B4,		//!< Alpha 4bit, Red 4bit, Green 4bit, Blue 4bit
			A4B4G4R4,		//!< Alpha 4bit, Blue 4bit, Green 4bit, Red 4bit

			R8G8B8,			//!< Red 8bit, Green 8bit, Blue 8bit
			B8G8R8,			//!< Blue 8bit, Green 8bit, Red 8bit
			R8G8B8A8,		//!< Red 8bit, Green 8bit, Blue 8bit, Alpha 8bit
			B8G8R8A8,		//!< Blue 8bit, Green 8bit, Red 8bit, Alpha 8bit
			A8R8G8B8,		//!< Alpha 8bit, Red 8bit, Green 8bit, Blue 8bit
			A8B8G8R8,		//!< Blue 8bit, Green 8bit, Red 8bit, Alpha 8bit

			RsGsBs,			//! Red, Green, Blue single float
			RsGsBsAs,		//! Red, Green, Blue, Alpha single float
			AsRsGsBs,		//! Alpha, Red, Green, Blue single float
			RdGdBd,			//! Red, Green, Blue double float
			RdGdBdAd,		//! Red, Green, Blue, Alpha double float
			AdRdGdBd,		//! Alpha, Red, Green, Blue double float

		};


#pragma pack( push, 1 )

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
		struct YATOOLS_IMPORT ColorR5G5B5
		{
			uint16 bits;
			inline void SetRed( uint8 r ) { bits = (bits & 0x07ff) | ((r & 0x1f) << 11); }
			inline void SetGreen( uint8 g ) { bits = (bits & 0xf83f) | ((g & 0x1f) << 6); }
			inline void SetBlue( uint8 b ) { bits = (bits & 0xffC1) | ((b & 0x1f) << 1); }
			inline uint8 GetRed( void ) { return bits & 0x1f; }
			inline uint8 GetGreen( void ) { return (bits >> 5) & 0x1f; }
			inline uint8 GetBlue( void ) { return (bits >> 10) & 0x1f; }
		};

		//! Blue 5bit, Green 5bit, Red 5bit
		struct YATOOLS_IMPORT ColorB5G5R5
		{
			uint16 bits;
			inline void SetRed( uint8 r ) { bits = (bits & 0xffC1) | ((r & 0x1f) << 1); }
			inline void SetGreen( uint8 g ) { bits = (bits & 0xf83f) | ((g & 0x1f) << 6); }
			inline void SetBlue( uint8 b ) { bits = (bits & 0x07ff) | ((b & 0x1f) << 11); }
			inline uint8 GetRed( void ) { return (bits >> 10) & 0x1f; }
			inline uint8 GetGreen( void ) { return (bits >> 5) & 0x1f; }
			inline uint8 GetBlue( void ) { return bits & 0x1f; }
		};

		//! Red 5bit, Green 5bit, Blue 5bit, Alpha 1bit
		struct YATOOLS_IMPORT ColorR5G5B5A1
		{
			uint16 bits;
			inline void SetRed( uint8 r ) { bits = (bits & 0x07ff) | ((r & 0x1f) << 11); }
			inline void SetGreen( uint8 g ) { bits = (bits & 0xf83f) | ((g & 0x1f) << 6); }
			inline void SetBlue( uint8 b ) { bits = (bits & 0xffC1) | ((b & 0x1f) << 1); }
			inline void SetAlpha( uint8 a ) { bits = (bits & 0xfffe) | (a & 0x01); }
			inline uint8 GetRed( void ) { return (bits >> 11) & 0x1f; }
			inline uint8 GetGreen( void ) { return (bits >> 6) & 0x1f; }
			inline uint8 GetBlue( void ) { return (bits >> 1) & 0x1f; }
			inline uint8 GetAlpha( void ) { return bits & 0x01; }
		};

		//! Blue 5bit, Green 5bit, Red 5bit, Alpha 1bit
		struct YATOOLS_IMPORT ColorB5G5R5A1
		{
			uint16 bits;
			inline void SetRed( uint8 r ) { bits = (bits & 0xffC1) | ((r & 0x1f) << 1); }
			inline void SetGreen( uint8 g ) { bits = (bits & 0xf83f) | ((g & 0x1f) << 6); }
			inline void SetBlue( uint8 b ) { bits = (bits & 0x07ff) | ((b & 0x1f) << 11); }
			inline void SetAlpha( uint8 a ) { bits = (bits & 0xfffe) | (a & 0x01); }
			inline uint8 GetRed( void ) { return (bits >> 1) & 0x1f; }
			inline uint8 GetGreen( void ) { return (bits >> 6) & 0x1f; }
			inline uint8 GetBlue( void ) { return (bits >> 11) & 0x1f; }
			inline uint8 GetAlpha( void ) { return bits & 0x01; }
		};

		//! Alpha 1bit, Red 5bit, Green 5bit, Blue 5bit
		struct YATOOLS_IMPORT ColorA1R5G5B5
		{
			uint16 bits;
			inline void SetRed( uint8 r ) { bits = (bits & 0x83ff) | ((r & 0x1f) << 10); }
			inline void SetGreen( uint8 g ) { bits = (bits & 0xfc1f) | ((g & 0x1f) << 5); }
			inline void SetBlue( uint8 b ) { bits = (bits & 0xffe0) | ((b & 0x1f)); }
			inline void SetAlpha( uint8 a ) { bits = (bits & 0x7fff) | ((a & 0x01) << 15); }
			inline uint8 GetRed( void ) { return (bits >> 10) & 0x1f; }
			inline uint8 GetGreen( void ) { return (bits >> 5) & 0x1f; }
			inline uint8 GetBlue( void ) { return bits & 0x1f; }
			inline uint8 GetAlpha( void ) { return (bits >> 15); }
		};

		//! Alpha 1bit, Blue 5bit, Green 5bit, Red 5bit
		struct YATOOLS_IMPORT ColorA1B5G5R5
		{
			uint16 bits;
			inline void SetRed( uint8 r ) { bits = (bits & 0xffe0) | ((r & 0x1f)); }
			inline void SetGreen( uint8 g ) { bits = (bits & 0xfc1f) | ((g & 0x1f) << 5); }
			inline void SetBlue( uint8 b ) { bits = (bits & 0x83ff) | ((b & 0x1f) << 10); }
			inline void SetAlpha( uint8 a ) { bits = (bits & 0x7fff) | ((a & 0x01) << 15); }
			inline uint8 GetRed( void ) { return bits & 0x1f; }
			inline uint8 GetGreen( void ) { return (bits >> 5) & 0x1f; }
			inline uint8 GetBlue( void ) { return (bits >> 10) & 0x1f; }
			inline uint8 GetAlpha( void ) { return (bits >> 15); }
		};

		//! Red 5bit, Green 6bit, Blue 5bit
		struct YATOOLS_IMPORT ColorR5G6B5
		{
			uint16 bits;
			inline void SetRed( uint8 r ) { bits = (bits & 0xffe0) | ((r & 0x1f)); }
			inline void SetGreen( uint8 g ) { bits = (bits & 0xf81f) | ((g & 0x3f) << 5); }
			inline void SetBlue( uint8 b ) { bits = (bits & 0x07ff) | ((b & 0x1f) << 11); }
			inline uint8 GetRed( void ) { return (bits >> 11) & 0x1f; }
			inline uint8 GetGreen( void ) { return (bits >> 5) & 0x3f; }
			inline uint8 GetBlue( void ) { return bits & 0x1f; }
		};

		//! Blue 5bit, Green 6bit, Red 5bit
		struct YATOOLS_IMPORT ColorB5G6R5
		{
			uint16 bits;
			inline void SetRed( uint8 r ) { bits = (bits & 0x07ff) | ((r & 0x1f) << 11); }
			inline void SetGreen( uint8 g ) { bits = (bits & 0xf81f) | ((g & 0x3f) << 5); }
			inline void SetBlue( uint8 b ) { bits = (bits & 0xffe0) | ((b & 0x1f)); }
			inline uint8 GetRed( void ) { return bits & 0x1f; }
			inline uint8 GetGreen( void ) { return (bits >> 5) & 0x3f; }
			inline uint8 GetBlue( void ) { return (bits >> 11) & 0x1f; }
		};

		//! Red 4bit, Green 4bit, Blue 4bit
		struct YATOOLS_IMPORT ColorR4G4B4
		{
			uint8 Blue : 4;
			uint8 Green : 4;
			uint8 Red : 4;
			uint8 reserve : 4;
		};

		//! Blue 4bit, Green 4bit, Red 4bit
		struct YATOOLS_IMPORT ColorB4G4R4
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

		//! Blue 4bit, Green 4bit, Red 4bit, Alpha 4bit
		struct YATOOLS_IMPORT ColorB4G4R4A4
		{
			uint8 Alpha : 4;
			uint8 Red : 4;
			uint8 Green : 4;
			uint8 Blue : 4;
		};

		//! Alpha 4bit, Red 4bit, Green 4bit, Blue 4bit
		struct YATOOLS_IMPORT ColorA4R4G4B4
		{
			uint8 Blue : 4;
			uint8 Green : 4;
			uint8 Red : 4;
			uint8 Alpha : 4;
		};

		//! Alpha 4bit, Blue 4bit, Green 4bit, Red 4bit
		struct YATOOLS_IMPORT ColorA4B4G4R4
		{
			uint8 Red : 4;
			uint8 Green : 4;
			uint8 Blue : 4;
			uint8 Alpha : 4;
		};

		//! Red 8bit, Green 8bit, Blue 8bit
		struct YATOOLS_IMPORT ColorR8G8B8
		{
			uint8 Blue;
			uint8 Green;
			uint8 Red;
		};

		//! Blue 8bit, Green 8bit, Red 8bit
		struct YATOOLS_IMPORT ColorB8G8R8
		{
			uint8 Red;
			uint8 Green;
			uint8 Blue;
		};

		//! Red 8bit, Green 8bit, Blue 8bit, Alpha 8bit
		struct YATOOLS_IMPORT ColorR8G8B8A8
		{
			uint8 Alpha;
			uint8 Blue;
			uint8 Green;
			uint8 Red;
		};

		//! Blue 8bit, Green 8bit, Red 8bit, Alpha 8bit
		struct YATOOLS_IMPORT ColorB8G8R8A8
		{
			uint8 Alpha;
			uint8 Red;
			uint8 Green;
			uint8 Blue;
		};

		//! Alpha 8bit, Red 8bit, Green 8bit, Blue 8bit
		struct YATOOLS_IMPORT ColorA8R8G8B8
		{
			uint8 Blue;
			uint8 Green;
			uint8 Red;
			uint8 Alpha;
		};

		//! Alpha 8bit, Blue 8bit, Green 8bit, Red 8bit
		struct YATOOLS_IMPORT ColorA8B8G8R8
		{
			uint8 Red;
			uint8 Green;
			uint8 Blue;
			uint8 Alpha;
		};

		//! Red, Green, Blue single float
		struct YATOOLS_IMPORT ColorRsGsBs
		{
			float Blue;
			float Green;
			float Red;
		};

		//! Red, Green, Blue, Alpha single float
		struct YATOOLS_IMPORT ColorRsGsBsAs
		{
			float Alpha;
			float Blue;
			float Green;
			float Red;
		};

		//! Alpha, Red, Green, Blue single float
		struct YATOOLS_IMPORT ColorAsRsGsBs
		{
			float Blue;
			float Green;
			float Red;
			float Alpha;
		};

		//! Red, Green, Blue double float
		struct YATOOLS_IMPORT ColorRdGdBd
		{
			double Blue;
			double Green;
			double Red;
		};

		//! Red, Green, Blue, Alpha double float
		struct YATOOLS_IMPORT ColorRdGdBdAd
		{
			double Alpha;
			double Blue;
			double Green;
			double Red;
		};

		//! Alpha, Red, Green, Blue double float
		struct YATOOLS_IMPORT ColorAdRdGdBd
		{
			double Blue;
			double Green;
			double Red;
			double Alpha;
		};

#pragma pack( )

		/**
		* @fn ulong GetColorFormatPixelSize( ColorFormat format )
		* @brief カラーフォーマットピクセルサイズ取得
		* @param[in] format				カラーフォーマット
		* @returns						カラーフォーマットの1ピクセルあたりのバイト数
		* @retval 0						カラーフォーマットが無効です
		* @details
		*	指定されたカラーフォーマットの1ピクセルあたりのバイトサイズを取得します。
		*/
		extern "C" YATOOLS_IMPORT uint GetColorFormatPixelSize( ColorFormat format );

		/**
		* @}
		*/

	}
}
