#include <yatools/yatools.image.h>
#include <yatools/yatools.image.file.h>
#include <stdio.h>

using namespace yatools::image;
using namespace yatools::image::file;


void DumpCheck( const char* message, bool check );


int main( void )
{
	DumpCheck( "TGA File header size check.", sizeof( TgaHeader ) == 18 );
	DumpCheck( "TGA File footer size check.", sizeof( TgaFooter ) == 26 );
	DumpCheck( "TGA File Extension size check.", sizeof( TgaExtension ) == 495 );

	return 0;
}

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
