#pragma once
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include "Memory/Pattern.hpp"
#include "Engine/util/Color.h"

#define MAKE_FN(addr, ret_type, name, args)	\
private: \
    uint32_t name##Opd[2] = { addr, GetCurrentToc() }; \
public: \
    using name##_t = ret_type(*)args;	\
    name##_t name = (name##_t)name##Opd;

class GameVariables
{
public:

   MAKE_FN(0xCB9910, int, __printf, (const char* format, ...));

   MAKE_FN(0xCB9A10, int, __snprintf, (char* s, size_t n, const char* format, ...));

   MAKE_FN(0xCCAE60, void, ___Assert, (const char* r3, const char* r4));

   MAKE_FN(0xAE4CD8, uint32_t, MultiPlayerGameMode_useItemOn, (void* gameMode, void* player, void* level, void* blockPos, void* direction, void* pos, uint32_t interactionHand, bool unk1, bool* unk2));

   MAKE_FN(0xB33A08, void, MultiPlayerGameMode_tick, (void* multiPlayerGameMode));

   MAKE_FN(0xAE1B00, uint32_t, MultiPlayerLevel_setLevel, (void* minecraft, void* level, uint32_t levelHash, uint32_t levelStorage, uint32_t r7, uint32_t r8));
   
   MAKE_FN(0xAE1A04, uint32_t, MultiPlayerGameMode_initPlayer, (void* gameMode, void* player));

   MAKE_FN(0xAEEC00, void, Minecraft_runMiddle, (void* minecraft));

   MAKE_FN(0xAE85CC, uint32_t, MultiPlayerGameMode_attack, (void* gamemode, void* player, void* entity));

   MAKE_FN(0x39F018, uint32_t, LivingEntity_onChangedBlock, (void* entity, void* pos));

   MAKE_FN(0x3AA788, float, LivingEntity_getJumpPower, (void* entity));

   MAKE_FN(0xA96E90, float, GameRenderer_GetFov, (void* gameRenderer, float datFloat, int datBoolean));

   MAKE_FN(0x4A8548, bool, Player_Hurt, (void* serverPlayer, void* damageSource, float damage));

   MAKE_FN(0x3A7F48, void, LivingEntity_actuallyHurt, (void* entity, void* entityDamageSource, float damage));

   MAKE_FN(0x4A94B8, void, Player_actuallyHurt, (void* player, void* damageSource, float damage));

   MAKE_FN(0xB34A6C, void, MultiPlayerGameMode_destroyBlock, (void* gamemode, void* blockPos));

   MAKE_FN(0xC619E0, int, CInput_GetValue, (uintptr_t cinput, uint32_t unk, uint8_t button, uint32_t r6));

   MAKE_FN(0xC61D04, bool, CInput_ButtonPressed, (uintptr_t cinput, uint32_t unk, uint8_t button, uint32_t r6));

   MAKE_FN(0xC61EEC, bool, CInput_ButtonReleased, (uintptr_t cinput, uint32_t unk, uint8_t button, uint32_t r6));

   MAKE_FN(0xC61F84, bool, CInput_ButtonDown, (uintptr_t cinput, uint32_t unk, uint8_t button));

   MAKE_FN(0xC62490, double, CInput_GetJoyStick_LX, (uintptr_t cinput, uint8_t button, bool r5));
   
   MAKE_FN(0xC62500, double, CInput_GetJoyStick_LY, (uintptr_t cinput, uint8_t button, bool r5));
   
   MAKE_FN(0xC62570, double, CInput_GetJoyStick_RX, (uintptr_t cinput, uint8_t button, bool r5));

   MAKE_FN(0xC625E0, double, CInput_GetJoyStick_RY, (uintptr_t cinput, uint8_t button, bool r5));

   MAKE_FN(0xC62B80, bool, CInput_RequestKeyboard, (uintptr_t cinput, const wchar_t* title, const wchar_t* initText, uint32_t _zero, size_t length, void* callback, uint64_t param, uint32_t unk));

   MAKE_FN(0xC62CFC, int, CInput_GetText, (uintptr_t cinput, wchar_t* outBuffer, size_t bufferSize));

   MAKE_FN(0xA98E30, void, GameRenderer_getFovAndAspect, (void* gameRenderer, float* fov, float* aspectRatio, uint32_t r6, bool someFovBool));

   MAKE_FN(0xA89068, void, GameRenderer_setupGuiScreen, (uintptr_t r3, uint32_t r4));

   MAKE_FN(0xA891F0, void, Gui_render, (void* guiComponent, double unk));

   MAKE_FN(0xA7E2E8, bool, Font_drawShadowRaw, (uintptr_t font, const std::wstring& text, uint32_t x, uint32_t y, uint32_t color, uint32_t dropShadow, uint32_t r9));

   MAKE_FN(0xAA4794, bool, Font_draw, (uintptr_t font, const std::wstring& text, uint32_t x, uint32_t y, uint32_t color));

   MAKE_FN(0xA7DB38, int, Font_width, (uintptr_t font, const std::wstring& text));

   MAKE_FN(0xA7E5DC, bool, GuiComponent_drawString, (void* guiComponent, uintptr_t font, const std::wstring& text, uint32_t x, uint32_t y, uint32_t color));

   MAKE_FN(0xA7E520, bool, GuiComponent_drawCenteredString, (void* guiComponent, uintptr_t font, const std::wstring& text, uint32_t x, uint32_t y, uint32_t color));

   MAKE_FN(0xA7D278, void, GuiComponent_fillGradient, (void* guiComponent, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color1, uint32_t color2));

   MAKE_FN(0xA7CE80, void, GuiComponent_fill, (void* guiComponent, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color));

   MAKE_FN(0xBDCA84, uintptr_t, Tesselator_GetInstance, ());

   MAKE_FN(0xBDCA9C, uintptr_t, Tesselator_getBuilder, (uintptr_t tesselator));

   MAKE_FN(0x9C1928, void, BufferBuilder_begin, (uintptr_t bufferBuilder));

   MAKE_FN(0x9C1A3C, void, BufferBuilder_color, (uintptr_t bufferBuilder, int r, int g, int b, float a));

   MAKE_FN(0x9C170C, void, BufferBuilder_end, (uintptr_t bufferBuilder));

   MAKE_FN(0x9C2388, void, BufferBuilder_vertexUV, (uintptr_t bufferBuilder, float f1, float f2, float f3, float f4, float f5));

   MAKE_FN(0x2E2180, void, FrostWalkerEnchantment_onEntityMoved, (void* entity, void* multiPlayerLevel, void* blockPos, int enchantmentLevel));

   MAKE_FN(0xB0E8F4, void, MultiPlayerLevel_getEntity, (void* outEntity, void* multiPlayerLevel, int id));

   MAKE_FN(0xAE03B4, int, Minecraft_getLocalPlayerIdx, (void* minecraft));

   MAKE_FN(0x85FA24, uintptr_t, CGameNetworkManager_GetPlayerByIndex, (uintptr_t gameNetworkManager, uint32_t r4));

   MAKE_FN(0x2245C0, int, Entity_getId, (void* entity));

   MAKE_FN(0x2355E4, bool, Entity_is, (void* entity1, void* entity2));

   MAKE_FN(0x886798, void, ConsoleUIController_PlayUISFX, (uintptr_t consoleUIController, uintptr_t soundEvent));

   MAKE_FN(0xC69D18, void, Renderer_Present, (void* renderer));

   MAKE_FN(0xC67ED0, void*, Renderer_getContext, (void* renderer));

   MAKE_FN(0xC69E5C, void, GlStateManager_clear, (void* renderer, uint32_t r4, uint32_t r5));

   MAKE_FN(0xC69C58, void, WaitFlip, ());

   MAKE_FN(0xCAA040, void, cellGcmFlush, (void* gcmContextData));

   MAKE_FN(0xC720B8, uintptr_t, Renderer_DrawVertices, (uintptr_t r3, uintptr_t r4, uintptr_t r5, uintptr_t r6, uintptr_t r7, uintptr_t r8, uintptr_t r9));



public:
   uintptr_t* pCInput = (uintptr_t*)0x16BD748;
   uintptr_t ConsoleUIController = 0x1558228;
   uintptr_t* pSoundEventBack = (uintptr_t*)0x14CA684;
   uintptr_t* pSoundEventCraft = (uintptr_t*)0x14CA688;
   uintptr_t* pSoundEventFocus = (uintptr_t*)0x14CA690;
   uintptr_t* pSoundEventPress = (uintptr_t*)0x14CA694;
   uintptr_t* pSoundEventScroll = (uintptr_t*)0x14CA698;
};

extern GameVariables* g_GameVariables;