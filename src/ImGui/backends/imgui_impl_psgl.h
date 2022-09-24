

#include "ImGui/imgui.h"      // IMGUI_IMPL_API

IMGUI_API bool        ImGui_ImplPSGL_Init();
IMGUI_API void        ImGui_ImplPSGL_Shutdown();
IMGUI_API void        ImGui_ImplPSGL_NewFrame();
IMGUI_API void        ImGui_ImplPSGL_RenderDrawData(ImDrawData* draw_data);
IMGUI_API bool        ImGui_ImplPSGL_ProcessEvent(SceCtrlData* pad);

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void        ImGui_ImplPSGL_InvalidateDeviceObjects();
IMGUI_API bool        ImGui_ImplPSGL_CreateDeviceObjects();