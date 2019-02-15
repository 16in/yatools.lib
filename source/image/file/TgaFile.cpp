#include <yatools/image/file/yatools.image.file.tgafile.h>


namespace yatools { namespace image { namespace file {


//-------------------------------------
// バイナリ操作
//-------------------------------------
//-------------------------------------
// ファイルヘッダ取得
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
// ファイルフッター取得
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
// ImageIDフィールド取得
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
// カラーマップフィールド取得
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
// 画像フィールド取得
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
// 拡張情報フィールド取得
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
// 開発者領域フィールド取得
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
