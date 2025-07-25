#ifndef THREADTOOLS_INL
#define THREADTOOLS_INL

// This file is included in threadtools.cpp for all other platforms
//
// Do not #include other files here

CTHREADLOCALPTR(CThread) g_pCurThread;

CThread::CThread() :	
#ifdef _WIN32
m_hThread( NULL ),
m_threadId( 0 ),
#elif defined(_POSIX)
m_threadId( 0 ),
m_threadZombieId( 0 ) ,
#endif
m_result( 0 ),
m_flags( 0 )
{
	m_szName[0] = 0;
	m_NotSuspendedEvent.Set();
}

//---------------------------------------------------------

CThread::~CThread()
{
#ifdef MSVC
	if (m_hThread)
#elif defined(POSIX)
	if ( m_threadId )
#endif
	{
		if ( IsAlive() )
		{
			Msg( "Illegal termination of worker thread! Threads must negotiate an end to the thread before the CThread object is destroyed.\n" ); 
#ifdef _WIN32

			DoNewAssertDialog( __FILE__, __LINE__, "Illegal termination of worker thread! Threads must negotiate an end to the thread before the CThread object is destroyed.\n" );
#endif
			if ( GetCurrentCThread() == this )
			{
				Stop(); // BUGBUG: Alfred - this doesn't make sense, this destructor fires from the hosting thread not the thread itself!!
			}
		}
	}
#if defined(POSIX)
	if ( m_threadZombieId )
	{
		// just clean up zombie threads immediately (the destructor is fired from the hosting thread)
		Join();
	}
#endif
}


//---------------------------------------------------------

const char *CThread::GetName()
{
	AUTO_LOCK( m_Lock );
	if ( !m_szName[0] )
	{
#if defined( _WIN32 )
		_snprintf( m_szName, sizeof(m_szName) - 1, "Thread(%p/%p)", this, m_hThread );
#elif defined( POSIX )
		_snprintf( m_szName, sizeof(m_szName) - 1, "Thread(%p/0x%p)", this, (void*)m_threadId );
#endif
		m_szName[sizeof(m_szName) - 1] = 0;
	}
	return m_szName;
}

//---------------------------------------------------------

void CThread::SetName(const char *pszName)
{
	AUTO_LOCK( m_Lock );
	strncpy( m_szName, pszName, sizeof(m_szName) - 1 );
	m_szName[sizeof(m_szName) - 1] = 0;
}

//-----------------------------------------------------
// Functions for the other threads
//-----------------------------------------------------

// Start thread running  - error if already running
bool CThread::Start( unsigned nBytesStack, ThreadPriorityEnum_t nPriority )
{
	AUTO_LOCK( m_Lock );

	if ( IsAlive() )
	{
		AssertMsg( 0, "Tried to create a thread that has already been created!" );
		return false;
	}

	bool  bInitSuccess = false;
	CThreadEvent createComplete;
	ThreadInit_t init = { this, &createComplete, &bInitSuccess };

#if defined( THREAD_PARENT_STACK_TRACE_ENABLED )
	{
		int iValidEntries = GetCallStack_Fast( init.ParentStackTrace, ARRAYSIZE( init.ParentStackTrace ), 0 );
		for( int i = iValidEntries; i < ARRAYSIZE( init.ParentStackTrace ); ++i )
		{
			init.ParentStackTrace[i] = NULL;
		}
	}
#endif

#ifdef _WIN32
	m_hThread = (HANDLE)CreateThread( NULL,
		nBytesStack,
		(LPTHREAD_START_ROUTINE)GetThreadProc(),
		new ThreadInit_t(init),
		nBytesStack ? STACK_SIZE_PARAM_IS_A_RESERVATION : 0,
		(LPDWORD)&m_threadId );

	if( nPriority != TP_PRIORITY_DEFAULT )
	{
		SetThreadPriority( m_hThread, nPriority );
	}

	if ( !m_hThread )
	{
		AssertMsg1( 0, "Failed to create thread (error 0x%x)", GetLastError() );
		return false;
	}
#elif POSIX
	pthread_attr_t attr;
	pthread_attr_init( &attr );
	pthread_attr_setstacksize( &attr, MAX( nBytesStack, 1024u*1024 ) );
	//lwss - fix memory leak here
	m_threadInit = ThreadInit_t( init );
	//if ( pthread_create( &m_threadId, &attr, (void *(*)(void *))GetThreadProc(), new ThreadInit_t( init ) ) != 0 )
	if ( pthread_create( &m_threadId, &attr, (void *(*)(void *))GetThreadProc(), &m_threadInit ) != 0 )
	//lwss end
	{
		AssertMsg1( 0, "Failed to create thread (error 0x%x)", GetLastError() );
		return false;
	}
	bInitSuccess = true;
#endif



	if ( !WaitForCreateComplete( &createComplete ) )
	{
		Msg( "Thread failed to initialize\n" );
#ifdef _WIN32
		CloseHandle( m_hThread );
		m_hThread = NULL;
#endif

		return false;
	}

	if ( !bInitSuccess )
	{
		Msg( "Thread failed to initialize\n" );
#ifdef _WIN32
		CloseHandle( m_hThread );
		m_hThread = NULL;
#elif defined(POSIX)
		m_threadId = 0;
		m_threadZombieId = 0;
#endif
		return false;
	}

#ifdef _WIN32
	if ( !m_hThread )
	{
		Msg( "Thread exited immediately\n" );
	}
#endif

#ifdef _WIN32
	AddThreadHandleToIDMap( m_hThread, m_threadId );
	return !!m_hThread;
#elif defined(POSIX)
	return !!m_threadId;
#endif
}

//---------------------------------------------------------
//
// Return true if the thread has been created and hasn't yet exited
//

bool CThread::IsAlive()
{
#ifdef _WIN32
	DWORD dwExitCode;
	return (
		m_hThread 
		&& GetExitCodeThread(m_hThread, &dwExitCode) 
		&& dwExitCode == STILL_ACTIVE );
#elif defined(POSIX)
	return !!m_threadId;
#endif
}

// This method causes the current thread to wait until this thread
// is no longer alive.
bool CThread::Join( unsigned timeout )
{
#ifdef _WIN32
	if ( m_hThread )
#elif defined(POSIX)
	if ( m_threadId || m_threadZombieId )
#endif
	{
		AssertMsg(GetCurrentCThread() != this, _T("Thread cannot be joined with self"));

#ifdef _WIN32
		return ThreadJoin( (ThreadHandle_t)m_hThread, timeout );
#elif defined(POSIX)
		bool ret = ThreadJoin(  (ThreadHandle_t)(m_threadId ? m_threadId : m_threadZombieId), timeout );
		m_threadZombieId = 0;
		return ret;
#endif
	}
	return true;
}

//---------------------------------------------------------

ThreadHandle_t CThread::GetThreadHandle()
{
#ifdef _WIN32
	return (ThreadHandle_t)m_hThread;
#else
	return (ThreadHandle_t)m_threadId;
#endif
}


//---------------------------------------------------------

int CThread::GetResult()
{
	return m_result;
}

//-----------------------------------------------------
// Functions for both this, and maybe, and other threads
//-----------------------------------------------------

// Forcibly, abnormally, but relatively cleanly stop the thread
//

void CThread::Stop(int exitCode)
{
	if ( !IsAlive() )
		return;

	if ( GetCurrentCThread() == this )
	{
		m_result = exitCode;
		if ( !( m_flags & SUPPORT_STOP_PROTOCOL ) )
		{
			OnExit();
			g_pCurThread = NULL;

#ifdef _WIN32
			CloseHandle( m_hThread );
			RemoveThreadHandleToIDMap( m_hThread );
			m_hThread = NULL;
#else
			m_threadId = 0;
			m_threadZombieId = 0;
#endif
		}
		else
		{
			throw exitCode;
		}
	}
	else
		AssertMsg( 0, "Only thread can stop self: Use a higher-level protocol");
}

//---------------------------------------------------------

// Get the priority
int CThread::GetPriority() const
{
#ifdef _WIN32
	return GetThreadPriority(m_hThread);
#elif defined(POSIX)
	struct sched_param thread_param;
	int policy;
	pthread_getschedparam( m_threadId, &policy, &thread_param );
	return thread_param.sched_priority;
#endif
}

//---------------------------------------------------------

// Set the priority
bool CThread::SetPriority(int priority)
{
#ifdef WIN32
	return ThreadSetPriority( (ThreadHandle_t)m_hThread, priority );
#else
	return ThreadSetPriority( (ThreadHandle_t)m_threadId, priority );
#endif
}

//---------------------------------------------------------

// Suspend a thread
unsigned CThread::Suspend()
{
	AssertMsg( ThreadGetCurrentId() == (ThreadId_t)m_threadId, "Cannot call CThread::Suspend from outside thread" );

	if ( ThreadGetCurrentId() != (ThreadId_t)m_threadId )
	{
		DebuggerBreakIfDebugging();
	}

	m_NotSuspendedEvent.Reset();
	m_NotSuspendedEvent.Wait();

	return 0;
}


//---------------------------------------------------------

unsigned CThread::Resume()
{
	if ( m_NotSuspendedEvent.Check() )
	{
		DevWarning( "Called Resume() on a thread that is not suspended!\n" );
	}
	m_NotSuspendedEvent.Set();
	return 0;
}

//---------------------------------------------------------

// Force hard-termination of thread.  Used for critical failures.
bool CThread::Terminate(int exitCode)
{
#if defined( _WIN32 )
	// I hope you know what you're doing!
	if (!TerminateThread(m_hThread, exitCode))
		return false;
	CloseHandle( m_hThread );
	RemoveThreadHandleToIDMap( m_hThread );
	m_hThread = NULL;
#elif defined(POSIX)
	pthread_kill( m_threadId, SIGKILL );
	m_threadId = 0;
#endif
	return true;
}

//-----------------------------------------------------
// Global methods
//-----------------------------------------------------

// Get the Thread object that represents the current thread, if any.
// Can return NULL if the current thread was not created using
// CThread
//

CThread *CThread::GetCurrentCThread()
{
	return g_pCurThread;
}

//---------------------------------------------------------
//
// Offer a context switch. Under Win32, equivalent to Sleep(0)
//

#ifdef Yield
#undef Yield
#endif
void CThread::Yield()
{
#ifdef _WIN32
	::Sleep(0);
#elif defined(POSIX)
	sched_yield();
#endif
}

//---------------------------------------------------------
//
// This method causes the current thread to yield and not to be
// scheduled for further execution until a certain amount of real
// time has elapsed, more or less. Duration is in milliseconds

void CThread::Sleep( unsigned duration )
{
#ifdef _WIN32
	::Sleep(duration);
#elif defined(POSIX)
	usleep( duration * 1000 );
#endif
}

//---------------------------------------------------------

// Optional pre-run call, with ability to fail-create. Note Init()
// is forced synchronous with Start()
bool CThread::Init()
{
	return true;
}

//---------------------------------------------------------

// Called when the thread exits
void CThread::OnExit() { }

// Allow for custom start waiting
bool CThread::WaitForCreateComplete( CThreadEvent *pEvent )
{
	// Force serialized thread creation...
	if (!pEvent->Wait(60000))
	{
		AssertMsg( 0, "Probably deadlock or failure waiting for thread to initialize." );
		return false;
	}
	return true;
}

bool CThread::IsThreadRunning()
{
	return ThreadIsThreadIdRunning( (ThreadId_t)m_threadId );
}

//---------------------------------------------------------
CThread::ThreadProc_t CThread::GetThreadProc()
{
	return ThreadProc;
}

void CThread::ThreadProcRunWithMinidumpHandler( void *pv )
{
	ThreadInit_t *pInit = reinterpret_cast<ThreadInit_t*>(pv);
	pInit->pThread->m_result = pInit->pThread->Run();
}

#ifdef _WIN32
unsigned long STDCALL CThread::ThreadProc(LPVOID pv)
#else
void* CThread::ThreadProc(LPVOID pv)
#endif
{
// #if defined( POSIX )
	ThreadInit_t *pInit = reinterpret_cast<ThreadInit_t*>(pv);
// #else
// 	std::auto_ptr<ThreadInit_t> pInit((ThreadInit_t *)pv);
// #endif

	AllocateThreadID();

	CThread *pThread = pInit->pThread;
	g_pCurThread = pThread;

	pThread->m_pStackBase = AlignValue( &pThread, 4096 );

	pInit->pThread->m_result = -1;

#if defined( THREAD_PARENT_STACK_TRACE_ENABLED )
	CStackTop_ReferenceParentStack stackTop( pInit->ParentStackTrace, ARRAYSIZE( pInit->ParentStackTrace ) );
#endif

	bool bInitSuccess = true;
	if ( pInit->pfInitSuccess )
		*(pInit->pfInitSuccess) = false;

	try
	{
		bInitSuccess = pInit->pThread->Init();
	}

	catch (...)
	{
		pInit->pInitCompleteEvent->Set();
		throw;
	}

	if ( pInit->pfInitSuccess )
		*(pInit->pfInitSuccess) = bInitSuccess;
	pInit->pInitCompleteEvent->Set();
	if (!bInitSuccess)
		return 0;

	if ( !Plat_IsInDebugSession() && (pInit->pThread->m_flags & SUPPORT_STOP_PROTOCOL) )
	{
		try
		{
			pInit->pThread->m_result = pInit->pThread->Run();
		}

		catch (...)
		{
		}
	}
	else
	{
#if defined( _WIN32 )
		CatchAndWriteMiniDumpForVoidPtrFn( ThreadProcRunWithMinidumpHandler, pv, false );
#else
		pInit->pThread->m_result = pInit->pThread->Run();
#endif
	}

	pInit->pThread->OnExit();
	g_pCurThread = NULL;
	FreeThreadID();

	AUTO_LOCK( pThread->m_Lock );
#ifdef _WIN32
	CloseHandle( pThread->m_hThread );
	RemoveThreadHandleToIDMap( pThread->m_hThread );
	pThread->m_hThread = NULL;
#elif defined(POSIX)
	pThread->m_threadZombieId = pThread->m_threadId;
	pThread->m_threadId = 0;
#else
#error
#endif

	pThread->m_ExitEvent.Set();

#if defined( POSIX )
	return (void*)(uintp)pInit->pThread->m_result;
#else
	return pInit->pThread->m_result;
#endif
}

#endif // THREADTOOLS_INL
