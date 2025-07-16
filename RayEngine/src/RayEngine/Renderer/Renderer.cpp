#include "raypch.h"

#include "RayEngine/Renderer/Renderer.h"

#include <raylib.h>

namespace RayEngine
{
	bool Renderer::Initialize()
	{
		return true;
	}

	void Renderer::Shutdown()
	{

	}

	void Renderer::BeginFrame()
	{
		BeginDrawing();
		ClearBackground(BLACK);
	}

	void Renderer::EndFrame()
	{
		EndDrawing();
	}
}