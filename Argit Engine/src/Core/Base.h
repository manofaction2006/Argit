#pragma once
#include <memory>

#define ARGIT_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define ARGIT_EXPAND_MACRO(x) x
#define ARGIT_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

namespace Argit {
	template <typename T>
	using Reference = std::shared_ptr<T>;

	template <typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	Reference<T> MakeReference(Args&& ... arguments) {
		return std::make_shared<T>(std::forward<Args>(arguments)...);
	}

	template<typename T, typename ... Args>
	Scope<T> MakeScope(Args&& ... arguments) {
		return std::make_unique<T>(std::forward<Args>(arguments)...);
	}
}