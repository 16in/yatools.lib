#pragma once

#include "../yatools.image.colorbuffer.h"


namespace yatools
{
	namespace image
	{
		namespace file
		{

			/**
			* @struct TgaHeader
			* @brief TGAファイルヘッダ
			* @details
			*	TGAファイルヘッダ構造です。
			*/
#pragma pack( 1 )
			struct TgaHeader
			{
				uint8	IdFieldLength;				//!< IDフィールド長
				uint8	ColorMapType;				//!< カラーマップタイプ
				uint8	ImageType;					//!< 画像タイプ
				uint16	ColorMapFirstEntryIndex;	//!< カラーマップ最初のエントリーまでのインデックス
				uint16	ColorMapLength;				//!< カラーマップ長
				uint8	ColorMapEntrySize;			//!< カラーマップ要素サイズ(bpp)
				uint16	XOrigin;					//!< X座標
				uint16	YOrigin;					//!< Y座標
				uint16	Width;						//!< 横幅
				uint16	Height;						//!< 縦幅
				uint8	PixelDepth;					//!< ピクセル深度
				uint8	Attribute : 4;				//!< 属性
				uint8	Horizontal : 1;				//!< 横方向
				uint8	Vertical : 1;				//!< 縦方向
				uint8	reserve : 2;
			};
#pragma pack( )

			/**
			* @struct TgaFooter
			* @brief TGAファイルフッター
			* @details
			*	TGAファイルフッター構造です。
			*/
#pragma pack( 1 )
			struct TgaFooter
			{
				uint32	ExtensionOffset;			//!< TgaExtensionへのオフセット
				uint32	DeveloperAreaOffset;		//!< DeveloperAreaへのオフセット
				char	Signature[ 18 ];			//!< 'TRUEVISION-XFILE.\0'
			};
#pragma pack( )

			/**
			* @struct TgaExtension
			* @brief TGA拡張領域
			* @details
			*	TGAファイルの拡張データ構造です。
			*/
#pragma pack( 1 )
			struct TgaExtension
			{
				uint16	ExtensionSize;				//!< 常に495
				char	AuthorName[ 41 ];			//!< 製作者名
				char	AuthorComment[ 324 ];		//!< コメント
				char	DateTimeStamp[ 12 ];		//!< タイムスタンプ
				char	JobID[ 41 ];				//!< ジョブID
				char	JobTime[ 6 ];				//!< 時分秒での作成時刻
				char	SoftwareID[ 41 ];			//!< ソフトウェアID
				char	SoftwareVersion[ 3 ];		//!< ソフトウェアバージョン
				uint32	KeyColor;					//!< キーカラー
				float	PixelAspectRatio;			//!< ピクセルアスペクト比
				float	GammaValue;					//!< ガンマ値
				uint32	ColorCorrectionOffset;		//!< カラーコレクションオフセット
				uint32  PostageStampOffset;
				uint32	ScanLineOffset;				//!< スキャンラインオフセット
				uint8	AttributesType;				//!< 属性タイプ
			};
#pragma pack( )

			/**
			* @class TgaFile
			* @brief TGAファイル
			* @details
			*	TGAファイルクラスです。
			*/
			class YATOOLS_IMPORT TgaFile
			{
			public:
				/**
				* @name ファイルバイナリ
				* @{
				*/


				/**
				* @}
				*/


			};

		}
	}
}
