#include <image/yatools.image.h>

namespace yatools { namespace image {


//-------------------------------------
// ����/�J��
//-------------------------------------
//-------------------------------------
// ����
//
ColorBuffer* ColorBuffer::Create( ColorFormat format, uint32 width, uint32 height )
{
	return NULL;
}

//-------------------------------------
// ����
//
ColorBuffer* ColorBuffer::Create( ColorFormat format, uint32 width, uint32 height, uintptr buffer, uint64 length )
{
	return NULL;
}

//-------------------------------------
// �J��
//
void ColorBuffer::Release( )
{
	if( this != NULL )
	{
		delete this;
	}
}


} }