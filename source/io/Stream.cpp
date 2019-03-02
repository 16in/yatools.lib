#include "yatools/io/yatools.io.stream.h"

using namespace yatools;
#define YatIoStream yatools::io::Stream


//-------------------------------------
// シーク
//-------------------------------------
//-------------------------------------
// 現在位置設定
//
int64 YatIoStream::SetPosition( int64 pos )
{
	return Seek( pos, SeekBase::Head );
}

//-------------------------------------
// 現在位置取得
//
int64 YatIoStream::GetPosition( void )
{
	return Seek( 0, SeekBase::Current );
}


//-------------------------------------
// 読み書き
//-------------------------------------
//-------------------------------------
// 1バイト読み込み
//
int32 YatIoStream::ReadByte( void )
{
	byte byte;
	if( Read( (uintptr)byte, 1 ) != 0 )
	{
		return byte;
	}
	return -1;
}

//-------------------------------------
// 1バイト書き込み
//
bool YatIoStream::WriteByte( byte byte )
{
	return Write( (uintptr)&byte, 1 ) >= 0;
}
