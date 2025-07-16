#pragma once

#include "RayEngine/Utilities/Utilities.h"
#include "RayEngine/Core/Application.h"

namespace RayEngine
{
	Application* CreateApplication(ApplicationCommandLineArgs args);
}

int main(int args, char** argv)
{
	RayEngine::Utilities::Log::Init();

	auto app = RayEngine::CreateApplication({ args, argv });

	app->Run();

	delete app;

	return 0;
}