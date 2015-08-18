#pragma once
#include "portaudio.h"

typedef unsigned long SampleType;
#define SAMPLE_TYPE_FLOAT32 ((SampleType) 0x00000001)
#define SAMPLE_TYPE_INT32	((SampleType) 0x00000002)
#define SAMPLE_TYPE_INT24	((SampleType) 0x00000004)
#define SAMPLE_TYPE_INT16   ((SampleType) 0x00000008)
#define SAMPLE_TYPE_INT8    ((SampleType) 0x00000010)
#define SAMPLE_TYPE_UINT8   ((SampleType) 0x00000020)

struct RecordPlayInfo{
	unsigned int seconds;
	unsigned int sampleRate;
	unsigned int channels;
	SampleType sampleType;
	unsigned int framePerBuffer;
};

struct RecordData{
	int          frameIndex;  /* Index into sample array. */
	int          maxFrameIndex;
	unsigned int totalBytes;
	void	     *recordedSamples;
};

typedef int (*callbackPointer)( const void*, void*, unsigned long,
	const PaStreamCallbackTimeInfo*,
	PaStreamCallbackFlags,
	void*);

class RecordPlayerABC{
private:
	RecordPlayerABC( const RecordPlayerABC& rp ){}
	RecordPlayerABC& operator=( const RecordPlayerABC& rp ){}

	/**
	* @brief : 根据bits获得format
	*/
	PaSampleFormat GetSampleFormat();
protected:
	static RecordPlayInfo	m_info;
	RecordData		m_data;
	callbackPointer m_pCallback;
public:
	RecordPlayerABC();
	virtual ~RecordPlayerABC();

	int StartPlay();
	virtual int SetData( const void* data )=0;
	virtual int SetData( const void* data, unsigned long bufferSize )=0;
};

class RecordPlayerFloat32 : public RecordPlayerABC{
private:
	static int playCallback(const void *inputBuffer,
		void *outputBuffer, unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags, 
		void *userData);
public:
	RecordPlayerFloat32( const RecordPlayInfo& info );
	~RecordPlayerFloat32(){}

	virtual int SetData( const void* data );
	virtual int SetData( const void* data, unsigned long bufferSize );
};

class RecordPlayerInt16 : public RecordPlayerABC{
private:
	static int playCallback(const void *inputBuffer,
		void *outputBuffer, unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags, 
		void *userData);
public:
	RecordPlayerInt16( const RecordPlayInfo& info );
	~RecordPlayerInt16(){}

	virtual int SetData( const void* data );
	virtual int SetData( const void* data, unsigned long bufferSize );
};