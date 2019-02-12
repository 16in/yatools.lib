#include <yatools/yatools.image.h>
#include <string.h>


namespace yatools { namespace image {


//-------------------------------------
// ����/�J��
//-------------------------------------
//-------------------------------------
// ����
//
ColorBuffer* ColorBuffer::Create( ColorFormat format, uint32 width, uint32 height )
{
	uint pixelSize = GetColorFormatPixelSize( format );
	if( pixelSize > 0 && width > 0 && height > 0 )
	{
		byte* colorBuffer = new byte[ pixelSize * width * height ];
		if( colorBuffer != NULL )
		{
			ColorBuffer* buffer = new ColorBuffer( );
			if( buffer == NULL )
			{
				delete[] colorBuffer;
			}
			else
			{
				buffer->m_Format = format;
				buffer->m_Width = width;
				buffer->m_Height = height;
				buffer->m_PixelSize = pixelSize;
				buffer->m_BufferSize = pixelSize * width * height;
				buffer->m_Buffer = (uintptr)colorBuffer;
				return buffer;
			}
		}
	}
	return NULL;
}

//-------------------------------------
// ����
//
ColorBuffer* ColorBuffer::Create( ColorFormat format, uint32 width, uint32 height, uintptr buffer, uint64 length )
{
	ColorBuffer* retval = NULL;
	if( buffer != NULL )
	{
		retval = Create( format, width, height );
		if( retval != NULL )
		{
			// �o�b�t�@�R�s�[�T�C�Y�����������ɑ�����
			uint64 bufferLength = length;
			if( bufferLength > retval->m_BufferSize )
			{
				bufferLength = retval->m_BufferSize;
			}
			memcpy( (void*)retval->m_Buffer, (void*)buffer, bufferLength );
		}
	}
	return retval;
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


//-------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
//-------------------------------------
//-------------------------------------
// �R���X�g���N�^
//
ColorBuffer::ColorBuffer( void )
{
	m_Format = Unknown;
	m_Width = m_Height = 0;
	m_Buffer = NULL;
	m_BufferSize = 0;
	m_PixelSize = 0;
}

//-------------------------------------
// �R�s�[�R���X�g���N�^
//
ColorBuffer::ColorBuffer( ColorBuffer& source )
{
	m_Format = source.m_Format;
	m_Width = source.m_Width;
	m_Height = source.m_Height;
	m_BufferSize = source.m_BufferSize;
	m_PixelSize = source.m_PixelSize;
	m_Buffer = (uintptr)new byte[ m_BufferSize ];
	if( m_Buffer != NULL )
	{
		memcpy( (void*)m_Buffer, (void*)source.m_Buffer, m_BufferSize );
	}
}

//-------------------------------------
// �f�X�g���N�^
//
ColorBuffer::~ColorBuffer( void )
{
	if( m_Buffer != NULL )
	{
		delete[] (byte*)m_Buffer;
		m_Buffer = NULL;
	}
}



} }