#include "imgui_impl_playstation3.h"


// Forward Declarations
static void ImGui_ImplPlaystation3_InitPlatformInterface();
static void ImGui_ImplPlaystation3_ShutdownPlatformInterface();

struct ImGui_ImplPlaystation3_Data
{
    bool                        HasGamepad;
    bool                        WantUpdateHasGamepad;

    ImGui_ImplPlaystation3_Data() { memset(this, 0, sizeof(*this)); }
};

// Backend data stored in io.BackendPlatformUserData to allow support for multiple Dear ImGui contexts
// It is STRONGLY preferred that you use docking branch with multi-viewports (== single Dear ImGui context + multiple windows) instead of multiple Dear ImGui contexts.
// FIXME: multi-context support is not well tested and probably dysfunctional in this backend.
// FIXME: some shared resources (mouse cursor shape, gamepad) are mishandled when using multi-context.
static ImGui_ImplPlaystation3_Data* ImGui_ImplPlaystation3_GetBackendData()
{
    return ImGui::GetCurrentContext() ? (ImGui_ImplPlaystation3_Data*)ImGui::GetIO().BackendPlatformUserData : NULL;
}


bool ImGui_ImplPlaystation3_Init()
{
    ImGuiIO& io = ImGui::GetIO();
    IM_ASSERT(io.BackendPlatformUserData == NULL && "Already initialized a platform backend!");

    // Setup backend capabilities flags
    ImGui_ImplPlaystation3_Data* bd = IM_NEW(ImGui_ImplPlaystation3_Data)();
    io.BackendPlatformUserData = (void*)bd;
    io.BackendPlatformName = "imgui_impl_playstation3";
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
    io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;    // We can create multi-viewports on the Platform side (optional)
    io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport; // We can call io.AddMouseViewportEvent() with correct data (optional)

    bd->WantUpdateHasGamepad = true;

    return true;
}

void ImGui_ImplPlaystation3_Shutdown()
{
    ImGui_ImplPlaystation3_Data* bd = ImGui_ImplPlaystation3_GetBackendData();
    IM_ASSERT(bd != NULL && "No platform backend to shutdown, or already shutdown?");
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplPlaystation3_ShutdownPlatformInterface();

    io.BackendPlatformName = NULL;
    io.BackendPlatformUserData = NULL;
    IM_DELETE(bd);
}

// This code supports multi-viewports (multiple OS Windows mapped into different Dear ImGui viewports)
// Because of that, it is a little more complicated than your typical single-viewport binding code!
static void ImGui_ImplPlaystation3_UpdateMouseData()
{

}

// Gamepad navigation mapping
static void ImGui_ImplPlaystation3_UpdateGamepads()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplPlaystation3_Data* bd = ImGui_ImplPlaystation3_GetBackendData();
    if ((io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) == 0)
        return;

    // Calling XInputGetState() every frame on disconnected gamepads is unfortunately too slow.
    // Instead we refresh gamepad availability by calling XInputGetCapabilities() _only_ after receiving WM_DEVICECHANGE.
    if (bd->WantUpdateHasGamepad)
    {
        bd->HasGamepad = true;
        bd->WantUpdateHasGamepad = false;
    }

    io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
    io.BackendFlags |= ImGuiBackendFlags_HasGamepad;

    /*io.AddKeyEvent(ImGuiKey_GamepadStart, XINPUT_GAMEPAD_START);
    io.AddKeyEvent(ImGuiKey_GamepadBack, XINPUT_GAMEPAD_BACK);
    io.AddKeyEvent(ImGuiKey_GamepadFaceDown, XINPUT_GAMEPAD_A);
    io.AddKeyEvent(ImGuiKey_GamepadFaceRight, XINPUT_GAMEPAD_B);
    io.AddKeyEvent(ImGuiKey_GamepadFaceLeft, XINPUT_GAMEPAD_X);
    io.AddKeyEvent(ImGuiKey_GamepadFaceUp, XINPUT_GAMEPAD_Y);
    io.AddKeyEvent(ImGuiKey_GamepadDpadLeft, XINPUT_GAMEPAD_DPAD_LEFT);
    io.AddKeyEvent(ImGuiKey_GamepadDpadRight, XINPUT_GAMEPAD_DPAD_RIGHT);
    io.AddKeyEvent(ImGuiKey_GamepadDpadUp, XINPUT_GAMEPAD_DPAD_UP);
    io.AddKeyEvent(ImGuiKey_GamepadDpadDown, XINPUT_GAMEPAD_DPAD_DOWN);
    io.AddKeyEvent(ImGuiKey_GamepadL1, XINPUT_GAMEPAD_LEFT_SHOULDER);
    io.AddKeyEvent(ImGuiKey_GamepadR1, XINPUT_GAMEPAD_RIGHT_SHOULDER);
    io.AddKeyAnalogEvent(ImGuiKey_GamepadL2, gamepad.bLeftTrigger, XINPUT_GAMEPAD_TRIGGER_THRESHOLD, 255);
    io.AddKeyAnalogEvent(ImGuiKey_GamepadR2, gamepad.bRightTrigger, XINPUT_GAMEPAD_TRIGGER_THRESHOLD, 255);
    io.AddKeyEvent(ImGuiKey_GamepadL3, XINPUT_GAMEPAD_LEFT_THUMB);
    io.AddKeyEvent(ImGuiKey_GamepadR3, XINPUT_GAMEPAD_RIGHT_THUMB);
    io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickLeft, gamepad.sThumbLX, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, -32768);
    io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickRight, gamepad.sThumbLX, +XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, +32767);
    io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickUp, gamepad.sThumbLY, +XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, +32767);
    io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickDown, gamepad.sThumbLY, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, -32768);
    io.AddKeyAnalogEvent(ImGuiKey_GamepadRStickLeft, gamepad.sThumbRX, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, -32768);
    io.AddKeyAnalogEvent(ImGuiKey_GamepadRStickRight, gamepad.sThumbRX, +XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, +32767);
    io.AddKeyAnalogEvent(ImGuiKey_GamepadRStickUp, gamepad.sThumbRY, +XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, +32767);
    io.AddKeyAnalogEvent(ImGuiKey_GamepadRStickDown, gamepad.sThumbRY, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, -32768);
    */
}

void ImGui_ImplPlaystation3_NewFrame()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplPlaystation3_Data* bd = ImGui_ImplPlaystation3_GetBackendData();
    IM_ASSERT(bd != NULL && "Did you call ImGui_ImplPlaystation3_Init()?");

    // Setup display size (every frame to accommodate for window resizing)
    io.DisplaySize = ImVec2(1920, 1080);

    // Setup time step

    // Update OS mouse position
    ImGui_ImplPlaystation3_UpdateMouseData();

    // Update game controllers (if enabled and available)
    ImGui_ImplPlaystation3_UpdateGamepads();
}

bool ImGui_ImplPlaystation3_HandleEvent()
{

    return true;
}

static void ImGui_ImplPlaystation3_InitPlatformInterface()
{

}

static void ImGui_ImplPlaystation3_ShutdownPlatformInterface()
{

}