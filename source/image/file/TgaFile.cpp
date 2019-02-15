#include <yatools/image/file/yatools.image.file.tgafile.h>


namespace yatools { namespace image { namespace file {


//-------------------------------------
// �o�C�i������
//-------------------------------------
//-------------------------------------
// �t�@�C���w�b�_�擾
//
TgaHeader* TgaFile::GetHeader( uintptr buffer, uint64 length )
{
	if( buffer != NULL && length >= sizeof( TgaHeader ) )
	{
		return (TgaHeader*)buffer;
	}
	return NULL;
}

//-------------------------------------
// �t�@�C���t�b�^�[�擾
//
TgaFooter* TgaFile::GetFooter( uintptr buffer, uint64 length )
{
	TgaHeader* header = GetHeader( buffer, length );
	if( header == NULL )
	{
		return NULL;
	}
	if( length >= sizeof( TgaHeader ) + sizeof( TgaFooter ) )
	{
		return (TgaFooter*)(buffer + (length - sizeof( TgaFooter )));
	}
	return NULL;
}

//-------------------------------------
// ImageID�t�B�[���h�擾
//
uintptr TgaFile::GetImageIdField( uintptr buffer, uint64 length )
{
	TgaHeader* header = GetHeader( buffer, length );
	if( header == NULL || header->IdFieldLength <= 0 )
	{
		return NULL;
	}
	return buffer + sizeof( TgaHeader );
}

//-------------------------------------
// �J���[�}�b�v�t�B�[���h�擾
//
uintptr TgaFile::GetColorMapField( uintptr buffer, uint64 length )
{
	TgaHeader* header = GetHeader( buffer, length );
	if( header == NULL || header->ColorMapType == 0 )
	{
		return NULL;
	}
	return (buffer + sizeof( TgaHeader ) + header->ColorMapSpecification.FirstEntryIndex);
}

//-------------------------------------
// �摜�t�B�[���h�擾
//
uintptr TgaFile::GetImageFile( uintptr buffer, uint64 length )
{
	TgaHeader* header = GetHeader( buffer, length );
	if( header == NULL || header->ImageType == 0 )
	{
		return NULL;
	}
	if( header->ColorMapType == 0 )
	{
		return (buffer + sizeof( TgaHeader ) + header->IdFieldLength);
	}
	return (buffer + sizeof( TgaHeader ) + header->IdFieldLength) + ((header->ColorMapSpecification.EntrySize / 8) * header->ColorMapSpecification.Length);
}

//-------------------------------------
// �g�����t�B�[���h�擾
//
TgaExtension* TgaFile::GetExtensionField( uintptr buffer, uint64 length )
{
	TgaFooter* footer = GetFooter( buffer, length );
	if( footer != NULL && footer->ExtensionOffset > 0 )
	{
		return (TgaExtension*)(buffer + footer->ExtensionOffset);
	}
	return NULL;
}

//-------------------------------------
// �J���җ̈�t�B�[���h�擾
//
uintptr TgaFile::GetDeveloperAreaField( uintptr buffer, uint64 length )
{
	TgaFooter* footer = GetFooter( buffer, length );
	if( footer != NULL && footer->DeveloperAreaOffset > 0 )
	{
		return (buffer + footer->DeveloperAreaOffset);
	}
	return NULL;
}


} } }
