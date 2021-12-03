#include "Helpers.hpp"

Helpers g_Helpers;
MultiPlayerLevel* g_Level;
MultiplayerLocalPlayer* g_Localplayer;
Minecraft* g_Minecraft;
MultiPlayerGameMode* g_Gamemode;
GuiComponent* g_GuiComponent;

void DrawText(const std::wstring& text, uint32_t x, uint32_t y, Color color)
{
   g_GameVariables->Font_draw(g_Minecraft->m_fontRender, text, x, y, color.ToHex());
}

void DrawShadowText(const std::wstring& text, uint32_t x, uint32_t y, Color color, bool centered)
{
   if (centered)
      g_GameVariables->GuiComponent_drawCenteredString(g_GuiComponent, g_Minecraft->m_fontRender, text, x, y, color.ToHex());
   else
      g_GameVariables->GuiComponent_drawString(g_GuiComponent, g_Minecraft->m_fontRender, text, x, y, color.ToHex());
}

void DrawRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color)
{
   g_GameVariables->GuiComponent_fill(g_GuiComponent, x, y, width, height, color.ToHex());
}

void DrawGradient(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color colorTop, Color colorBottom)
{
   g_GameVariables->GuiComponent_fillGradient(g_GuiComponent, x, y, width, height, colorTop.ToHex(), colorBottom.ToHex());
}

void DisplayKeyboard(const std::wstring& title, const std::wstring& defaultText, size_t maxInputLength, void* callback)
{
   g_GameVariables->CInput_RequestKeyboard(*g_GameVariables->pCInput, title.c_str(), defaultText.c_str(), 0, maxInputLength, callback, 0, 0);
}

std::string GetKeyboardResult()
{
   wchar_t keyboardResult[500];
   g_GameVariables->CInput_GetText(*g_GameVariables->pCInput, keyboardResult, sizeof(keyboardResult));

   std::wstring resultWString = std::wstring(keyboardResult);
   std::string text(resultWString.begin(), resultWString.end());

   return text;
}

int GetControlValue(eButtons button)
{
   return g_GameVariables->CInput_GetValue(*g_GameVariables->pCInput, 0, button, true);
}

bool ButtonPressed(eButtons button)
{
   return g_GameVariables->CInput_ButtonPressed(*g_GameVariables->pCInput, 0, button, 0);
}

bool ButtonDown(eButtons button)
{
   return g_GameVariables->CInput_ButtonDown(*g_GameVariables->pCInput, 0, button);
}

bool IsButtonBinds(eButtons button1, eButtons button2)
{
   return (ButtonPressed(button1) && ButtonDown(button2))
      || (ButtonDown(button1) && ButtonPressed(button2));
}

double GetLeftJoyStickX()
{
   return g_GameVariables->CInput_GetJoyStick_LX(*g_GameVariables->pCInput, 0, 0);
}

double GetLeftJoyStickY()
{
   return g_GameVariables->CInput_GetJoyStick_LY(*g_GameVariables->pCInput, 0, 0);
}

double GetRightJoyStickX()
{
   return g_GameVariables->CInput_GetJoyStick_RX(*g_GameVariables->pCInput, 0, 0);
}

double GetRightJoyStickY()
{
   return g_GameVariables->CInput_GetJoyStick_RY(*g_GameVariables->pCInput, 0, 0);
}

bool IsEntitySelf(void* entity)
{
   //g_GameVariables->Entity_is(entity, g_Localplayer);
   if (entity == g_Localplayer)
      return true;

   return false;
}

Entity* GetEntityById(int id)
{
   uintptr_t entity[2];
   g_GameVariables->MultiPlayerLevel_getEntity(entity, g_Level, id);

   return (Entity*)entity[0];
}

void DebugLocalPlayer()
{
   int id = g_GameVariables->Minecraft_getLocalPlayerIdx(g_Minecraft);

   printf("id 0x%X\n", id);

   Entity* entity = GetEntityById(id);

   printf("entity 0x%X\n", entity);
}

void PlayUISoundBack()
{
   g_GameVariables->ConsoleUIController_PlayUISFX(g_GameVariables->ConsoleUIController, *g_GameVariables->pSoundEventBack);
}

void PlayUISoundSelect()
{
   g_GameVariables->ConsoleUIController_PlayUISFX(g_GameVariables->ConsoleUIController, *g_GameVariables->pSoundEventPress);
}

void PlayUISoundScroll()
{
   g_GameVariables->ConsoleUIController_PlayUISFX(g_GameVariables->ConsoleUIController, *g_GameVariables->pSoundEventScroll);
}