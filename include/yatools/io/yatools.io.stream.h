#pragma once

#include "../yatools.type.h"


namespace yatools
{
	namespace io
	{

		/**
		* @class Stream
		* @brief 入出力ストリーム
		* @details
		*	入出力制御用のストリーム基底クラスです。
		*/
		class YATOOLS_IMPORT Stream
		{
		public:
			/**
			* @enum SeekBase
			* @brief シーク基準
			* @details
			*	シークの基準位置です。
			*/
			enum SeekBase
			{
				Head = 0,		/**< ストリーム先頭 */
				Current,		/**< 現在位置 */
				End				/**< 末端 */
			};

		public:
			/**
			* @name 位置関係
			* @{
			*/
			/**
			* @brief シーク
			* @param[in] offset			baseからのオフセット位置
			* @param[in] base			シーク基準
			* @returns					変更後の現在位置	\n
			*							変更後の位置がストリーム末端を超えていた場合は-1
			* @details
			*	ストリームの現在位置を指定の位置へ変更します。
			*/
			virtual int64 Seek( int64 offset, SeekBase base ) = 0;

			/**
			* @brief 現在位置設定
			* @param[in] pos			ストリーム先頭からの位置
			* @returns					設定された現在位置		\n
			*							posがストリーム末端を超えていた場合は-1
			* @details
			*	ストリームの現在位置を指定された場所へ設定します。
			*/
			virtual int64 SetPosition( int64 pos );

			/**
			* @brief 現在位置取得
			* @returns					ストリームの現在位置
			* @details
			*	ストリームの現在位置を取得します。
			*/
			virtual int64 GetPosition( void );

			/**
			* @brief ストリームサイズ設定
			* @param[in] length			新しく設定するストリームサイズ
			* @returns					変更後のストリームサイズ
			* @retval -1				変更に失敗
			* @details
			*	ストリームサイズを設定します。
			*/
			virtual int64 SetLength( int64 length ) = 0;

			/**
			* @brief ストリームサイズ取得
			* @returns					ストリームサイズ
			* @details
			*	ストリームサイズを取得します。
			*/
			virtual int64 GetLength( void ) = 0;

			/**
			* @}
			*/
			/**
			* @name 読み書き
			* @{
			*/
			/**
			* @brief 読み込み
			* @param[in,out] buffer				読み込みデータの格納先バッファ
			* @param[in] size					読み込むサイズ
			* @returns							bufferに格納されたデータサイズ
			* @retval -1						ストリーム末端
			* @details
			*	ストリームの現在位置から指定のバイト数を読み込みます。	\n
			*	少なくともbufferはsizeで指定したバイト数分、領域を確保済みでなくてはいけません。
			*/
			virtual int32 Read( uintptr buffer, int32 size ) = 0;

			/**
			* @brief 1byte読み込み
			* @returns							int32へキャストされたバイトデータ
			* @retval -1						読み込みに失敗
			* @details
			*	ストリームの現在位置から1バイト読み込みます。
			*/
			virtual int32 ReadByte( void );

			/**
			* @brief 書き込み
			* @param[in] buffer					書き込みデータ
			* @param[in] size					書き込むサイズ
			* @returns							実際に書き込まれたサイズ	\n
			*									失敗時は-1
			* @details
			*	ストリームの現在位置へbufferで指定された内容を書き込みます。
			*/
			virtual int32 Write( uintptr buffer, int32 size ) = 0;

			/**
			* @brief 1byte書き込み
			* @param[in] byte					書き込むバイトデータ
			* @retval true						成功
			* @retval false						失敗
			* @details
			*	ストリームの現在位置へ指定したバイトデータを書き込みます。
			*/
			virtual bool WriteByte( byte byte );

			/**
			* @}
			*/

		};

	}
}
