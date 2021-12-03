#pragma once
#include <string>
#include "Enums.hpp"
#include "Game.hpp"

#include "Engine/gamemode/GameMode.h"
#include "Engine/client/Minecraft.h"
#include "Engine/entity/player/ServerPlayer.h"
#include "Engine/world/entity/DamageSource.h"
#include "Engine/util/Direction.h"
#include "Engine/world/level/block/BlockPos.h"
#include "Engine/client/gui/GuiComponent.h"

class Helpers
{
public:
   // host only
   bool selfInvulnerability = false;

   float visualFov = 100.0f;

   float movmentJumpMotion = 0.90f;

   // host only
   bool combatOneHitKill = false;


   int nukerSize = 50;
   bool nuker = false;

   bool frostWalker = false;
};


void DrawText(const std::wstring& text, uint32_t x, uint32_t y, Color color);
void DrawShadowText(const std::wstring& text, uint32_t x, uint32_t y, Color color, bool centered);
void DrawRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color);
void DrawGradient(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color colorTop, Color colorBottom);
void DisplayKeyboard(const std::wstring& title, const std::wstring& defaultText, size_t maxInputLength, void* callback);
std::string GetKeyboardResult();
int GetControlValue(eButtons button);
bool ButtonPressed(eButtons button);
bool ButtonDown(eButtons button);
bool IsButtonBinds(eButtons button1, eButtons button2);
double GetLeftJoyStickX();
double GetLeftJoyStickY();
double GetRightJoyStickX();
double GetRightJoyStickY();
bool IsEntitySelf(void* entity);
Entity* GetEntityById(int id);
void DebugLocalPlayer();
void PlayUISoundBack();
void PlayUISoundSelect();
void PlayUISoundScroll();

extern Helpers g_Helpers;
extern MultiPlayerLevel* g_Level;
extern MultiplayerLocalPlayer* g_Localplayer;
extern Minecraft* g_Minecraft;
extern MultiPlayerGameMode* g_Gamemode;
extern GuiComponent* g_GuiComponent;