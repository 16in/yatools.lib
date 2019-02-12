#include <image/yatools.image.h>

namespace yatools { namespace image {


//-------------------------------------
// ê∂ê¨/äJï˙
//-------------------------------------
//-------------------------------------
// ê∂ê¨
//
ColorBuffer* ColorBuffer::Create( ColorFormat format, uint32 width, uint32 height )
{
	return NULL;
}

//-------------------------------------
// ê∂ê¨
//
ColorBuffer* ColorBuffer::Create( ColorFormat format, uint32 width, uint32 height, uintptr buffer, uint64 length )
{
	return NULL;
}

//-------------------------------------
// äJï˙
//
void ColorBuffer::Release( )
{
	if( this != NULL )
	{
		delete this;
	}
}


} }