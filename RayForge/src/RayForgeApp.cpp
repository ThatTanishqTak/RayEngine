#include "RayEngine/Core/Application.h" // Core Application interface for initializing and running the engine
#include "RayEngine/Core/EntryPoint.h" // Defines the platform-specific entry point macro

#include "EditorLayer.h" // Custom layer for editor UI and interaction

namespace RayEngine
{
    // RayForge: Derives from the base Application class to customize the editor application
    class RayForge : public Application
    {
    public:
        // Constructor: forwards application specifications to the base Application
        RayForge(const ApplicationSpecification& specs) : Application(specs) // Initialize base Application members
        {
            // Add any RayForge-specific initialization here
        }
    };

    // CreateApplication: Engine calls this factory function to instantiate the client application
    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        ApplicationSpecification specs; // Configuration for window title, size, VSync, and CLI args

        specs.Name = "RayForge"; // Window title displayed by the OS
        specs.Width = 1920; // Default editor window width
        specs.Height = 1080; // Default editor window height
        specs.CommandLineArgs = args; // Pass through any CLI arguments for custom handling
        specs.VSync = true; // Enable vertical sync to cap framerate and reduce tearing

        // Return a new instance of our custom RayForge application
        return new RayForge(specs);
    }
}