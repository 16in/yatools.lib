#pragma once

#include "yatools.io.stream.h"


namespace yatools
{
	namespace io
	{

		/**
		* @class MemoryStream
		* @brief メモリストリーム
		* @details
		*	メモリ上のバッファに対する入出力ストリームです。	\n
		*	このストリームは確保済みの領域に対しての読み書きを行いますが、サイズを変更することはできません。
		*/
		class YATOOLS_IMPORT MemoryStream : Stream
		{
		public:
			/**
			* @name コンストラクタ/デストラクタ
			* @{
			*/
			/**
			* @brief コンストラクタ
			* @param[in] buffer			メモリの初期状態
			* @param[in] length			bufferの長さ
			* @details
			*	コンストラクタです。
			*/
			MemoryStream( uintptr buffer, int64 length )
			{
				m_Buffer = buffer;
				m_Length = length;
				m_Position = 0;
			}

			/**
			* @}
			*/
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
			virtual int64 Seek( int64 offset, SeekBase base );

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
			virtual int64 SetLength( int64 length )
			{
				return -1;
			}

			/**
			* @brief ストリームサイズ取得
			* @returns					ストリームサイズ
			* @details
			*	ストリームサイズを取得します。
			*/
			virtual int64 GetLength( void )
			{
				return m_Length;
			}

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
			virtual int32 Read( uintptr buffer, int32 size );

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
			virtual int32 Write( uintptr buffer, int32 size );

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

		protected:
			uintptr m_Buffer;			//!< 管理バッファ
			int64	m_Length;			//!< バッファ長
			int64	m_Position;			//!< 現在位置

		};

	}
}
