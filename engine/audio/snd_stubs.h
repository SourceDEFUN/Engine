//========= Copyright Valve Corporation, All rights reserved. ============//

#ifndef SND_STUBS_H
#define SND_STUBS_H

#include "engine/ienginevoice.h"

class CEngineVoiceStub : public IEngineVoice
{
public:
	virtual bool IsHeadsetPresent( int iController ) { return false; }
	virtual bool IsLocalPlayerTalking( int iController ) { return false; }

	virtual void AddPlayerToVoiceList( uint64 xPlayer, int iController ) {}
	virtual void RemovePlayerFromVoiceList( uint64 xPlayer, int iController ) {}

	virtual void GetRemoteTalkers( int *pNumTalkers, uint64 *pRemoteTalkers )
	{
		if ( pNumTalkers )
			*pNumTalkers = 0;
	}

	virtual bool VoiceUpdateData( int iController ) { return false; }
	virtual void GetVoiceData( int iController, const byte **ppvVoiceDataBuffer, unsigned int *pnumVoiceDataBytes )
	{
		if ( ppvVoiceDataBuffer )
			*ppvVoiceDataBuffer = NULL;
		if ( pnumVoiceDataBytes )
			*pnumVoiceDataBytes = NULL;
	}
	virtual void VoiceResetLocalData( int iController ) {}

	virtual void SetPlaybackPriority( uint64 remoteTalker, int iController, int iAllowPlayback ) {}
	virtual void PlayIncomingVoiceData( uint64 xuid, const byte *pbData, unsigned int dwDataSize, const bool *bAudiblePlayers = NULL ) {}

	virtual void RemoveAllTalkers() {}
};

CEngineVoiceStub *Audio_GetEngineVoiceStub();


IEngineVoice *Audio_GetEngineVoiceSteam();


#endif
