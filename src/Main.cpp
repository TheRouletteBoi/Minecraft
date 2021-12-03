
#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <sys/timer.h>
#include <cell/pad.h>
#include "Util/NewDeleteOverride.hpp"
#include "Util/TimeHelpers.hpp"
#include "Game.hpp"
#include "Hooking.hpp"
#include "Menu.hpp"
#include "Submenus.hpp"

SYS_MODULE_INFO(Minecraft, 0, 1, 1);
SYS_MODULE_START(Minecraft_Main);
SYS_MODULE_STOP(Minecraft_Stop);

sys_ppu_thread_t gMinecraftThreadId = SYS_PPU_THREAD_ID_INVALID;


/***
* 
* https://www.youtube.com/watch?v=68SP6vfPw7I MCPE Master
* Menu
* have 4 tabs opened by default
* if hovering over a tab and R3 is pressed you can move/dock the menu anywhere on screen using R3 or L3
* 
* 
*/ 


CDECL_BEGIN
int Minecraft_Main(int argc, char* argv[])
{
   sys_ppu_thread_create(&gMinecraftThreadId, [](uint64_t arg)
   {
#if NDEBUG
      sleep_for(10000);
#endif

      g_GameVariables = new GameVariables();
      g_Helpers = Helpers();
      g_Menu = Menu(MainMenu, CombatTab, MovementTab, PlayerTab, ItemTab);

      HookingInitiate();

      g_Menu.RegisterOnMain([]
      {
         

         printf("welcome to minecraft sprx mod menu\n");
      });


      // everything under here is bad and must be changed. it adds a submenu here and in Menu::OnOpen() so there are 2 instances of the submenu. BADDDd
      g_CombatTab = Menu::TabComponent(CombatTab, false);
      g_MovmentTab = Menu::TabComponent(MovementTab, false);
      g_PlayerTab = Menu::TabComponent(PlayerTab, false);
      g_VisualTab = Menu::TabComponent(VisualTab, false);
      g_WorldTab = Menu::TabComponent(WorldTab, false);
      g_ItemTab = Menu::TabComponent(ItemTab, false);
      g_EnchantmentTab = Menu::TabComponent(EnchantmentTab, false);
      g_HostTab = Menu::TabComponent(HostTab, false);
      g_DebugTab = Menu::TabComponent(DebugTab, false);


      g_Menu.AddTabToListIfNotInList(Menu::TabComponent(CombatTab, false));
      g_Menu.AddTabToListIfNotInList(Menu::TabComponent(MovementTab, false));
      g_Menu.AddTabToListIfNotInList(Menu::TabComponent(PlayerTab, false));
      g_Menu.AddTabToListIfNotInList(Menu::TabComponent(VisualTab, false));
      g_Menu.AddTabToListIfNotInList(Menu::TabComponent(WorldTab, false));
      g_Menu.AddTabToListIfNotInList(Menu::TabComponent(ItemTab, false));
      g_Menu.AddTabToListIfNotInList(Menu::TabComponent(EnchantmentTab, false));
      g_Menu.AddTabToListIfNotInList(Menu::TabComponent(HostTab, false));
      g_Menu.AddTabToListIfNotInList(Menu::TabComponent(DebugTab, false));

      sys_ppu_thread_exit(0);

   }, 0, 3000, 8192, SYS_PPU_THREAD_CREATE_JOINABLE, "Minecraft");

   return 0;
}

int Minecraft_Stop(int argc, char* argv[])
{
   uint64_t retVal;
   sys_ppu_thread_join(gMinecraftThreadId, &retVal);
   HookingRemoveAll();
   delete g_GameVariables;

   return 0;
}
CDECL_END