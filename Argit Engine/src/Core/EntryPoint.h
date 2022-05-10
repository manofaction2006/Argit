#pragma once
#include "Application.h"
#include <chrono>

using namespace Argit;

int main() {
	Application* app = getApplication();

	app->OnInit();
	
	auto prev = std::chrono::high_resolution_clock::time_point{};

	do {
		if (std::chrono::high_resolution_clock::is_steady) {
			auto now = std::chrono::high_resolution_clock::now();
			auto result = std::chrono::duration_cast<std::chrono::milliseconds>(now - prev);
			float deltatime = result.count();
			app->OnUpdate(deltatime);
		}

	} while (app->isApplicationRunning());
	app->OnDestroy();

	delete app;
}