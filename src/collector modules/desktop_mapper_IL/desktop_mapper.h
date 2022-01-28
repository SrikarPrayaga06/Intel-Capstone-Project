/**
*** INTEL CONFIDENTIAL
*** 
*** Copyright (March 2011) (March 2011) Intel Corporation All Rights Reserved. 
*** The source code contained or described herein and all documents related to the
*** source code ("Material") are owned by Intel Corporation or its suppliers or 
*** licensors. Title to the Material remains with Intel Corporation or its 
*** suppliers and licensors. The Material contains trade secrets and proprietary 
*** and confidential information of Intel or its suppliers and licensors. 
*** The Material is protected by worldwide copyright and trade secret laws 
*** and treaty provisions. No part of the Material may be used, copied, 
*** reproduced, modified, published, uploaded, posted, transmitted, distributed,
*** or disclosed in any way without Intel's prior express written permission.
***
*** No license under any patent, copyright, trade secret or other intellectual
*** property right is granted to or conferred upon you by disclosure or delivery
*** of the Materials, either expressly, by implication, inducement, estoppel or
*** otherwise. Any license under such intellectual property rights must be 
*** express and approved by Intel in writing.
**/

#ifndef __INCLUDE_PURE_EVENT_DRIVEN_INCREMENTING_INPUT__
#define __INCLUDE_PURE_EVENT_DRIVEN_INCREMENTING_INPUT__

//-----------------------------------------------------------------------------
// Headers inclusions.
//-----------------------------------------------------------------------------
#include <windows.h>
#include "pub_intel_modeler.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*--------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// Defines.
//-----------------------------------------------------------------------------
#define STRING_BUFFERS_SIZE 1024
#define MAX_MPLEX_LOGGER_CHECKS 10
#define MAX_WINDOWS 10
#define WAIT_FOR_MULTIPLEX_LOGGER_TIME_IN_MS 1000
#define LOGGER_MAX_LOG_TRIES 10
#define LOG_RETRY_PAUSE_IN_MS 100
#define INPUT_PAUSE_IN_MS 1000 // does not accept floating point
#define INPUT_COUNT 21
	#define INPUT_EXECUTABLE 0
	#define INPUT_WINDOW_TITLE 1
	#define INPUT_CURRENT_WINDOW 2
	#define INPUT_NEXT_WINDOW 3
	#define INPUT_PREV_WINDOW 4
	#define INPUT_FOREGROUND_WINDOW 5
	#define INPUT_SHELL_WINDOW 6
	#define INPUT_DESKTOP_WINDOW 7
	#define INPUT_IS_HUNG 8
	#define INPUT_IS_ZOOMED 9
	#define INPUT_IS_OCCULTED 10
	#define INPUT_IS_VISIBLE 11
	#define INPUT_IS_MINIMIZED 12
	#define INPUT_IS_WINDOW_UNICODE 13
	#define INPUT_WINDOW_RECT 14
	#define INPUT_CLIENT_RECT 15
	#define INPUT_WINDOW_PLACEMENT 16
	#define INPUT_WINDOW_STYLE 17
	#define INPUT_WINDOW_STYLE_EX 18
	#define INPUT_WINDOW_MONITOR 19
	#define INPUT_MONITOR_INFO 20

#define INPUT_NAME_STRING "DESKTOP-MAPPER"
#define MY_INPUT_CLOSE_ERROR_STRINGS \
	"Dynamic Error 1"
#define INPUT_DESCRIPTION_STRINGS \
	"Executable Name", \
	"Current Window Title", \
	"Current Window Handle", \
	"Next Window Handle", \
	"Previous Window Handle", \
	"Foreground Window HandleHandle", \
	"Shell Window Handle", \
	"Desktop Window Handle", \
	"Window is Hung", \
	"Window is Zoomed", \
	"Window is Visible", \
	"Window is Occulted", \
	"Window is Minimized", \
	"Window is Unicode", \
	"Window Rectangle", \
	"Client Window Rectangle", \
	"Window Style", \
	"Window Style Ex", \
	"Window Placement", \
	"Window Monitor", \
	"Window Monitor Info", \

#define INPUT_TYPES \
	STRING_COUNTER, \
	STRING_COUNTER, \
	STRING_COUNTER, \
	STRING_COUNTER, \
	STRING_COUNTER, \
	STRING_COUNTER, \
	STRING_COUNTER, \
	STRING_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER, \
	ULL_COUNTER

#define WAIT_EVENTS_COUNT (2)
	#define STOP_EVENT_INDEX (0)
	#define FOREGROUND_WINDOW_CHANGE_INDEX (1)

//-----------------------------------------------------------------------------
// Structs
//-----------------------------------------------------------------------------
typedef struct {
	DWORD ownerpid;
	DWORD childpid;
} windowinfo;

typedef struct _windows_structure {
	TCHAR executable[STRING_BUFFERS_SIZE]; //1024 bytes
	TCHAR className[STRING_BUFFERS_SIZE];
	HWND currentWindow;
	HWND nextWindow;
	HWND prevWindow;
	HWND foregroundWindow;
	HWND shellWindow;
	HWND desktopWindow;
	BOOL isOcculted;
	BOOL isVisible;
	BOOL isMinimized;
	BOOL isHung;
	BOOL isZoomed;
	BOOL isWindowUnicode;
	RECT windowRect;
	RECT clientRect;
	WINDOWPLACEMENT placement;
	LONG_PTR style;
	LONG_PTR style_ex;
	HMONITOR monitor;
	MONITORINFO monitorInfo;
} WINDOWS_STRUCTURE, * PWINDOWS_STRUCTURE;

//-----------------------------------------------------------------------------
// Child Windows Callback Function.
//-----------------------------------------------------------------------------

BOOL CALLBACK EnumChildWindowsCallback(HWND hWnd, LPARAM lp) {
	windowinfo* info = (windowinfo*)lp;
	DWORD pid = 0;
	GetWindowThreadProcessId(hWnd, &pid);
	if (pid != info->ownerpid) info->childpid = pid;
	return TRUE;
}

//-----------------------------------------------------------------------------
// Function prototypes.
//-----------------------------------------------------------------------------
ESRV_API ESRV_STATUS modeler_init_inputs(
	unsigned int *, 
	int *, 
	int *, 
	char *,
	size_t
);
ESRV_API ESRV_STATUS modeler_open_inputs(PINTEL_MODELER_INPUT_TABLE);
ESRV_API ESRV_STATUS modeler_close_inputs(PINTEL_MODELER_INPUT_TABLE);
ESRV_STATUS modeler_read_inputs(PINTEL_MODELER_INPUT_TABLE);
ESRV_STATUS modeler_listen_inputs(PINTEL_MODELER_INPUT_TABLE);
ESRV_STATUS modeler_process_dctl(PINTEL_MODELER_INPUT_TABLE);
ESRV_STATUS modeler_process_lctl(PINTEL_MODELER_INPUT_TABLE);
//-----------------------------------------------------------------------------
ESRV_API unsigned int __stdcall custom_desktop_thread(void*);
ESRV_API unsigned int __stdcall custom_logger_thread(void*);
ESRV_STATUS get_window_info(WINDOWS_STRUCTURE*);

void get_process_image_name(HWND, TCHAR*, DWORD);
void map_desktop();
ESRV_STATUS multiplex_logging(PINTEL_MODELER_INPUT_TABLE, WINDOWS_STRUCTURE*);

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_PURE_EVENT_DRIVEN_INCREMENTING_INPUT__
