//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=====================================================================================//

#ifndef SND_DEV_XAUDIO_H
#define SND_DEV_XAUDIO_H
#pragma once
#include "audio_pch.h"
#include "inetmessage.h"
#include "netmessages.h"

class IAudioDevice;
IAudioDevice *Audio_CreateXAudioDevice( void );
#endif // SND_DEV_XAUDIO_H
