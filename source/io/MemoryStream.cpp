#include "yatools/io/yatools.io.memorystream.h"
#include <string.h>

using namespace yatools;
#define YatIoStream yatools::io::MemoryStream


//-------------------------------------
// シーク
//-------------------------------------
//-------------------------------------
// 現在位置設定
//
int64 YatIoStream::Seek( int64 offset, SeekBase base )
{
	int64 basePos[ 3 ] = { 0, m_Position, m_Length };
	int64 pos = basePos[ base ] + offset;
	if( pos < 0 ) { pos = 0; }
	if( pos >= m_Length )
	{
		return -1;
	}
	return m_Position = pos;
}

//-------------------------------------
// 現在位置取得
//
int64 YatIoStream::GetPosition( void )
{
	return (int64)m_Position;
}


//-------------------------------------
// 読み書き
//-------------------------------------
//-------------------------------------
// 読み込み
//
int32 YatIoStream::Read( uintptr buffer, int32 size )
{
	if( m_Position < m_Length )
	{
		if( m_Length - m_Position < size )
		{
			size = m_Length - m_Position;
		}
		memcpy( (void*)buffer, (void*)(m_Buffer + m_Position), size );
		m_Position += size;
		return size;
	}
	return -1;
}

//-------------------------------------
// 書き込み
//
int32 YatIoStream::Write( uintptr buffer, int32 size )
{
	if( m_Position + size <= m_Length )
	{
		memcpy( (void*)(m_Buffer + m_Position), (void*)buffer, size );
		m_Position += size;
		return size;
	}
	return -1;
}

//-------------------------------------
// 1バイト読み込み
//
int32 YatIoStream::ReadByte( void )
{
	if( m_Position + 1 <= m_Length )
	{
		return ((uint8*)m_Buffer)[ m_Position++ ];
	}
	return -1;
}

//-------------------------------------
// 1バイト書き込み
//
bool YatIoStream::WriteByte( byte byte )
{
	if( m_Position + 1 <= m_Length )
	{
		((uint8*)m_Buffer)[ m_Position++ ] = byte;
	}
	return false;
}
