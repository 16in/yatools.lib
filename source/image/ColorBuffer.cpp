#include <image/yatools.image.h>

namespace yatools { namespace image {


//-------------------------------------
// 生成/開放
//-------------------------------------
//-------------------------------------
// 生成
//
ColorBuffer* ColorBuffer::Create( ColorFormat format, uint32 width, uint32 height )
{
	return NULL;
}

//-------------------------------------
// 生成
//
ColorBuffer* ColorBuffer::Create( ColorFormat format, uint32 width, uint32 height, uintptr buffer, uint64 length )
{
	return NULL;
}

//-------------------------------------
// 開放
//
void ColorBuffer::Release( )
{
	if( this != NULL )
	{
		delete this;
	}
}


} }