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


//-------------------------------------
// �s�N�Z������
//-------------------------------------
//-------------------------------------
// �s�N�Z���T�C�Y�擾
//
uint64 ColorBuffer::GetPixelSize( void )
{
	return m_PixelSize;
}

//-------------------------------------
// �s�N�Z���ݒ�
//
bool ColorBuffer::SetPixel( uint32 x, uint32 y, uintptr pixel, uint64 length )
{
	if( m_PixelSize <= length )
	{
		uintptr address = GetPixelAddress( x, y );
		if( address != NULL && (address + m_PixelSize) < (m_Buffer + m_BufferSize) )
		{
			memcpy( (void*)address, (void*)pixel, m_PixelSize );
			return true;
		}
	}
	return false;
}

//-------------------------------------
// �s�N�Z���ݒ�
//
bool ColorBuffer::SetPixels( uint32 x, uint32 y, uintptr pixels, uint64 length )
{
	uintptr address = GetPixelAddress( x, y );
	if( address != NULL )
	{
		uint64 count = length / m_PixelSize;
		if( count > 0 && address + (count * m_PixelSize) < (m_Buffer + m_BufferSize) )
		{
			memcpy( (void*)address, (void*)pixels, count * m_PixelSize );
			return true;
		}
	}
	return false;
}

//-------------------------------------
// �s�N�Z���A�h���X�擾
//
uintptr ColorBuffer::GetPixelAddress( uint32 x, uint32 y )
{
	if( x < m_Width && y < m_Height )
	{
		return m_Buffer + ((x + (m_Width * y)) * m_PixelSize);
	}
	return NULL;
}

//-------------------------------------
// �s�N�Z���u���b�N�ݒ�
//
bool ColorBuffer::SetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height, uintptr blocks, uint64 length )
{
	uintptr address = GetPixelAddress( x, y );
	if( address != NULL )
	{
		if( x + width < m_Width && y + height < m_Height && width * height * m_PixelSize <= length )
		{
			uint64 rowlength = m_Width * m_PixelSize;
			if( address + (rowlength * height) + (width * m_PixelSize) < m_Buffer + m_BufferSize )
			{
				uint64 blockrowlength = width * m_PixelSize;
				for( uint32 i = 0; i < height; i++ )
				{
					address = GetPixelAddress( x, y + i );
					memcpy( (void*)address, (void*)blocks, blockrowlength );
					blocks += blockrowlength;
				}
				return true;
			}
		}
	}
	return false;
}

//-------------------------------------
// �s�N�Z���u���b�N�ݒ�
//
bool ColorBuffer::SetPixelBlock( uint32 x, uint32 y, ColorBuffer* blockBuffer )
{
	if( blockBuffer->m_Format != m_Format )
	{
		return false;
	}
	return SetPixelBlock( x, y, m_Width, m_Height, m_Buffer, m_BufferSize );
}

//-------------------------------------
// �s�N�Z���u���b�N�擾
//
ColorBuffer* ColorBuffer::GetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height )
{
	if( x + width < m_Width && y + height < m_Height )
	{
		ColorBuffer* block = Create( m_Format, width, height );

	}
	return NULL;
}



} }