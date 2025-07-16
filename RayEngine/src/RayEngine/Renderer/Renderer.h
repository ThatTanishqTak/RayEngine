#pragma once

namespace RayEngine
{
	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		bool Initialize();
		void Shutdown();

		void BeginFrame();
		void EndFrame();

	private:

	};
}