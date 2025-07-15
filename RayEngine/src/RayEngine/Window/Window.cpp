#include "raypch.h"

#include "RayEngine/Window/Window.h"

#include <raylib.h>

namespace RayEngine
{
	Window::Window(const WindowSpecification& specification) : m_Specification(specification)
	{

	}

	bool Window::Initialize()
	{
		InitWindow(m_Specification.Width, m_Specification.Height, m_Specification.Title);
		SetTargetFPS(60);

		return true;
	}

	void Window::Shutdown()
	{
		CloseWindow();
	}

	bool Window::ShouldClose() const
	{
		return WindowShouldClose();
	}

	void Window::PollEvents()
	{

	}
}