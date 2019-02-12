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
			R5G6B5,			//!< Red 5bit, Green 6bit, Blue 5bit
			R4G4B4,			//!< Red 4bit, Green 4bit, Blue 4bit
			R4G4B4A4,		//!< Red 4bit, Green 4bit, Blue 4bit, Alpha 4bit
			A4R4G4B4,		//!< Alpha 4bit, Red 4bit, Green 4bit, Blue 4bit
			R8G8B8,			//!< Red 8bit, Green 8bit, Blue 8bit
			R8G8B8A8,		//!< Red 8bit, Green 8bit, Blue 8bit, Alpha 8bit
			A8R8G8B8,		//!< Alpha 8bit, Red 8bit, Green 8bit, Blue 8bit

			RsGsBs,			//! Red, Green, Blue single float
			RsGsBsAs,		//! Red, Green, Blue, Alpha single float
			AsRsGsBs,		//! Alpha, Red, Green, Blue single float
			RdGdBd,			//! Red, Green, Blue double float
			RdGdBdAd,		//! Red, Green, Blue, Alpha double float
			AdRdGdBd,		//! Alpha, Red, Green, Blue double float

		};


#pragma pack( 1 )

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
