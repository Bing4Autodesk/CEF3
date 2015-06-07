

/*! \file		vldapi.h
*	\brief		Visual Leak Detector APIs
*/
#pragma once

#include <windows.h>
#include "vlddef.h"

#ifdef __cplusplus		// Use undecorated names
extern "C" {
#endif // __cplusplus

// Define SAL macros to be empty if some old Visual Studio used
#ifndef __reserved
#define __reserved
#endif
#ifndef __in
#define __in
#endif
#ifndef __in_opt
#define __in_opt
#endif
#ifndef __out_ecount_z
#define __out_ecount_z(x)
#endif

#ifndef VLD_LIB // If VLD is used as DLL
#define VLD_DECLSPEC_DLLEXPORT __declspec(dllexport) 
#define VLD_DECLSPEC_DLLIMPORT __declspec(dllimport) 
#else // If VLD is used as static library
#define VLD_DECLSPEC_DLLEXPORT 
#define VLD_DECLSPEC_DLLIMPORT
#endif

	// This is needed for exporting/importing functions from/to VLD.dll
#ifdef VLD_EXPORTS
#define VLDAPI VLD_DECLSPEC_DLLEXPORT 
#else 
#define VLDAPI VLD_DECLSPEC_DLLIMPORT
#endif

/*! 	 
	\brief		Disables Visual Leak Detector's memory leak detection at
				runtime. If memory leak detection is already disabled, then calling this
				function has no effect.
  
	\return		None.
   
	\remarks 
				In multithreaded programs, this function operates on a per-thread
				basis. In other words, if you call this function from one thread, then
				memory leak detection is only disabled for that thread. If memory leak
				detection is enabled for other threads, then it will remain enabled for
				those other threads. It was designed to work this way to insulate you,
				the programmer, from having to ensure thread synchronization when calling
				VLDEnable() and VLDDisable(). Without this, calling these two functions
				unsynchronized could result in unpredictable and unintended behavior.
				But this also means that if you want to disable memory leak detection
				process-wide, then you need to call this function from every thread in
				the process.
*/
void VLDAPI VLDDisable ();

/*!  
	\brief		Enables Visual Leak Detector's memory leak detection at runtime.
				If memory leak detection is already enabled, which it is by default, then
				calling this function has no effect.
  
	\return		None.
   
	\remarks 
				In multithreaded programs, this function operates on a per-thread
				basis. In other words, if you call this function from one thread, then
				memory leak detection is only enabled for that thread. If memory leak
				detection is disabled for other threads, then it will remain disabled for
				those other threads. It was designed to work this way to insulate you,
				the programmer, from having to ensure thread synchronization when calling
				VLDEnable() and VLDDisable(). Without this, calling these two functions
				unsynchronized could result in unpredictable and unintended behavior.
				But this also means that if you want to enable memory leak detection
				process-wide, then you need to call this function from every thread in
				the process.
*/

void VLDAPI VLDEnable ();

/*!	 
	\brief		Restore Visual Leak Detector's previous state.
	\return		None.
*/
void VLDAPI VLDRestore ();

/*!	 
	\brief		Disables Visual Leak Detector's memory leak detection at
				runtime in all threads. If memory leak detection is already disabled, 
				then calling this function has no effect.
	\return		None.
*/
void VLDAPI VLDGlobalDisable ();

/*!	 
	\brief		Enables Visual Leak Detector's memory leak detection 
				at runtime in all threads. If memory leak detection is already enabled, 
				which it is by default, then calling this function has no effect.
	\return		None.
*/
void VLDAPI VLDGlobalEnable ();

/*!	 
	\brief		Report leaks up to the execution point.
	\return		UINT.
*/
UINT VLDAPI VLDReportLeaks ();

/*!	 
	\brief		Return memory leaks count to the execution point.
	\return		UINT.
*/
UINT VLDAPI VLDGetLeaksCount ();

/*!	 
	\brief		Mark all leaks as reported.
	\return		None.
*/
void VLDAPI VLDMarkAllLeaksAsReported();

/*!	 
	\brief		Look for recently loaded DLLs and patch them if necessary.
	\return		None.
*/
void VLDAPI VLDRefreshModules();

/*!		 
	\brief		Enable Memory leak checking on the specified module.
	\param[in]  module module handle.
	\return		None.
*/
void VLDAPI VLDEnableModule(HMODULE module);

/*!		 
	\brief		Disable Memory leak checking on the specified module.
	\param[in]  module module handle.
	\return		None.
*/
void VLDAPI VLDDisableModule(HMODULE module);

/*!		 
	\brief		Return all current options
	\return		Mask of current options.
*/
UINT VLDAPI VLDGetOptions();

/*!		 
	\brief		Return current report filename.
	\param[in]  filename current report filename (max characters - MAX_PATH).
	\return		None.
*/
void VLDAPI VLDGetReportFilename(WCHAR *filename);

/*!	 
	\brief		Return current report filename.
	\param[in]  option_mask Only the following flags are checked
				VLD_OPT_AGGREGATE_DUPLICATES
				VLD_OPT_MODULE_LIST_INCLUDE
				VLD_OPT_SAFE_STACK_WALK
				VLD_OPT_SLOW_DEBUGGER_DUMP
				VLD_OPT_TRACE_INTERNAL_FRAMES
				VLD_OPT_START_DISABLED
				VLD_OPT_SKIP_HEAPFREE_LEAKS
				VLD_OPT_VALIDATE_HEAPFREE
	\param[in]	maxDataDump  - maximum number of user-data bytes to dump for each leaked block, default 256.
	\param[in]	maxTraceFrames - maximum number of frames per stack trace for each leaked block, default 64.
	\return		None.
*/
void VLDAPI VLDSetOptions(UINT option_mask, SIZE_T maxDataDump, UINT maxTraceFrames);

/*!		 
	\brief		Set list of modules included/excluded in leak detection
				depending on parameter "includeModules".
	\param[in]  modules list of modules to be forcefully included/excluded in leak detection.
	\param[in]	includeModules include or exclude that modules.
	\return		None.
*/
void VLDAPI VLDSetModulesList(const WCHAR *modules, BOOL includeModules);

/*!		 
	\brief		Return current list of included/excluded modules
				depending on flag VLD_OPT_TRACE_INTERNAL_FRAMES.
	\param[in]  modules destination string for list of included/excluded modules (maximum length 512 characters).
	\param[in]	size maximum string size.
	\return		BOOL: TRUE if include modules, otherwise FALSE.
*/
BOOL VLDAPI VLDGetModulesList(WCHAR *modules, UINT size);

/*!	 
	\brief		Update the report options via function call rather than INI file.
	\param[in]  option_mask Only the following flags are checked
				VLD_OPT_REPORT_TO_DEBUGGER
				VLD_OPT_REPORT_TO_FILE
				VLD_OPT_REPORT_TO_STDOUT
				VLD_OPT_UNICODE_REPORT
	\param[in]	filename is optional and can be NULL.
	\return		None.
*/
void VLDAPI VLDSetReportOptions(UINT option_mask, const WCHAR *filename);

/*!		 
	\brief		Installs or uninstalls a client-defined reporting function by hooking it 
				into the C run-time debug reporting process (debug version only).
	\param[in]  mode The action to take: VLD_RPTHOOK_INSTALL or VLD_RPTHOOK_REMOVE.
	\param[in]	pfnNewHook Report hook to install or remove.
	\return		int: 0 if success.
*/
int VLDAPI VLDSetReportHook(int mode,  VLD_REPORT_HOOK pfnNewHook);

/*!		 
	\brief		Performs symbol resolution for all saved extent CallStack's that have
				been tracked by Visual Leak Detector. This function is necessary for applications that 
				dynamically load and unload modules, and through which memory leaks might be included.
				If this is NOT called, stack traces may have stack frames with no symbol information. This 
				happens because the symbol API's cannot look up symbols for a binary / module that has been unloaded
	\return		None.
*/
void VLDAPI VLDResolveCallstacks();

#ifdef __cplusplus
}
#endif // __cplusplus
