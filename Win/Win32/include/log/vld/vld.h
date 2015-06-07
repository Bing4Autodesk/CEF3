
/*! 
	\file		vld.h
*	\brief		Visual Leak Detector main head file
*/
#pragma once

#if defined _DEBUG || defined VLD_FORCE_ENABLE

#include "vldapi.h"

#pragma comment(lib, "vld.lib")

// Force a symbolic reference to the global VisualLeakDetector class object from
// the DLL. This ensures that the DLL is loaded and linked with the program,
// even if no code otherwise imports any of the DLL's exports.
#pragma comment(linker, "/include:__imp_?g_vld@@3VVisualLeakDetector@@A")

#else // !_debug

#define VLDEnable()
#define VLDDisable()
#define VLDRestore()
#define VLDGlobalDisable()
#define VLDGlobalEnable()
#define VLDReportLeaks() 0
#define VLDGetLeaksCount() 0
#define VLDMarkAllLeaksAsReported()
#define VLDRefreshModules()
#define VLDEnableModule(a)
#define VLDDisableModule(b)
#define VLDGetOptions() 0
#define VLDGetReportFilename(a)
#define VLDSetOptions(a, b, c)
#define VLDSetReportHook(a, b)
#define VLDSetModulesList(a)
#define VLDGetModulesList(a, b) false
#define VLDSetReportOptions(a, b)
#define VLDResolveCallstacks()

#endif // _debug
