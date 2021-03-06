#include <yatools/yatools.image.h>
#include <yatools/yatools.image.file.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace yatools::image;
using namespace yatools::image::file;


/**
* @fn void DumpCheck( const char* message, bool check )
* @brief チェック結果出力
* @param[in] message			チェック内容メッセージ
* @param[in] check				チェック結果
* @details
*	チェック結果とチェック内容を出力します。
*/
void DumpCheck( const char* message, bool check )
{
	printf( message );
	if( check )
	{
		puts( "  OK!!" );
	}
	else
	{
		puts( "  NG!!" );
	}
}


/**
* @fn int main( int argc, char* argv[] )
* @brief エントリーポイント
* @param[in] argc				コマンドライン引数個数
* @param[in] argv[]				コマンドライン引数
* @returns						コマンドライン戻り値
* @details
*	エントリーポイントです。
*/
int main( int argc, char* argv[] )
{
	puts( "----[Pixel struct]------------------------" );
	DumpCheck( "Pixel[Gray8] size check.", sizeof( ColorGray8 ) == 1 );
	DumpCheck( "Pixel[Gray16] size check.", sizeof( ColorGray16 ) == 2 );
	DumpCheck( "Pixel[R5G5B5] size check.", sizeof( ColorR5G5B5 ) == 2 );
	DumpCheck( "Pixel[B5G5R5] size check.", sizeof( ColorB5G5R5 ) == 2 );
	DumpCheck( "Pixel[R5G5B5A1] size check.", sizeof( ColorR5G5B5A1 ) == 2 );
	DumpCheck( "Pixel[B5G5R5A1] size check.", sizeof( ColorB5G5R5A1 ) == 2 );
	DumpCheck( "Pixel[A1R5G5B5] size check.", sizeof( ColorA1R5G5B5 ) == 2 );
	DumpCheck( "Pixel[A1B5G5R5] size check.", sizeof( ColorA1B5G5R5 ) == 2 );
	DumpCheck( "Pixel[R5G6B5] size check.", sizeof( ColorR5G6B5 ) == 2 );
	DumpCheck( "Pixel[B5G6R5] size check.", sizeof( ColorB5G6R5 ) == 2 );
	DumpCheck( "Pixel[R4G4B4] size check.", sizeof( ColorR4G4B4 ) == 2 );
	DumpCheck( "Pixel[B4G4R4] size check.", sizeof( ColorB4G4R4 ) == 2 );
	DumpCheck( "Pixel[R4G4B4A4] size check.", sizeof( ColorR4G4B4A4 ) == 2 );
	DumpCheck( "Pixel[B4G4R4A4] size check.", sizeof( ColorB4G4R4A4 ) == 2 );
	DumpCheck( "Pixel[A4R4G4B4] size check.", sizeof( ColorA4R4G4B4 ) == 2 );
	DumpCheck( "Pixel[A4B4G4R4] size check.", sizeof( ColorA4B4G4R4 ) == 2 );
	DumpCheck( "Pixel[R8G8B8] size check.", sizeof( ColorR8G8B8 ) == 3 );
	DumpCheck( "Pixel[B8G8R8] size check.", sizeof( ColorB8G8R8 ) == 3 );
	DumpCheck( "Pixel[R8G8B8A8] size check.", sizeof( ColorR8G8B8A8 ) == 4 );
	DumpCheck( "Pixel[B8G8R8A8] size check.", sizeof( ColorB8G8R8A8 ) == 4 );
	DumpCheck( "Pixel[A8R8G8B8] size check.", sizeof( ColorA8R8G8B8 ) == 4 );
	DumpCheck( "Pixel[A8B8G8R8] size check.", sizeof( ColorA8B8G8R8 ) == 4 );
	DumpCheck( "Pixel[RsGsBs] size check.", sizeof( ColorRsGsBs ) == 12 );
	DumpCheck( "Pixel[RsGsBsAs] size check.", sizeof( ColorRsGsBsAs ) == 16 );
	DumpCheck( "Pixel[AsRsGsBs] size check.", sizeof( ColorAsRsGsBs ) == 16 );
	DumpCheck( "Pixel[RdGdBd] size check.", sizeof( ColorRdGdBd ) == 24 );
	DumpCheck( "Pixel[RdGdBdAd] size check.", sizeof( ColorRdGdBdAd ) == 32 );
	DumpCheck( "Pixel[AdRdGdBd] size check.", sizeof( ColorAdRdGdBd ) == 32 );


	puts( "----[TGA File]------------------------" );
	DumpCheck( "header size check.", sizeof( TgaHeader ) == 18 );
	DumpCheck( "footer size check.", sizeof( TgaFooter ) == 26 );
	DumpCheck( "Extension size check.", sizeof( TgaExtension ) == 495 );

	puts( "----[BMP File]------------------------" );
	DumpCheck( "header size check.", sizeof( BmpHeader ) == 14 );
	DumpCheck( "infomation size check.", sizeof( BmpInfomationHeader ) == 40 );

	puts( "----[Png File]------------------------" );
	{
		FILE* fp = fopen( "test.png", "rb" );
		fseek( fp, 0, SEEK_END );
		uint64_t size = ftell( fp );
		fseek( fp, 0, SEEK_SET );
		uint8_t* buffer = new uint8_t[ size ];
		fread( buffer, 1, size, fp );
		fclose( fp );

		PngInfomation info;
		PngFile::GetInfomation( &info, (uintptr_t)buffer, size );


		ColorBuffer* colorBuffer = PngFile::GetColorBuffer( (uintptr_t)buffer, size );
		delete[] buffer;
		if( colorBuffer != NULL )
		{
			size = PngFile::WriteFileBuffer( colorBuffer, NULL, 0 );
			buffer = new uint8_t[ size ];
			PngFile::WriteFileBuffer( colorBuffer, (uintptr_t)buffer, size );

			fp = fopen( "test.png.png", "wb" );
			fwrite( buffer, 1, size, fp );
			fclose( fp );
			delete[] buffer;
		}
	}

#ifdef _WIN32
	{
		puts( "----[Windows]-------------------------" );
		ColorBuffer* buffer = Windows::GetColorBuffer( GetDesktopWindow( ) );
		if( buffer != NULL )
		{
			uint64_t size = PngFile::WriteFileBuffer( buffer, NULL, 0 );
			uint8_t* fileBuffer = new uint8_t[ size ];
			PngFile::WriteFileBuffer( buffer, (uintptr_t)fileBuffer, size );

			FILE* fp = fopen( "test.ss.png", "wb" );
			fwrite( fileBuffer, 1, size, fp );
			fclose( fp );
			delete[] fileBuffer;

			buffer->Release( );
		}
	}
#endif

	return 0;
}
