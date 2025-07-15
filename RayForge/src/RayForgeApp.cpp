#include "RayEngine.h"
#include "RayEngine/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace RayEngine
{
	class RayForge : public Application
	{
	public:
		RayForge(const ApplicationSpecification& specs) : Application(specs)
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification specs;

		specs.Name = "RayForge";
		specs.Width = 1920;
		specs.Height = 1080;
		specs.CommandLineArgs = args;
		specs.VSync = true;

		return new RayForge(specs);
	}
}