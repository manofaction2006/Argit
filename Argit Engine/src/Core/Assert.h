#pragma once
#include "Base.h"
#include "Log.h"


#ifdef ARGIT_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define ARGIT_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { ARGIT##type##ERROR(msg, __VA_ARGS__); ARGIT_DEBUGBREAK(); } }
#define ARGIT_INTERNAL_ASSERT_WITH_MSG(type, check, ...) ARGIT_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define ARGIT_INTERNAL_ASSERT_NO_MSG(type, check) ARGIT_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", ARGIT_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define ARGIT_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define ARGIT_INTERNAL_ASSERT_GET_MACRO(...) ARGIT_EXPAND_MACRO( ARGIT_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ARGIT_INTERNAL_ASSERT_WITH_MSG, ARGIT_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define ARGIT_ASSERT(...) ARGIT_EXPAND_MACRO( ARGIT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define ARGIT_CORE_ASSERT(...) ARGIT_EXPAND_MACRO( ARGIT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define ARGIT_ASSERT(...)
#define ARGIT_CORE_ASSERT(...)
#endif