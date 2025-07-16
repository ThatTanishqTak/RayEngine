#pragma once

namespace RayEngine
{
    struct WindowSpecification
    {
        const char* Title;

        int Width;
        int Height;
        bool VSync = false;
    };

    class EngineWindow
    {
    public:
        EngineWindow() = default;
        EngineWindow(const WindowSpecification& specification);
        ~EngineWindow() = default;

        bool Initialize();
        void Shutdown();

        void SetVSync(bool enabled);
        bool IsVSync() const { return m_Specification.VSync; }

        void SetTitle(const char* title);

        int GetWidth() const { return m_Specification.Width; }
        int GetHeight() const { return m_Specification.Height; }

        void* GetNativeWindow() const { return m_Window; }

        bool ShouldClose() const;
        void PollEvents();

    private:
        WindowSpecification m_Specification{};

        void* m_Window = nullptr;
    };
}