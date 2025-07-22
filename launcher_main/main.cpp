//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: A redirection tool that allows the DLLs to reside elsewhere.
//
//=====================================================================================//

#if defined( _WIN32 )
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <direct.h>
#endif
#ifdef POSIX
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <limits.h>
#include <string.h>
#define MAX_PATH PATH_MAX
#endif

#include "tier0/basetypes.h"

#ifdef WIN32
typedef int (*LauncherMain_t)( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
							  LPSTR lpCmdLine, int nCmdShow );
#elif POSIX
typedef int (*LauncherMain_t)( int argc, char **argv );
#else
#error
#endif

#ifdef WIN32
// hinting the nvidia driver to use the dedicated graphics card in an optimus configuration
// for more info, see: http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
extern "C" { _declspec( dllexport ) DWORD NvOptimusEnablement = 0x00000001; }

// same thing for AMD GPUs using v13.35 or newer drivers
extern "C" { __declspec( dllexport ) int AmdPowerXpressRequestHighPerformance = 1; }

#endif


//-----------------------------------------------------------------------------
// Purpose: Return the directory where this .exe is running from
// Output : char
//-----------------------------------------------------------------------------
static char *GetBaseDir( const char *pszBuffer )
{
	static char	basedir[ MAX_PATH ];
	char szBuffer[ MAX_PATH ];
	size_t j;
	char *pBuffer = NULL;

	strcpy( szBuffer, pszBuffer );

	pBuffer = strrchr( szBuffer,'\\' );
	if ( pBuffer )
	{
		*(pBuffer+1) = '\0';
	}

	strcpy( basedir, szBuffer );

	j = strlen( basedir );
	if (j > 0)
	{
		if ( ( basedir[ j-1 ] == '\\' ) || 
			 ( basedir[ j-1 ] == '/' ) )
		{
			basedir[ j-1 ] = 0;
		}
	}

	return basedir;
}

#ifdef WIN32

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	// Must add 'bin' to the path....
	char* pPath = getenv("PATH");

	// Use the .EXE name to determine the root directory
	char moduleName[ MAX_PATH ];
	char szBuffer[4096];
	if ( !GetModuleFileName( hInstance, moduleName, MAX_PATH ) )
	{
		MessageBox( 0, "Failed calling GetModuleFileName", "Launcher Error", MB_OK );
		return 0;
	}

	// Get the root directory the .exe is in
	char* pRootDir = GetBaseDir( moduleName );

#ifdef _DEBUG
	int len = 
#endif
	_snprintf( szBuffer, sizeof( szBuffer ), "PATH=%s\\bin\\;%s", pRootDir, pPath );
	szBuffer[sizeof( szBuffer ) - 1] = '\0';
	assert( len < sizeof( szBuffer ) );
	_putenv( szBuffer );

	// Assemble the full path to our "launcher.dll"
	_snprintf( szBuffer, sizeof( szBuffer ), "%s\\bin\\launcher.dll", pRootDir );
	szBuffer[sizeof( szBuffer ) - 1] = '\0';

	// STEAM OK ... filesystem not mounted yet
	HINSTANCE launcher = LoadLibraryEx( szBuffer, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
	if ( !launcher )
	{
		char *pszError;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&pszError, 0, NULL);

		char szBuf[1024];
		_snprintf(szBuf, sizeof( szBuf ), "Failed to load the launcher DLL:\n\n%s", pszError);
		szBuf[sizeof( szBuf ) - 1] = '\0';
		MessageBox( 0, szBuf, "Launcher Error", MB_OK );

		LocalFree(pszError);
		return 0;
	}

	LauncherMain_t main = (LauncherMain_t)GetProcAddress( launcher, "LauncherMain" );
	return main( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
}

#elif defined (POSIX)

#if defined( LINUX )

#include <fcntl.h>
#include <sys/stat.h>

static bool IsDebuggerPresent( int time )
{
	// Need to get around the __wrap_open() stuff. Just find the open symbol
	// directly and use it...
	typedef int (open_func_t)( const char *pathname, int flags, mode_t mode );
	open_func_t *open_func = (open_func_t *)dlsym( RTLD_NEXT, "open" );

	if ( open_func )
	{
		for ( int i = 0; i < time; i++ )
		{
			int tracerpid = -1;

			int fd = (*open_func)( "/proc/self/status", O_RDONLY, S_IRUSR );
			if (fd >= 0)
			{
				char buf[ 4096 ];
				static const char tracerpid_str[] = "TracerPid:";

				const int len = read( fd, buf, sizeof(buf) - 1 );
				if ( len > 0 )
				{
					buf[ len ] = 0;

					const char *str = strstr( buf, tracerpid_str );
					tracerpid = str ? atoi( str + sizeof( tracerpid_str ) ) : -1;
				}

				close( fd );
			}

			if ( tracerpid > 0 )
				return true;

			sleep( 1 );
		}
	}

	return false;
}

static void WaitForDebuggerConnect( int argc, char *argv[], int time )
{
	for ( int i = 1; i < argc; i++ )
	{
		if ( strstr( argv[i], "-wait_for_debugger" ) )
		{
			printf( "\nArg -wait_for_debugger found.\nWaiting %dsec for debugger...\n", time );
			printf( "  pid = %d\n", getpid() );

			if ( IsDebuggerPresent( time ) )
				printf("Debugger connected...\n\n");

			break;
		}
	}
}

#else

static void WaitForDebuggerConnect( int argc, char *argv[], int time )
{
}

#endif // !LINUX

int main( int argc, char *argv[] )
{
	char ld_path[4196];
	char *path = "bin/";
	char *ld_env;

	if( (ld_env = getenv("LD_LIBRARY_PATH")) != NULL )
	{
		snprintf(ld_path, sizeof(ld_path), "%s:bin/", ld_env);
		path = ld_path;
	}

	setenv("LD_LIBRARY_PATH", path, 1);

	extern char** environ;
	if( getenv("NO_EXECVE_AGAIN") == NULL )
	{
		setenv("NO_EXECVE_AGAIN", "1", 1);
		execve(argv[0], argv, environ);
	}

	void *launcher = dlopen( "bin/liblauncher" DLL_EXT_STRING, RTLD_NOW );

	if( !launcher )
		launcher = dlopen( "bin/launcher" DLL_EXT_STRING, RTLD_NOW );

	if ( !launcher )
	{
		fprintf( stderr, "%s\nFailed to load the launcher\n", dlerror() );
		return 0;
	}

	LauncherMain_t main = (LauncherMain_t)dlsym( launcher, "LauncherMain" );
	if ( !main )
	{
		fprintf( stderr, "Failed to load the launcher entry proc\n" );
		return 0;
	}

#if defined(__clang__) && !defined(OSX)
	// When building with clang we absolutely need the allocator to always
	// give us 16-byte aligned memory because if any objects are tagged as
	// being 16-byte aligned then clang will generate SSE instructions to move
	// and initialize them, and an allocator that does not respect the
	// contract will lead to crashes. On Linux we normally use the default
	// allocator which does not give us this alignment guarantee.
	// The google tcmalloc allocator gives us this guarantee.
	// Test the current allocator to make sure it gives us the required alignment.
	void* pointers[20];
	for (int i = 0; i < ARRAYSIZE(pointers); ++i)
	{
		void* p = malloc( 16 );
		pointers[ i ] = p;
		if ( ( (size_t)p ) & 0xF )
		{
			printf( "%p is not 16-byte aligned. Aborting.\n", p );
			printf( "Pass /define:CLANG to VPC to correct this.\n" );
			return -10;
		}
	}
	for (int i = 0; i < ARRAYSIZE(pointers); ++i)
	{
		if ( pointers[ i ] )
			free( pointers[ i ] );
	}

	if ( __has_feature(address_sanitizer) )
	{
		printf( "Address sanitizer is enabled.\n" );
	}
	else
	{
		printf( "No address sanitizer!\n" );
	}
#endif

	WaitForDebuggerConnect( argc, argv, 30 );

	return main( argc, argv );
}

#else
#error
#endif // WIN32 || POSIX