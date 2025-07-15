#pragma once

#include "RayEngine/Core/Application.h"

namespace RayEngine
{
	Application* CreateApplication(ApplicationCommandLineArgs args);
}

int main(int args, char** argv)
{
	auto app = RayEngine::CreateApplication({ args, argv });

	app->Run();

	delete app;

	return 0;
}