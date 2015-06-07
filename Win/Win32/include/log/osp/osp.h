
#ifndef _OSP_H
#define _OSP_H

// for Microsoft c++
#ifdef _MSC_VER

//╫Тееап
#ifndef _EQUATOR_
#pragma pack(push)
#pragma pack(1)
#endif

#define API extern "C"			__declspec(dllexport)
#define OSP_API 				__declspec(dllexport)

// for gcc
#else

#define API extern "C"
#define OSP_API

#endif	// _MSC_VER

#ifdef _MSC_VER

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#if _MSC_VER <= 1200
#define _WIN32_WINNT 0x0400
#else
#define _WIN32_WINNT 0x0501
#endif

#ifdef WINVER
#undef WINVER
#endif
#if _MSC_VER <= 1200
#define WINVER 0x0400
#else
#define WINVER 0x0501
#endif

#include <malloc.h>
#include <time.h>

#ifdef _AFXDLL
#include <afx.h>
#include <afxwin.h>
#include <winsock2.h>
#else
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#endif

#include <assert.h>
#pragma comment(lib,"Ws2_32.lib")

#endif	// _MSC_VER

#ifdef __linux__

typedef int 				 BOOL;
#define TRUE				 1
#define FALSE				 0

#endif	// __linux__

API void OspPrintf(BOOL bScreen, BOOL bFile, char * szFormat,...);

API BOOL OspInit(BOOL TelNetEnable=FALSE, unsigned short TelNetPort=0, char* pchModuleName = NULL );

#endif // _OSP_H
