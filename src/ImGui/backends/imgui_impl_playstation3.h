
#include "ImGui/imgui.h"      // IMGUI_IMPL_API

IMGUI_IMPL_API bool     ImGui_ImplPlaystation3_Init(NSView* _Nonnull view);
IMGUI_IMPL_API void     ImGui_ImplPlaystation3_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplPlaystation3_NewFrame(NSView* _Nullable view);
IMGUI_IMPL_API bool     ImGui_ImplPlaystation3_HandleEvent(NSEvent* _Nonnull event, NSView* _Nullable view);