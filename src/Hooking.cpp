#include "Hooking.hpp"


DetourHook* multiPlayerGameMode_useItemOnHk;
DetourHook* multiPlayerGameMode_tickHk;
DetourHook* multiPlayerLevel_setLevelHk;
DetourHook* multiPlayerGameMode_initPlayerHk;
DetourHook* minecraft_runMiddleHk;
DetourHook* multiPlayerGameMode_attackHk;
DetourHook* gameRenderer_setupGuiScreenHk;
DetourHook* gui_renderHk;
ImportExportHook* sceNpBasicSetPresenceDetails2Hk;
DetourHook* livingEntity_onChangedBlockHk;
DetourHook* livingEntity_getJumpPowerHk;
DetourHook* gameRenderer_GetFovHk;
DetourHook* player_HurtHk;
DetourHook* livingEntity_actuallyHurtHk;
DetourHook* player_actuallyHurtHk;
DetourHook* multiPlayerGameMode_destroyBlockHk;

uint32_t MultiPlayerGameMode_useItemOnHook(MultiPlayerGameMode* gameMode, MultiplayerLocalPlayer** player, MultiPlayerLevel* level,
   BlockPos* blockPos, Direction* direction, Vec3* pos, uint32_t interactionHand, bool unk1, bool* unk2)
{
   g_Level = level;
   g_Localplayer = *player;

   return multiPlayerGameMode_useItemOnHk->GetOriginal<uint32_t>(gameMode, player, level, blockPos, direction, pos, interactionHand, unk1, unk2); // returns 0x1 or 0x0
}

void MultiPlayerGameMode_tickHook(MultiPlayerGameMode* multiPlayerGameMode)
{
   g_Gamemode = multiPlayerGameMode;

   multiPlayerGameMode_tickHk->GetOriginal<void>(multiPlayerGameMode);
}

uint32_t MultiPlayerLevel_setLevelHook(Minecraft* minecraft, MultiPlayerLevel* level, uint32_t levelHash, uint32_t levelStorage, uint32_t r7, uint32_t r8)
{
   g_Minecraft = minecraft;
   g_Level = level;

   return multiPlayerLevel_setLevelHk->GetOriginal<uint32_t>(minecraft, level, levelHash, levelStorage, r7, r8);
}

uint32_t MultiPlayerGameMode_initPlayerHook(MultiPlayerGameMode* gameMode, MultiplayerLocalPlayer** player)
{
   g_Gamemode = gameMode;
   g_Localplayer = *player;

   return multiPlayerGameMode_initPlayerHk->GetOriginal<uint32_t>(gameMode, player);
}

void Minecraft_runMiddleHook(Minecraft* minecraft)
{
   g_Minecraft = minecraft;

   minecraft_runMiddleHk->GetOriginal<void>(minecraft);
}

uint32_t MultiPlayerGameMode_attackHook(MultiPlayerGameMode* gamemode, MultiplayerLocalPlayer** player, Entity* entity)
{
   //g_Gamemode = gamemode;
   g_Localplayer = *player;

   return multiPlayerGameMode_attackHk->GetOriginal<uint32_t>(gamemode, player, entity);
}

void GameRenderer_setupGuiScreenHook(uintptr_t r3, uint32_t r4)
{
   //g_GuiComponent = (GuiComponent*)*(uintptr_t*)(*(uintptr_t*)(r3 + 0x1C) + 0x140);
   gameRenderer_setupGuiScreenHk->GetOriginal<void>(r3, r4);

   // drawing must be called after the original
   //g_Menu.OnGameTick();
}

void Gui_renderHook(GuiComponent* gui, double unk)
{
   g_GuiComponent = gui;
   gui_renderHk->GetOriginal<void>(gui, unk);

   // drawing must be called after the original
   g_MenuTab.OnGameTick();
}

uint32_t LivingEntity_onChangedBlockHook(Entity* entity, BlockPos* pos)
{
   if (g_Helpers.frostWalker)
   {
      g_GameVariables->FrostWalkerEnchantment_onEntityMoved(&entity->m_this, entity->m_multiPlayerLevel2, pos, 255);
   }

   return livingEntity_onChangedBlockHk->GetOriginal<uint32_t>(entity, pos);
}

float LivingEntity_getJumpPowerHook(Entity* entity)
{
   //if (0.0f < g_Helpers.movmentJumpMotion)
   //   return g_Helpers.movmentJumpMotion;

   return livingEntity_getJumpPowerHk->GetOriginal<float>(entity);
}

float GameRenderer_GetFovHook(void* gameRenderer, float datFloat, int datBoolean)
{
   if (0.0f < g_Helpers.visualFov)
      return g_Helpers.visualFov;

   return gameRenderer_GetFovHk->GetOriginal<float>(gameRenderer, datFloat, datBoolean); // returns  70.0
}

bool Player_HurtHook(ServerPlayer* serverPlayer, DamageSource* damageSource, float damage)
{
   printf("Player_HurtHook\n");
   printf("serverPlayer 0x%X\n", serverPlayer);
   printf("self 0x%X\n", g_Localplayer);

   if (IsEntitySelf(serverPlayer) && g_Helpers.selfInvulnerability)
      return true;

   return player_HurtHk->GetOriginal<bool>(serverPlayer, damageSource, damage);
}

void LivingEntity_actuallyHurtHook(Entity* entity, EntityDamageSource* entityDamageSource, float damage)
{
   if (g_Helpers.combatOneHitKill)
      damage = 99.f;

   livingEntity_actuallyHurtHk->GetOriginal<void>(entity, entityDamageSource, damage);
}

void Player_actuallyHurtHook(ServerPlayer* player, DamageSource* damageSource, float damage)
{
   if (g_Helpers.combatOneHitKill)
      damage = 99.f;

   player_actuallyHurtHk->GetOriginal<void>(player, damageSource, damage);
}

void MultiPlayerGameMode_destroyBlockHook(MultiPlayerGameMode* gamemode, BlockPos* blockPos)
{
   if (g_Helpers.nuker)
   {
      int size = g_Helpers.nukerSize;
      for (int x = 0 - size / 2; x < size / 2; x++)
      {
         for (int y = 0 - size / 2; y < size / 2; y++)
         {
            for (int z = 0 - size / 2; z < size / 2; z++)
            {
               blockPos->x += x;
               blockPos->y += y;
               blockPos->z += z;

               multiPlayerGameMode_destroyBlockHk->GetOriginal<void>(gamemode, blockPos);
               multiPlayerGameMode_destroyBlockHk->GetOriginal<void>(gamemode, blockPos);
            }
         }
      }
   }

   multiPlayerGameMode_destroyBlockHk->GetOriginal<void>(gamemode, blockPos);
}


DetourHook* Player_normalTickHk;
DetourHook* Entity_IsInWaterHk;
DetourHook* Entity_IsInWaterOrRainHk;
DetourHook* Entity_IsUnderLiquidHk;
DetourHook* Items_WeaponItem_GetDestroySpeedHk;

float kSpeed = 90.0f;
void* playerRef = nullptr;
bool kFly = false;
float kJump = 50.0f;
bool kWater = false;
bool kScuba = false;
float kDestroy = 40.0f;

float Player_GetWalkingSpeedModifierHook(void* self)
{
   return kSpeed;
}

void Player_normalTickHook(void* self)
{
   playerRef = self;
   if (kFly)
   {
      /* The players Abilities struct is located 0xC6C bytes from the main player stack */
      //Abilities* dataPtr = (Abilities*)self;
      //Abilities* abilities = &dataPtr[0xC6C / sizeof(Abilities)];
      //abilities->mayfly = true;
   }
   Player_normalTickHk->GetOriginal<void>(self);
}

void Mob_JumpFromGroundHook(void* self)
{
   /* jump height is located 0x4C bytes up from Mob stack */
   /* see this picture to see what I mean */
   /* http://i.imgur.com/QeR9vPU.png */
   float* dataPtr = (float*)self;
   dataPtr[0x4C / sizeof(float)] = kJump;
}

bool Entity_IsInWaterHook(void* self)
{
   return (kWater) ? true : Entity_IsInWaterHk->GetOriginal<bool>(self);
}

bool Entity_IsInWaterOrRainHook(void* self)
{
   return (kWater) ? true : Entity_IsInWaterOrRainHk->GetOriginal<bool>(self);
}

bool Entity_IsUnderLiquidHook(void* self, void* material)
{
   if (kScuba)
   {
      if (IsEntitySelf(self))
      {
         return false;
      }
   }
   return Entity_IsUnderLiquidHk->GetOriginal<bool>(self, material);
}

float Items_HatchetItem_GetDestroySpeedHook(void* ItemInstance, void* tile)
{
   return kDestroy;
}
float Items_PickaxeItem_GetDestroySpeedHook(void* ItemInstance, void* tile)
{
   return kDestroy;
}
float Items_Item_GetDestroySpeedHook(void* ItemInstance, void* tile)
{
   return kDestroy;
}
float Items_DiggerItem_GetDestroySpeedHook(void* ItemInstance, void* tile)
{
   return kDestroy;
}
float Items_ShearsItem_GetDestroySpeedHook(void* ItemInstance, void* tile)
{
   return kDestroy;
}

float Items_WeaponItem_GetDestroySpeedHook(void* ItemInstance, void* tile)
{
   return kDestroy;
}

uint32_t sceNpBasicSetPresenceDetails2Hook(SceNpBasicPresenceDetails2* pres, uint32_t options)
{
   strncpy(pres->status, "Using \uF477 RouletteBoi SPRX \uF477", 30);

   return sceNpBasicSetPresenceDetails2Hk->GetOriginal<uint32_t>(pres, options);
}

void InstallHooks()
{
   multiPlayerGameMode_useItemOnHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->MultiPlayerGameMode_useItemOn),
      (uintptr_t)MultiPlayerGameMode_useItemOnHook);

   multiPlayerGameMode_tickHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->MultiPlayerGameMode_tick),
      (uintptr_t)MultiPlayerGameMode_tickHook);

   multiPlayerLevel_setLevelHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->MultiPlayerLevel_setLevel),
      (uintptr_t)MultiPlayerLevel_setLevelHook);

   // using false because this function only has 4 instructions. Preserve registers takes 6 instructions so settings it to false will default back to 4 instructions 
   multiPlayerGameMode_initPlayerHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->MultiPlayerGameMode_initPlayer),
      (uintptr_t)MultiPlayerGameMode_initPlayerHook, false);

   minecraft_runMiddleHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->Minecraft_runMiddle),
      (uintptr_t)Minecraft_runMiddleHook);

   multiPlayerGameMode_attackHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->MultiPlayerGameMode_attack),
      (uintptr_t)MultiPlayerGameMode_attackHook);

   gameRenderer_setupGuiScreenHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->GameRenderer_setupGuiScreen),
      (uintptr_t)GameRenderer_setupGuiScreenHook);

   gui_renderHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->Gui_render),
      (uintptr_t)Gui_renderHook);

   sceNpBasicSetPresenceDetails2Hk = new ImportExportHook(ImportExportHook::Import, "sceNp", 0x5E849303, (uintptr_t)sceNpBasicSetPresenceDetails2Hook);

   livingEntity_onChangedBlockHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->LivingEntity_onChangedBlock),
      (uintptr_t)LivingEntity_onChangedBlockHook);

   //livingEntity_getJumpPowerHk = new DetourHook(
   //   *(uint32_t*)(g_GameVariables->LivingEntity_getJumpPower),
   //   (uintptr_t)LivingEntity_getJumpPowerHook, false);

   gameRenderer_GetFovHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->GameRenderer_GetFov),
      (uintptr_t)GameRenderer_GetFovHook);

   player_HurtHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->Player_Hurt),
      (uintptr_t)Player_HurtHook);

   livingEntity_actuallyHurtHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->LivingEntity_actuallyHurt),
      (uintptr_t)LivingEntity_actuallyHurtHook);

   player_actuallyHurtHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->Player_actuallyHurt),
      (uintptr_t)Player_actuallyHurtHook);

   multiPlayerGameMode_destroyBlockHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->MultiPlayerGameMode_destroyBlock),
      (uintptr_t)MultiPlayerGameMode_destroyBlockHook);
}

void RemoveHooks()
{
   delete multiPlayerGameMode_useItemOnHk;
   delete multiPlayerGameMode_tickHk;
   delete multiPlayerLevel_setLevelHk;
   delete multiPlayerGameMode_initPlayerHk;
   delete minecraft_runMiddleHk;
   delete multiPlayerGameMode_attackHk;
   delete gameRenderer_setupGuiScreenHk;
   delete gui_renderHk;
   delete sceNpBasicSetPresenceDetails2Hk;
   delete livingEntity_onChangedBlockHk;
   //delete livingEntity_getJumpPowerHk;
   delete gameRenderer_GetFovHk;
   delete player_HurtHk;
   delete livingEntity_actuallyHurtHk;
   delete player_actuallyHurtHk;
   delete multiPlayerGameMode_destroyBlockHk;
}