#pragma once

#include "RayEngine/Utilities/Utilities.h"
#include "RayEngine/Core/Application.h"

// Engine entry point hooking into client application.
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