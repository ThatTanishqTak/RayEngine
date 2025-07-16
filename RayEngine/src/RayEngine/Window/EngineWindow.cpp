#include "raypch.h"
#include "RayEngine/Window/EngineWindow.h"

namespace RayEngine
{
	EngineWindow::EngineWindow(const WindowSpecification& specification) : m_Specification(specification)
	{

	}


	bool EngineWindow::Initialize()
	{
		InitWindow(m_Specification.Width, m_Specification.Height, m_Specification.Title);
		SetWindowState(FLAG_WINDOW_RESIZABLE);
		SetVSync(m_Specification.VSync);
		m_Window = GetWindowHandle();

		if (!IsWindowReady())
		{
			return false;
		}

		SetTargetFPS(60);

		return true;
	}

	void EngineWindow::Shutdown()
	{
		if (IsWindowReady())
		{
			CloseWindow();
		}
	}

	bool EngineWindow::ShouldClose() const
	{
		return WindowShouldClose();
	}

	void EngineWindow::PollEvents()
	{
		PollInputEvents();
	}

	void EngineWindow::SetVSync(bool enabled)
	{
		m_Specification.VSync = enabled;
		if (enabled)
		{
			SetTargetFPS(60);
		}

		else
		{
			SetTargetFPS(0);
		}
	}

	void EngineWindow::SetTitle(const char* title)
	{
		m_Specification.Title = title;
		SetWindowTitle(title);
	}
}