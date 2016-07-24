	// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_system.h"

#ifdef TB_TARGET_MACOSX

#include <sys/time.h>
#include <stdio.h>

//Includes native mac functions such as CoreGraphics used in this case
#include <ApplicationServices/ApplicationServices.h>
#include <AppKit/AppKit.h>

void(*TBDebugCallback)(const char* str) = nullptr;

#ifdef TB_RUNTIME_DEBUG_INFO

void TBDebugOut(const char *str)
{
	if (TBDebugCallback == nullptr)
		printf("%s", str);
	else
		TBDebugCallback(str);
}

#endif // TB_RUNTIME_DEBUG_INFO

namespace tb {
	
	// == TBSystem ========================================
	
	static NSWindow* _windowHandle; // not part of TBSystem, but static to this compiled object
	
	double TBSystem::GetTimeMS()
	{
		struct timeval now;
		gettimeofday( &now, NULL );
		return now.tv_usec/1000 + now.tv_sec*1000;
	}
	
	// Implementation currently done in port_glfw.cpp.
	// FIX: Implement here for linux-desktop/android/macos?
	//void TBSystem::RescheduleTimer(double fire_time)
	//{
	//}
	
	int TBSystem::GetLongClickDelayMS()
	{
		return 500;
	}
	
	int TBSystem::GetPanThreshold()
	{
		return 5 * GetDPI() / 96;
	}
	
	int TBSystem::GetPixelsPerLine()
	{
		return 40 * GetDPI() / 96;
	}
	
	int TBSystem::GetDPI()
	{
		CGFloat f = [_windowHandle backingScaleFactor];
		
		return 96 * f;
	}
	
	void TBSystem::SetWindow(void *window_handle){
		_windowHandle = (NSWindow*)window_handle;
	}
	
} // namespace tb

#endif // TB_TARGET_MACOSX
