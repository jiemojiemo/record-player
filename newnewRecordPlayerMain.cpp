#include "recordplayerfactory.h"
#include <stdio.h>
#include <string>
#define TEST 1

#pragma comment( lib, "portaudio_x86.lib" )

int main()
{
#if TEST
	//open file
	FILE* file = fopen( "record.raw", "rb" );
	if( file == NULL )
	{
		fprintf( stderr, "Error:Cannot open the file.\n" );
		return -1;
	}

	//get file size
	unsigned long fileSize = 0;
	fseek( file, 0, SEEK_END );
	fileSize = ftell( file );
	fseek( file, 0, SEEK_SET );

	//malloc memory
	void* buffer = (void*)malloc( fileSize );
	if( buffer == NULL )
	{
		fprintf( stderr, "Error: malloc failure.\n" );
		return -1;
	}

	//copy data from file
	fread( buffer, 1, fileSize, file );
	fclose( file );

	//play 
	RecordPlayInfo info;
	info.channels = 1;
	info.sampleRate = 44100;
	info.sampleType = SAMPLE_TYPE_FLOAT32;
	info.seconds = 10;
	info.framePerBuffer = 512;
	RecordPlayerFactory recordPlayFactory;
	RecordPlayerABC *player = recordPlayFactory.GetRecordPlayer( info );
	//player->SetData( buffer, fileSize );
	 player->SetData( buffer );
	player->StartPlay();
	if( buffer != NULL )
	{
		free( buffer );
		buffer = NULL;
	}
#endif
	return 0;
}
