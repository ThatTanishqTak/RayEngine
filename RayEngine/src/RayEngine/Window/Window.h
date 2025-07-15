#pragma once

namespace RayEngine
{
	struct WindowSpecification
	{
		const char* Title;

		int Width;
		int Height;
	};

	class Window
	{
	public:
		Window() = default;
		Window(const WindowSpecification& specification);
		~Window() = default;

		bool Initialize();
		void Shutdown();

		bool ShouldClose() const;
		void PollEvents();

	private:
		WindowSpecification m_Specification{};
		
		void* m_Window = nullptr;
	};
}