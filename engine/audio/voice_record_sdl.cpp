//========= Copyright 1996-2009, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
// This module implements the voice record and compression functions 

//#include "audio_pch.h"
//#include "voice.h"
#include "tier0/platform.h"
#include "ivoicerecord.h"
#include "tier0/dbg.h"
#include "tier0/threadtools.h"

#include <assert.h>
#include <SDL3/SDL_audio.h>

#define RECORDING_BUFFER_SECONDS 3
#define SAMPLE_COUNT 2048

// ------------------------------------------------------------------------------
// VoiceRecord_SDL
// ------------------------------------------------------------------------------

struct AudioBuf
{
	int Read(char *out, int len)
	{
		int nAvalible = (size + (writePtr - readPtr)) % size;

		if( nAvalible == 0 )
			return 0;

		if( len > nAvalible ) len = nAvalible;

		int diff = (data + size) - readPtr;


		if( len > diff )
		{
			memcpy(out, readPtr, diff );
			memcpy(out+diff, data, len-diff );
		} else memcpy(out, readPtr, len);

		readPtr += len;

		if( readPtr >= data + size )
			readPtr -= size;

		return len;
	}

	void Write(char *in, int len)
	{
		int diff = (data + size) - writePtr;

		if( len > diff )
		{
			memcpy(writePtr, in, diff );
			memcpy(data, in+diff, len-diff );
		} else memcpy(writePtr, in, len);

		writePtr += len;

		if (writePtr >= (data + size))
			writePtr -= size;
	}

	int size;
	char *data;
	char *readPtr;
	char *writePtr;
};

class VoiceRecord_SDL : public IVoiceRecord
{
protected:
	virtual				~VoiceRecord_SDL();
public:
	VoiceRecord_SDL();
	virtual void	Release();
	// virtual void	PollCapture();
	bool			RecordStart();
	void			RecordStop();

	// Initialize. The format of the data we expect from the provider is
	// 8-bit signed mono at the specified sample rate.
	bool		Init(int sampleRate);
	virtual void		Idle() {}; // Stub
	void RenderBuffer( char *pszBuf, int size );

	// Get the most recent N samples.
	int			GetRecordedData(short *pOut, int nSamplesWanted );

	SDL_AudioSpec m_ReceivedRecordingSpec;
	int m_BytesPerSample; // Who needs your incapsulation?
	int m_nSampleRate;
private:
	bool				InitalizeInterfaces();	// Initialize the openal capture buffers and other interfaces
	void				ReleaseInterfaces();	// Release openal buffers and other interfaces
	void				ClearInterfaces();				// Clear members.
private:

	SDL_AudioDeviceID m_Device;
    SDL_AudioStream*  m_Stream{};
    AudioBuf          m_AudioBuffer;
};

void audioRecordingCallback( void *userdata, uint8 *stream, int len )
{
	VoiceRecord_SDL *voice = (VoiceRecord_SDL*)userdata;
	voice->RenderBuffer( (char*)stream, len );
}

VoiceRecord_SDL::VoiceRecord_SDL() :
m_nSampleRate( 0 ) ,m_Device( 0 )
{
	m_AudioBuffer.data = NULL;
	m_AudioBuffer.readPtr = NULL;
	m_AudioBuffer.writePtr = NULL;

	ClearInterfaces();
}

VoiceRecord_SDL::~VoiceRecord_SDL()
{
	ReleaseInterfaces();
	ClearInterfaces();
}

void VoiceRecord_SDL::Release()
{
	ReleaseInterfaces();
	ClearInterfaces();
	delete this;
}

// Secton: we have audioRecordingCallback for that 🤦
// void VoiceRecord_SDL::PollCapture()
// {
//     if (!m_Stream) return;

//     const int chunkSize = 4096;
//     Uint8 temp[chunkSize];

//     int bytesRead;
//     while ((bytesRead = SDL_GetAudioStreamData(m_Stream, temp, chunkSize)) > 0)
//         RenderBuffer((char*)temp, bytesRead);
// }

bool VoiceRecord_SDL::RecordStart() {
    if (!m_Stream) return false;
    return SDL_ResumeAudioDevice(m_Device);
}

void VoiceRecord_SDL::RecordStop() {
    if (m_Device)
        SDL_PauseAudioDevice(m_Device);

    if (m_Stream) {
        SDL_DestroyAudioStream(m_Stream);
        m_Stream = nullptr;
        m_Device = 0;
    }
}

bool VoiceRecord_SDL::InitalizeInterfaces()
{
    SDL_AudioSpec desired{};
    desired.freq = m_nSampleRate;
    desired.format = SDL_AUDIO_S16;
    desired.channels = 1;
    // desired.samples = SAMPLE_COUNT;

    // SDL3: open a capture stream instead of setting callback
    m_Stream = SDL_OpenAudioDeviceStream(
        m_Device, // NULL + iscapture → replaced
        &desired,
        nullptr, // No direct callback; we'll pull data
        nullptr  // No userdata
    );

    if (!m_Stream) return false;

    // Get actual format
    m_ReceivedRecordingSpec = desired;  // SDL3 won't automatically fill this struct.
    // If you need actual device format, use SDL_GetAudioStreamFormat().

    // Device ID (needed for pause/resume)
    m_Device = SDL_GetAudioStreamDevice(m_Stream);

    m_BytesPerSample =
        m_ReceivedRecordingSpec.channels *
        (SDL_AUDIO_BITSIZE(m_ReceivedRecordingSpec.format) / 8);

    int bytesPerSecond = m_ReceivedRecordingSpec.freq * m_BytesPerSample;

    m_AudioBuffer.size = RECORDING_BUFFER_SECONDS * bytesPerSecond;
    if (!m_AudioBuffer.data)
        m_AudioBuffer.data = (char*)malloc(m_AudioBuffer.size);

    m_AudioBuffer.readPtr = m_AudioBuffer.data;
    m_AudioBuffer.writePtr = m_AudioBuffer.data +
                             SAMPLE_COUNT * m_BytesPerSample * 2;

    memset(m_AudioBuffer.data, 0, m_AudioBuffer.size);

    return true;
}

bool VoiceRecord_SDL::Init(int sampleRate) {
    m_nSampleRate = sampleRate;

    SDL_AudioSpec desired{};
    desired.freq = sampleRate;
    desired.format = SDL_AUDIO_S16;
    desired.channels = 1;
    // desired.samples = SAMPLE_COUNT;

    // SDL3: Open capture stream
    m_Stream = SDL_OpenAudioDeviceStream(
        m_Device, &desired, nullptr, nullptr
    );

    if (!m_Stream) {
        Msg("Failed to open audio capture: %s", SDL_GetError());
        return false;
    }

    m_Device = SDL_GetAudioStreamDevice(m_Stream);
    m_BytesPerSample = desired.channels * (SDL_AUDIO_BITSIZE(desired.format) / 8);

    return true;
}


void VoiceRecord_SDL::ReleaseInterfaces()
{
	if( m_Device != 0 )
		SDL_CloseAudioDevice( m_Device );

	m_Device = 0;
}


void VoiceRecord_SDL::ClearInterfaces()
{
	if( m_AudioBuffer.data )
	{
		free( m_AudioBuffer.data );
		m_AudioBuffer.data = NULL;
		m_AudioBuffer.readPtr = NULL;
		m_AudioBuffer.writePtr = NULL;
	}
	m_Device = 0;
}

void VoiceRecord_SDL::RenderBuffer( char *pszBuf, int size )
{
	m_AudioBuffer.Write( pszBuf, size );
}

int VoiceRecord_SDL::GetRecordedData(short *pOut, int nSamples )
{
	if ( !m_AudioBuffer.data || nSamples == 0 )
		return 0;

	int cbSamples = nSamples * m_BytesPerSample;

	return m_AudioBuffer.Read( (char*)pOut, cbSamples )/m_BytesPerSample;
}

IVoiceRecord* CreateVoiceRecord_SDL(int sampleRate)
{
	VoiceRecord_SDL *pRecord = new VoiceRecord_SDL;
	if ( pRecord && pRecord->Init(sampleRate) )
		return pRecord;
	else if( pRecord )
		pRecord->Release();

	return NULL;
}
