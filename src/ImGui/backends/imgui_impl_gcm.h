#pragma once
#include "ImGui/imgui.h"

IMGUI_API bool        ImGui_ImplGcm_Init();
IMGUI_API void        ImGui_ImplGcm_Shutdown();
IMGUI_API void        ImGui_ImplGcm_NewFrame();
IMGUI_API void        ImGui_ImplGcm_RenderDrawData(ImDrawData* draw_data);

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void        ImGui_ImplGcm_DestroyDeviceObjects();
IMGUI_API void        ImGui_ImplGcm_InvalidateDeviceObjects();
IMGUI_API bool        ImGui_ImplGcm_CreateDeviceObjects();