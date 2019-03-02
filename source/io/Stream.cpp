#include "yatools/io/yatools.io.stream.h"

using namespace yatools;
#define YatIoStream yatools::io::Stream


//-------------------------------------
// �V�[�N
//-------------------------------------
//-------------------------------------
// ���݈ʒu�ݒ�
//
int64 YatIoStream::SetPosition( int64 pos )
{
	return Seek( pos, SeekBase::Head );
}

//-------------------------------------
// ���݈ʒu�擾
//
int64 YatIoStream::GetPosition( void )
{
	return Seek( 0, SeekBase::Current );
}


//-------------------------------------
// �ǂݏ���
//-------------------------------------
//-------------------------------------
// 1�o�C�g�ǂݍ���
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
// 1�o�C�g��������
//
bool YatIoStream::WriteByte( byte byte )
{
	return Write( (uintptr)&byte, 1 ) >= 0;
}
