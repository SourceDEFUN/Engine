//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#ifndef AI_DEBUG_H
#define AI_DEBUG_H

#include "fmtstr.h"
#include "ai_debug_shared.h"

#if defined( _WIN32 )
#pragma once
#endif


enum AIMsgFlags
{
	AIMF_IGNORE_SELECTED = 0x01
};

void DevMsg( CAI_BaseNPC *pAI, unsigned flags, PRINTF_FORMAT_STRING const char *pszFormat, ... );
void DevMsg( CAI_BaseNPC *pAI, PRINTF_FORMAT_STRING const char *pszFormat, ... );


//-----------------------------------------------------------------------------
// Purpose: Use this to perform AI tracelines that are trying to determine LOS between points.
//			LOS checks between entities should use FVisible.
//-----------------------------------------------------------------------------
void AI_TraceLOS( const Vector& vecAbsStart, const Vector& vecAbsEnd, CBaseEntity *pLooker, trace_t *ptr, ITraceFilter *pFilter = NULL );

//-----------------------------------------------------------------------------

#ifdef DEBUG
extern bool g_fTestSteering;
#define TestingSteering() g_fTestSteering
#else
#define TestingSteering() false
#endif

//-----------------------------------------------------------------------------


#ifdef _DEBUG
extern ConVar ai_debug_doors;
#define AIIsDebuggingDoors( pNPC ) ( ai_debug_doors.GetBool() && pNPC->m_bSelected )
#define AIDoorDebugMsg( pNPC, msg )	if ( !AIIsDebuggingDoors( pNPC ) ) ; else Msg( msg )
#else
#define AIIsDebuggingDoors( pNPC ) (false)
#define AIDoorDebugMsg( pNPC, msg )	((void)(0)) 
#endif


//-----------------------------------------------------------------------------

#endif // AI_DEBUG_H
