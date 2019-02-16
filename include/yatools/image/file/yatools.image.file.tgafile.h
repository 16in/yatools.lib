#pragma once

#include "../yatools.image.colorbuffer.h"


namespace yatools
{
	namespace image
	{
		namespace file
		{


			/**
			* @enum TgaImageType
			* @brief TGAイメージタイプ列挙体
			* @details
			*	TGAのイメージタイプ列挙体です。	\n
			*	TgaHeader.ImageTypeが取りうる値です。
			*/
			enum TgaImageType
			{
				TGA_NO_IMAGE = 0,					//!< 画像なし
				TGA_COLOR_MAP = 1,					//!< カラーマップ
				TGA_TRUE_COLOR = 2,					//!< フルカラー
				TGA_GRAY_SCALE = 3,					//!< グレースケール
				TGA_COLOR_MAP_RLE = 9,				//!< カラーマップ ランレングス
				TGA_TRUE_COLOR_RLE = 10,			//!< フルカラー ランレングス
				TGA_GRAY_SCALE_RLE = 11,			//!< グレースケール ランレングス
			};

			/**
			* @enum TgaImageDirection
			* @brief TGAイメージ格納方向
			* @details
			*	TGAのイメージビットがどの方向で格納されているかを表します。	\n
			*	TgaHeader.Descriptor.Directionが取りうる値です。
			*/
			enum TgaImageDirection
			{
				TGA_IMAGE_LEFT_BOTTOM = 0,			//!< 左下→右上
				TGA_IMAGE_RIGHT_BOTTOM = 1,			//!< 右下→左上
				TGA_IMAGE_LEFT_TOP = 2,				//!< 左上→右下
				TGA_IMAGE_RIGHT_TOP = 3,			//!< 右上→左下
			};


#pragma pack( 1 )

			/**
			* @struct TgaColorMapSpecification
			* @brief カラーマップ仕様構造体
			* @details
			*	TGAカラーマップに関する仕様情報です。
			*/
			struct TgaColorMapSpecification
			{
				uint16	FirstEntryIndex;			//!< カラーマップ最初のエントリーまでのインデックス
				uint16	Length;						//!< カラーマップ長
				uint8	EntrySize;					//!< カラーマップ要素サイズ(bpp)
			};

			/**
			* @struct TgaColorMapSpecification
			* @brief 画像仕様構造体
			* @details
			*	TGA画像に関する仕様情報です。
			*/
			struct TgaImageSpecification
			{
				uint16	XOrigin;					//!< X座標
				uint16	YOrigin;					//!< Y座標
				uint16	Width;						//!< 横幅
				uint16	Height;						//!< 縦幅
				uint8	PixelDepth;					//!< ピクセル深度

				struct
				{
					uint8	AlphaDepth : 4;			//!< アルファ深度情報
					uint8	Direction : 2;			//!< 向き情報
					uint8	unuse : 2;
				} Descriptor;
			};

			/**
			* @struct TgaHeader
			* @brief TGAファイルヘッダ
			* @details
			*	TGAファイルヘッダ構造です。
			*/
			struct TgaHeader
			{
				uint8	IdFieldLength;				//!< IDフィールド長
				uint8	ColorMapType;				//!< カラーマップタイプ
				uint8	ImageType;					//!< 画像タイプ

				//! カラーマップ仕様
				TgaColorMapSpecification ColorMapSpecification;

				//! 画像仕様
				TgaImageSpecification ImageSpecification;
			};

			/**
			* @struct TgaFooter
			* @brief TGAファイルフッター
			* @details
			*	TGAファイルフッター構造です。
			*/
			struct TgaFooter
			{
				uint32	ExtensionOffset;			//!< TgaExtensionへのオフセット
				uint32	DeveloperAreaOffset;		//!< DeveloperAreaへのオフセット
				char	Signature[ 18 ];			//!< 'TRUEVISION-XFILE.\0'
			};

			/**
			* @struct TgaExtension
			* @brief TGA拡張領域
			* @details
			*	TGAファイルの拡張データ構造です。
			*/
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
				* @name バイナリ操作
				* @{
				*/
				/**
				* @brief ファイルヘッダ取得
				* @param[in] buffer					TGAファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							TGAファイルヘッダ構造体
				* @details
				*	ファイルヘッダを取得します。
				*/
				static TgaHeader* GetHeader( uintptr buffer, uint64 length );

				/**
				* @brief ファイルフッター取得
				* @param[in] buffer					TGAファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							TGAファイルフッター構造体
				* @retval NULL						存在しない
				* @details
				*	ファイルフッターを取得します。
				*/
				static TgaFooter* GetFooter( uintptr buffer, uint64 length );

				/**
				* @brief ImageIDフィールド取得
				* @param[in] buffer					TGAファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							ImageIDフィールドの先頭ポインタ
				* @retval NULL						存在しない
				* @details
				*	イメージIDフィールドを取得します。
				*/
				static uintptr GetImageIdField( uintptr buffer, uint64 length );

				/**
				* @brief カラーマップフィールド取得
				* @param[in] buffer					TGAファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							カラーマップフィールドの先頭ポインタ
				* @retval NULL						存在しない
				* @details
				*	カラーマップフィールドを取得します。		\n
				*	カラーマップの諸情報はヘッダを参照してください。
				*/
				static uintptr GetColorMapField( uintptr buffer, uint64 length );

				/**
				* @brief 画像フィールド取得
				* @param[in] buffer					TGAファイルが格納済みのメモリ領域
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
				* @param[in] buffer					TGAファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							生成されたカラーバッファ
				* @retval NULL						生成に失敗
				* @details
				*	画像フィールドをヘッダ情報に従ってカラーバッファ化します。	\n
				*	圧縮形式の場合、この関数は失敗します。
				*/
				static ColorBuffer* GetColorBuffer( uintptr buffer, uint64 length );

				/**
				* @brief 拡張情報フィールド取得
				* @param[in] buffer					TGAファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							拡張情報フィールドの先頭ポインタ
				* @retval NULL						存在しない
				* @details
				*	拡張情報フィールドを取得します。
				*/
				static TgaExtension* GetExtensionField( uintptr buffer, uint64 length );

				/**
				* @brief 開発者領域フィールド取得
				* @param[in] buffer					TGAファイルが格納済みのメモリ領域
				* @param[in] length					bufferサイズ
				* @returns							開発者領域フィールドの先頭ポインタ
				* @retval NULL						存在しない
				* @details
				*	開発者領域フィールドを取得します。
				*/
				static uintptr GetDeveloperAreaField( uintptr buffer, uint64 length );

				/**
				* @brief TGAファイル書き出し
				* @param[in] colorBuffer			TGAファイルとして書き出すカラーバッファ
				* @param[in, out] buffer			書き出し先メモリ領域	\n
				*									NULLの場合は戻り値が必要な領域サイズを返します。
				* @param[in] length					bufferに格納可能なバイト数
				* @returns							bufferに書き出されたバイト数		\n
				*									bufferがNULLの場合は必要なバイト数
				* @retval 0							colorBufferがTGAファイルに書き出し可能な形式ではない
				* @details
				*	カラーバッファをTGAファイルとしてメモリ領域に書き出します。		\n
				*	書き出し可能なカラーバッファのフォーマットは次のとおりです。	\n
				*	・ColorFormatR8G8B8		\n
				*	・ColorFormatA8R8G8B8	\n
				*	・ColorFormatA1R5G5B5	\n
				*	・ColorFormatGray8		\n
				*	\n
				*	bufferがNULLの場合、ColorBufferの書き出しに必要なバイト数を返します。
				*/
				static uint64 WriteFileBuffer( ColorBuffer* colorBuffer, uintptr buffer, uint64 length );

				/**
				* @}
				*/


			};

		}
	}
}
