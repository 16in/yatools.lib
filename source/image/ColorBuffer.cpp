#include <yatools/yatools.image.h>
#include <string.h>


namespace yatools { namespace image {


//-------------------------------------
// 生成/開放
//-------------------------------------
//-------------------------------------
// 生成
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
// 生成
//
ColorBuffer* ColorBuffer::Create( ColorFormat format, uint32 width, uint32 height, uintptr buffer, uint64 length )
{
	ColorBuffer* retval = NULL;
	if( buffer != NULL )
	{
		retval = Create( format, width, height );
		if( retval != NULL )
		{
			// バッファコピーサイズを小さい方に揃える
			uint64 bufferLength = length;
			if( bufferLength > retval->m_BufferSize )
			{
				bufferLength = retval->m_BufferSize;
			}
			memcpy( (void*)retval->m_Buffer, (void*)buffer, (size_t)bufferLength );
		}
	}
	return retval;
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

//-------------------------------------
// コピー
//
ColorBuffer* ColorBuffer::Copy( void )
{
	return new ColorBuffer( *this );
}

//-------------------------------------
// フォーマットコンバート
//
ColorBuffer* ColorBuffer::Convert( ColorFormat format )
{
	ColorBuffer* buffer = Create( format, m_Width, m_Height );
	for( uint64 i = 0; i < m_Width * m_Height; i++ )
	{
		double red, green, blue, alpha;
		GetPixelColorIndex( i, red, green, blue, alpha );
		buffer->SetPixelColorIndex( i, red, green, blue, alpha );
	}
	return buffer;
}


//-------------------------------------
// コンストラクタ/デストラクタ
//-------------------------------------
//-------------------------------------
// コンストラクタ
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
// コピーコンストラクタ
//
ColorBuffer::ColorBuffer( ColorBuffer& source )
{
	m_Format = source.m_Format;
	m_Width = source.m_Width;
	m_Height = source.m_Height;
	m_BufferSize = source.m_BufferSize;
	m_PixelSize = source.m_PixelSize;
	m_Buffer = (uintptr)new byte[ (unsigned int)m_BufferSize ];
	if( m_Buffer != NULL )
	{
		memcpy( (void*)m_Buffer, (void*)source.m_Buffer, (size_t)m_BufferSize );
	}
}

//-------------------------------------
// デストラクタ
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
// 情報取得
//-------------------------------------
//-------------------------------------
// 横幅取得
//
uint32 ColorBuffer::GetWidth( void )
{
	return m_Width;
}

//-------------------------------------
// 縦幅取得
//
uint32 ColorBuffer::GetHeight( void )
{
	return m_Height;
}

//-------------------------------------
// カラーフォーマット取得
//
ColorFormat ColorBuffer::GetFormat( void )
{
	return m_Format;
}

//-------------------------------------
// ピクセルサイズ取得
//
uint64 ColorBuffer::GetPixelSize( void )
{
	return m_PixelSize;
}

//-------------------------------------
// 総ピクセル数取得
//
uint64 ColorBuffer::GetPixelCount( void )
{
	return m_Width * m_Height;
}


//-------------------------------------
// ピクセル操作
//-------------------------------------
//-------------------------------------
// ピクセル設定
//
bool ColorBuffer::SetPixel( uint32 x, uint32 y, uintptr pixel, uint64 length )
{
	if( m_PixelSize <= length )
	{
		uintptr address = GetPixelAddress( x, y );
		if( address != NULL && (address + m_PixelSize) <= (m_Buffer + m_BufferSize) )
		{
			memcpy( (void*)address, (void*)pixel, (size_t)m_PixelSize );
			return true;
		}
	}
	return false;
}

//-------------------------------------
// ピクセルカラー設定
//
bool ColorBuffer::SetPixelColor( uint32 x, uint32 y, double red, double green, double blue, double alpha )
{
	return SetPixelColorIndex( x + (y * m_Width), red, green, blue, alpha );
}

//-------------------------------------
// ピクセルカラー設定
//
bool ColorBuffer::SetPixelColorIndex( uint64 index, double red, double green, double blue, double alpha )
{
	uintptr address = m_Buffer + (uintptr)(index * m_PixelSize);
	if( address != NULL && (address + m_PixelSize) <= (m_Buffer + m_BufferSize) )
	{
		switch( m_Format )
		{
		case ColorFormat::Gray8: case ColorFormat::Gray16:
			{
				double gray = (red * 0.2126 + green * 0.7152 + blue * 0.0722);
				if( gray < 0 ) { gray = 0; }
				else if( gray > 1 ) { gray = 1; }
				if( m_Format == ColorFormat::Gray8 )
				{
					((ColorGray8*)(address))->Gray = (uint8)(gray * 0xff);
				}
				else if( m_Format == ColorFormat::Gray16 )
				{
					((ColorGray16*)(address))->Gray = (uint16)(gray * 0xffff);
				}
			}
			break;
		case ColorFormat::R5G5B5:
			((ColorR5G5B5*)(address))->SetRed( (uint8)(red * 0x1f) );
			((ColorR5G5B5*)(address))->SetGreen( (uint8)(green * 0x1f) );
			((ColorR5G5B5*)(address))->SetBlue( (uint8)(blue * 0x1f) );
			break;
		case ColorFormat::B5G5R5:
			((ColorB5G5R5*)(address))->SetRed( (uint8)(red * 0x1f) );
			((ColorB5G5R5*)(address))->SetGreen( (uint8)(green * 0x1f) );
			((ColorB5G5R5*)(address))->SetBlue( (uint8)(blue * 0x1f) );
			break;
		case ColorFormat::R5G6B5:
			((ColorR5G6B5*)(address))->SetRed( (uint8)(red * 0x1f) );
			((ColorR5G6B5*)(address))->SetGreen( (uint8)(green * 0x3f) );
			((ColorR5G6B5*)(address))->SetBlue( (uint8)(blue * 0x1f) );
			break;
		case ColorFormat::B5G6R5:
			((ColorB5G6R5*)(address))->SetRed( (uint8)(red * 0x1f) );
			((ColorB5G6R5*)(address))->SetGreen( (uint8)(green * 0x3f) );
			((ColorB5G6R5*)(address))->SetBlue( (uint8)(blue * 0x1f) );
			break;
		case ColorFormat::A1R5G5B5:
			((ColorA1R5G5B5*)(address))->SetAlpha( (uint8)(alpha >= 0.5 ? 1 : 0) );
			((ColorA1R5G5B5*)(address))->SetRed( (uint8)(red * 0x1f) );
			((ColorA1R5G5B5*)(address))->SetGreen( (uint8)(green * 0x1f) );
			((ColorA1R5G5B5*)(address))->SetBlue( (uint8)(blue * 0x1f) );
			break;
		case ColorFormat::A1B5G5R5:
			((ColorA1B5G5R5*)(address))->SetAlpha( (uint8)(alpha >= 0.5 ? 1 : 0) );
			((ColorA1B5G5R5*)(address))->SetRed( (uint8)(red * 0x1f) );
			((ColorA1B5G5R5*)(address))->SetGreen( (uint8)(green * 0x1f) );
			((ColorA1B5G5R5*)(address))->SetBlue( (uint8)(blue * 0x1f) );
			break;
		case ColorFormat::R5G5B5A1:
			((ColorR5G5B5A1*)(address))->SetAlpha( (uint8)(alpha >= 0.5 ? 1 : 0) );
			((ColorR5G5B5A1*)(address))->SetRed( (uint8)(red * 0x1f) );
			((ColorR5G5B5A1*)(address))->SetGreen( (uint8)(green * 0x1f) );
			((ColorR5G5B5A1*)(address))->SetBlue( (uint8)(blue * 0x1f) );
			break;
		case ColorFormat::B5G5R5A1:
			((ColorB5G5R5A1*)(address))->SetAlpha( (uint8)(alpha >= 0.5 ? 1 : 0) );
			((ColorB5G5R5A1*)(address))->SetRed( (uint8)(red * 0x1f) );
			((ColorB5G5R5A1*)(address))->SetGreen( (uint8)(green * 0x1f) );
			((ColorB5G5R5A1*)(address))->SetBlue( (uint8)(blue * 0x1f) );
			break;
		case ColorFormat::R4G4B4:
			((ColorR4G4B4*)(address))->Red = (uint8)(red * 0x0f);
			((ColorR4G4B4*)(address))->Green = (uint8)(green * 0x0f);
			((ColorR4G4B4*)(address))->Blue = (uint8)(blue * 0x0f);
			break;
		case ColorFormat::B4G4R4:
			((ColorB4G4R4*)(address))->Red = (uint8)(red * 0x0f);
			((ColorB4G4R4*)(address))->Green = (uint8)(green * 0x0f);
			((ColorB4G4R4*)(address))->Blue = (uint8)(blue * 0x0f);
			break;
		case ColorFormat::R4G4B4A4:
			((ColorR4G4B4A4*)(address))->Alpha = (uint8)(alpha * 0x0f);
			((ColorR4G4B4A4*)(address))->Red = (uint8)(red * 0x0f);
			((ColorR4G4B4A4*)(address))->Green = (uint8)(green * 0x0f);
			((ColorR4G4B4A4*)(address))->Blue = (uint8)(blue * 0x0f);
			break;
		case ColorFormat::B4G4R4A4:
			((ColorB4G4R4A4*)(address))->Alpha = (uint8)(alpha * 0x0f);
			((ColorB4G4R4A4*)(address))->Red = (uint8)(red * 0x0f);
			((ColorB4G4R4A4*)(address))->Green = (uint8)(green * 0x0f);
			((ColorB4G4R4A4*)(address))->Blue = (uint8)(blue * 0x0f);
			break;
		case ColorFormat::A4R4G4B4:
			((ColorA4R4G4B4*)(address))->Alpha = (uint8)(alpha * 0x0f);
			((ColorA4R4G4B4*)(address))->Red = (uint8)(red * 0x0f);
			((ColorA4R4G4B4*)(address))->Green = (uint8)(green * 0x0f);
			((ColorA4R4G4B4*)(address))->Blue = (uint8)(blue * 0x0f);
			break;
		case ColorFormat::A4B4G4R4:
			((ColorA4B4G4R4*)(address))->Alpha = (uint8)(alpha * 0x0f);
			((ColorA4B4G4R4*)(address))->Red = (uint8)(red * 0x0f);
			((ColorA4B4G4R4*)(address))->Green = (uint8)(green * 0x0f);
			((ColorA4B4G4R4*)(address))->Blue = (uint8)(blue * 0x0f);
			break;
		case ColorFormat::R8G8B8:
			((ColorR8G8B8*)(address))->Red = (uint8)(red * 0xff);
			((ColorR8G8B8*)(address))->Green = (uint8)(green * 0xff);
			((ColorR8G8B8*)(address))->Blue = (uint8)(blue * 0xff);
			break;
		case ColorFormat::B8G8R8:
			((ColorB8G8R8*)(address))->Red = (uint8)(red * 0xff);
			((ColorB8G8R8*)(address))->Green = (uint8)(green * 0xff);
			((ColorB8G8R8*)(address))->Blue = (uint8)(blue * 0xff);
			break;
		case ColorFormat::R8G8B8A8:
			((ColorR8G8B8A8*)(address))->Alpha = (uint8)(alpha * 0xff);
			((ColorR8G8B8A8*)(address))->Red = (uint8)(red * 0xff);
			((ColorR8G8B8A8*)(address))->Green = (uint8)(green * 0xff);
			((ColorR8G8B8A8*)(address))->Blue = (uint8)(blue * 0xff);
			break;
		case ColorFormat::B8G8R8A8:
			((ColorB8G8R8A8*)(address))->Alpha = (uint8)(alpha * 0xff);
			((ColorB8G8R8A8*)(address))->Red = (uint8)(red * 0xff);
			((ColorB8G8R8A8*)(address))->Green = (uint8)(green * 0xff);
			((ColorB8G8R8A8*)(address))->Blue = (uint8)(blue * 0xff);
			break;
		case ColorFormat::A8R8G8B8:
			((ColorA8R8G8B8*)(address))->Alpha = (uint8)(alpha * 0xff);
			((ColorA8R8G8B8*)(address))->Red = (uint8)(red * 0xff);
			((ColorA8R8G8B8*)(address))->Green = (uint8)(green * 0xff);
			((ColorA8R8G8B8*)(address))->Blue = (uint8)(blue * 0xff);
			break;
		case ColorFormat::A8B8G8R8:
			((ColorA8B8G8R8*)(address))->Alpha = (uint8)(alpha * 0xff);
			((ColorA8B8G8R8*)(address))->Red = (uint8)(red * 0xff);
			((ColorA8B8G8R8*)(address))->Green = (uint8)(green * 0xff);
			((ColorA8B8G8R8*)(address))->Blue = (uint8)(blue * 0xff);
			break;
		case ColorFormat::AsRsGsBs:
			((ColorAsRsGsBs*)(address))->Alpha = (float)alpha;
			((ColorAsRsGsBs*)(address))->Red = (float)red;
			((ColorAsRsGsBs*)(address))->Green = (float)green;
			((ColorAsRsGsBs*)(address))->Blue = (float)blue;
			break;
		case ColorFormat::RsGsBsAs:
			((ColorRsGsBsAs*)(address))->Alpha = (float)alpha;
			((ColorRsGsBsAs*)(address))->Red = (float)red;
			((ColorRsGsBsAs*)(address))->Green = (float)green;
			((ColorRsGsBsAs*)(address))->Blue = (float)blue;
			break;
		case ColorFormat::RsGsBs:
			((ColorRsGsBs*)(address))->Red = (float)red;
			((ColorRsGsBs*)(address))->Green = (float)green;
			((ColorRsGsBs*)(address))->Blue = (float)blue;
			break;
		case ColorFormat::AdRdGdBd:
			((ColorAdRdGdBd*)(address))->Alpha = alpha;
			((ColorAdRdGdBd*)(address))->Red = red;
			((ColorAdRdGdBd*)(address))->Green = green;
			((ColorAdRdGdBd*)(address))->Blue = blue;
			break;
		case ColorFormat::RdGdBdAd:
			((ColorRdGdBdAd*)(address))->Alpha = alpha;
			((ColorRdGdBdAd*)(address))->Red = red;
			((ColorRdGdBdAd*)(address))->Green = green;
			((ColorRdGdBdAd*)(address))->Blue = blue;
			break;
		case ColorFormat::RdGdBd:
			((ColorRdGdBd*)(address))->Red = red;
			((ColorRdGdBd*)(address))->Green = green;
			((ColorRdGdBd*)(address))->Blue = blue;
			break;
		}
		return true;
	}
	return false;
}

//-------------------------------------
// ピクセル設定
//
bool ColorBuffer::SetPixels( uint32 x, uint32 y, uintptr pixels, uint64 length )
{
	uintptr address = GetPixelAddress( x, y );
	if( address != NULL )
	{
		uint64 count = length / m_PixelSize;
		if( count > 0 && address + (count * m_PixelSize) <= (m_Buffer + m_BufferSize) )
		{
			memcpy( (void*)address, (void*)pixels, (size_t)(count * m_PixelSize) );
			return true;
		}
	}
	return false;
}

//-------------------------------------
// ピクセルアドレス取得
//
uintptr ColorBuffer::GetPixelAddress( uint32 x, uint32 y )
{
	if( x < m_Width && y < m_Height )
	{
		return m_Buffer + (uintptr)((x + (m_Width * y)) * m_PixelSize);
	}
	return NULL;
}

//-------------------------------------
// ピクセルカラー取得
//
bool ColorBuffer::GetPixelColor( uint32 x, uint32 y, double& red, double& green, double& blue, double& alpha )
{
	return GetPixelColorIndex( x + (y * m_Width), red, green, blue, alpha );
}

//-------------------------------------
// ピクセルカラー取得
//
bool ColorBuffer::GetPixelColorIndex( uint64 index, double& red, double& green, double& blue, double& alpha )
{
	if( index < m_Width * m_Height )
	{
		uintptr address = m_Buffer + (uintptr)(index * m_PixelSize);
		switch( m_Format )
		{
		case ColorFormat::Gray8:
			red = green = blue = ((ColorGray8*)(address))->Gray / (double)0xff;
			break;
		case ColorFormat::Gray16:
			red = green = blue = ((ColorGray16*)(address))->Gray / (double)0xffff;
			break;
		case ColorFormat::R5G5B5:
			red = ((ColorR5G5B5*)(address))->GetRed( ) / (double)0x1f;
			green = ((ColorR5G5B5*)(address))->GetGreen( ) / (double)0x1f;
			blue = ((ColorR5G5B5*)(address))->GetBlue( ) / (double)0x1f;
			break;
		case ColorFormat::B5G5R5:
			red = ((ColorB5G5R5*)(address))->GetRed( ) / (double)0x1f;
			green = ((ColorB5G5R5*)(address))->GetGreen( ) / (double)0x1f;
			blue = ((ColorB5G5R5*)(address))->GetBlue( ) / (double)0x1f;
			break;
		case ColorFormat::R5G6B5:
			red = ((ColorR5G6B5*)(address))->GetRed( ) / (double)0x1f;
			green = ((ColorR5G6B5*)(address))->GetGreen( ) / (double)0x3f;
			blue = ((ColorR5G6B5*)(address))->GetBlue( ) / (double)0x1f;
			break;
		case ColorFormat::B5G6R5:
			red = ((ColorB5G6R5*)(address))->GetRed( ) / (double)0x1f;
			green = ((ColorB5G6R5*)(address))->GetGreen( ) / (double)0x3f;
			blue = ((ColorB5G6R5*)(address))->GetBlue( ) / (double)0x1f;
			break;
		case ColorFormat::A1R5G5B5:
			alpha = (double)((ColorA1R5G5B5*)(address))->GetAlpha();
			red = ((ColorA1R5G5B5*)(address))->GetRed( ) / (double)0x1f;
			green = ((ColorA1R5G5B5*)(address))->GetGreen( ) / (double)0x1f;
			blue = ((ColorA1R5G5B5*)(address))->GetBlue( ) / (double)0x1f;
			break;
		case ColorFormat::A1B5G5R5:
			alpha = (double)((ColorA1B5G5R5*)(address))->GetAlpha( );
			red = ((ColorA1B5G5R5*)(address))->GetRed( ) / (double)0x1f;
			green = ((ColorA1B5G5R5*)(address))->GetGreen( ) / (double)0x1f;
			blue = ((ColorA1B5G5R5*)(address))->GetBlue( ) / (double)0x1f;
			break;
		case ColorFormat::R5G5B5A1:
			alpha = (double)((ColorR5G5B5A1*)(address))->GetAlpha( );
			red = ((ColorR5G5B5A1*)(address))->GetRed( ) / (double)0x1f;
			green = ((ColorR5G5B5A1*)(address))->GetGreen( ) / (double)0x1f;
			blue = ((ColorR5G5B5A1*)(address))->GetBlue( ) / (double)0x1f;
			break;
		case ColorFormat::B5G5R5A1:
			alpha = (double)((ColorB5G5R5A1*)(address))->GetAlpha( );
			red = ((ColorB5G5R5A1*)(address))->GetRed( ) / (double)0x1f;
			green = ((ColorB5G5R5A1*)(address))->GetGreen() / (double)0x1f;
			blue = ((ColorB5G5R5A1*)(address))->GetBlue( ) / (double)0x1f;
			break;
		case ColorFormat::R4G4B4:
			red = ((ColorR4G4B4*)(address))->Red / (double)0x0f;
			green = ((ColorR4G4B4*)(address))->Green / (double)0x0f;
			blue = ((ColorR4G4B4*)(address))->Blue / (double)0x0f;
			break;
		case ColorFormat::B4G4R4:
			red = ((ColorB4G4R4*)(address))->Red / (double)0x0f;
			green = ((ColorB4G4R4*)(address))->Green / (double)0x0f;
			blue = ((ColorB4G4R4*)(address))->Blue / (double)0x0f;
			break;
		case ColorFormat::R4G4B4A4:
			alpha = ((ColorR4G4B4A4*)(address))->Alpha / (double)0x0f;
			red = ((ColorR4G4B4A4*)(address))->Red / (double)0x0f;
			green = ((ColorR4G4B4A4*)(address))->Green / (double)0x0f;
			blue = ((ColorR4G4B4A4*)(address))->Blue / (double)0x0f;
			break;
		case ColorFormat::B4G4R4A4:
			alpha = ((ColorB4G4R4A4*)(address))->Alpha / (double)0x0f;
			red = ((ColorB4G4R4A4*)(address))->Red / (double)0x0f;
			green = ((ColorB4G4R4A4*)(address))->Green / (double)0x0f;
			blue = ((ColorB4G4R4A4*)(address))->Blue / (double)0x0f;
			break;
		case ColorFormat::A4R4G4B4:
			alpha = ((ColorA4R4G4B4*)(address))->Alpha / (double)0x0f;
			red = ((ColorA4R4G4B4*)(address))->Red / (double)0x0f;
			green = ((ColorA4R4G4B4*)(address))->Green / (double)0x0f;
			blue = ((ColorA4R4G4B4*)(address))->Blue / (double)0x0f;
			break;
		case ColorFormat::A4B4G4R4:
			alpha = ((ColorA4B4G4R4*)(address))->Alpha / (double)0x0f;
			red = ((ColorA4B4G4R4*)(address))->Red / (double)0x0f;
			green = ((ColorA4B4G4R4*)(address))->Green / (double)0x0f;
			blue = ((ColorA4B4G4R4*)(address))->Blue / (double)0x0f;
			break;
		case ColorFormat::R8G8B8:
			red = ((ColorR8G8B8*)(address))->Red / (double)0xff;
			green = ((ColorR8G8B8*)(address))->Green / (double)0xff;
			blue = ((ColorR8G8B8*)(address))->Blue / (double)0xff;
			break;
		case ColorFormat::B8G8R8:
			red = ((ColorB8G8R8*)(address))->Red / (double)0xff;
			green = ((ColorB8G8R8*)(address))->Green / (double)0xff;
			blue = ((ColorB8G8R8*)(address))->Blue / (double)0xff;
			break;
		case ColorFormat::R8G8B8A8:
			alpha = ((ColorR8G8B8A8*)(address))->Alpha / (double)0xff;
			red = ((ColorR8G8B8A8*)(address))->Red / (double)0xff;
			green = ((ColorR8G8B8A8*)(address))->Green / (double)0xff;
			blue = ((ColorR8G8B8A8*)(address))->Blue / (double)0xff;
			break;
		case ColorFormat::B8G8R8A8:
			alpha = ((ColorB8G8R8A8*)(address))->Alpha / (double)0xff;
			red = ((ColorB8G8R8A8*)(address))->Red / (double)0xff;
			green = ((ColorB8G8R8A8*)(address))->Green / (double)0xff;
			blue = ((ColorB8G8R8A8*)(address))->Blue / (double)0xff;
			break;
		case ColorFormat::A8R8G8B8:
			alpha = ((ColorA8R8G8B8*)(address))->Alpha / (double)0xff;
			red = ((ColorA8R8G8B8*)(address))->Red / (double)0xff;
			green = ((ColorA8R8G8B8*)(address))->Green / (double)0xff;
			blue = ((ColorA8R8G8B8*)(address))->Blue / (double)0xff;
			break;
		case ColorFormat::A8B8G8R8:
			alpha = ((ColorA8B8G8R8*)(address))->Alpha / (double)0xff;
			red = ((ColorA8B8G8R8*)(address))->Red / (double)0xff;
			green = ((ColorA8B8G8R8*)(address))->Green / (double)0xff;
			blue = ((ColorA8B8G8R8*)(address))->Blue / (double)0xff;
			break;
		case ColorFormat::AsRsGsBs:
			alpha = ((ColorAsRsGsBs*)(address))->Alpha;
			red = ((ColorAsRsGsBs*)(address))->Red;
			green = ((ColorAsRsGsBs*)(address))->Green;
			blue = ((ColorAsRsGsBs*)(address))->Blue;
			break;
		case ColorFormat::RsGsBsAs:
			alpha = ((ColorRsGsBsAs*)(address))->Alpha;
			red = ((ColorRsGsBsAs*)(address))->Red;
			green = ((ColorRsGsBsAs*)(address))->Green;
			blue = ((ColorRsGsBsAs*)(address))->Blue;
			break;
		case ColorFormat::RsGsBs:
			red = ((ColorRsGsBs*)(address))->Red;
			green = ((ColorRsGsBs*)(address))->Green;
			blue = ((ColorRsGsBs*)(address))->Blue;
			break;
		case ColorFormat::AdRdGdBd:
			alpha = ((ColorAdRdGdBd*)(address))->Alpha;
			red = ((ColorAdRdGdBd*)(address))->Red;
			green = ((ColorAdRdGdBd*)(address))->Green;
			blue = ((ColorAdRdGdBd*)(address))->Blue;
			break;
		case ColorFormat::RdGdBdAd:
			alpha = ((ColorRdGdBdAd*)(address))->Alpha;
			red = ((ColorRdGdBdAd*)(address))->Red;
			green = ((ColorRdGdBdAd*)(address))->Green;
			blue = ((ColorRdGdBdAd*)(address))->Blue;
			break;
		case ColorFormat::RdGdBd:
			red = ((ColorRdGdBd*)(address))->Red;
			green = ((ColorRdGdBd*)(address))->Green;
			blue = ((ColorRdGdBd*)(address))->Blue;
			break;
		}
		return true;
	}
	return false;
}

//-------------------------------------
// ピクセルブロック設定
//
bool ColorBuffer::SetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height, uintptr blocks, uint64 length )
{
	uintptr address = GetPixelAddress( x, y );
	if( address != NULL )
	{
		if( x + width < m_Width && y + height < m_Height && width * height * m_PixelSize <= length )
		{
			uint64 rowlength = m_Width * m_PixelSize;
			if( address + (rowlength * height) + (width * m_PixelSize) <= m_Buffer + m_BufferSize )
			{
				uint64 blockrowlength = width * m_PixelSize;
				for( uint32 i = 0; i < height; i++ )
				{
					address = GetPixelAddress( x, y + i );
					memcpy( (void*)address, (void*)blocks, (size_t)blockrowlength );
					blocks += (uintptr)blockrowlength;
				}
				return true;
			}
		}
	}
	return false;
}

//-------------------------------------
// ピクセルブロック設定
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
// ピクセルブロック取得
//
ColorBuffer* ColorBuffer::GetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height )
{
	if( x + width < m_Width && y + height < m_Height )
	{
		ColorBuffer* block = Create( m_Format, width, height );
		if( block != NULL )
		{
			if( !GetPixelBlock( x, y, block->m_Width, block->m_Height, block->m_Buffer, block->m_BufferSize ) )
			{
				block->Release( );
				block = NULL;
			}
		}
	}
	return NULL;
}

//-------------------------------------
// ピクセルブロック取得
//
bool ColorBuffer::GetPixelBlock( uint32 x, uint32 y, uint32 width, uint32 height, uintptr blockBuffer, uint64 length )
{
	bool retval = false;
	if( x + width < m_Width && y + height < m_Height )
	{
		if( length >= width * height * m_PixelSize )
		{
			for( uint32 by = 0; by < height; by++ )
			{
				uintptr address = GetPixelAddress( x, y + by );
				uintptr blockAddress = blockBuffer + (uintptr)((width * by) * m_PixelSize);
				memcpy( (void*)blockAddress, (void*)address, (size_t)(width * m_PixelSize) );
			}
			retval = true;
		}
	}
	return retval;
}



} }
