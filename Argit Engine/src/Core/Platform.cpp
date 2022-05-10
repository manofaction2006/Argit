#include "pch.h"
#include "Platform.h"

#ifdef _WIN32
	#ifdef _WIN64
		Platform currentPlatform = Platform::Windows;
	#else
		Platform currentPlatform = Platform::Windows;
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		Platform currentPlatform = Platform::Ios;
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		Platform currentPlatform = Platform::Mac;
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)	
	Platform currentPlatform = Platform::Android;
	#error "Android is not supported!"
#elif defined(__linux__)
	Platform currentPlatform = Platform::Linux;
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif // End of platform detection