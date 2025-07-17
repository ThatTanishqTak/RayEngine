#pragma once

// EditorLayer.h: Defines the EditorLayer class used to implement the editor-specific UI and functionality

#include <iostream> // For basic console output and debugging

// TODO: Forward-declare application and rendering classes to reduce compile-time dependencies

// The EditorLayer class will be responsible for initializing
// and handling the UI panels, viewport, and editor events.
// It inherits from the base Layer class defined in the engine core.

// Example forward declarations (uncomment and adjust as needed):
// class Layer;
// namespace RayEngine { class Application; class Renderer; }

// class EditorLayer : public Layer
// {
// public:
//     EditorLayer();
//     ~EditorLayer();
//
//     void OnAttach() override;   // Called when the layer is added to the layer stack
//     void OnDetach() override;   // Called when the layer is removed from the layer stack
//     void OnUpdate(Timestep ts) override; // Called every frame with time-step info
//     void OnImGuiRender() override;      // Called to draw ImGui UI elements
//
// private:
//     // Add editor-specific state here (e.g., selected entity, scene reference)
// };

// Including Layer.h or other dependencies can be done when implementation details are known