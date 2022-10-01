
#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <sys/timer.h>
#include <cell/pad.h>
#include "Util/NewDeleteOverride.hpp"
#include "Util/TimeHelpers.hpp"
#include "Util/SystemCalls.hpp"
#include "Game.hpp"
#include "Hooking.hpp"

SYS_MODULE_INFO(Minecraft, 0, 1, 1);
SYS_MODULE_START(Minecraft_Main);
SYS_MODULE_STOP(Minecraft_Stop);

sys_ppu_thread_t gMinecraftPpuThread = SYS_PPU_THREAD_ID_INVALID;
sys_ppu_thread_t gFailSafePpuThread = SYS_PPU_THREAD_ID_INVALID;
bool gFalilSafeRunning = true;


/***
* 
* https://www.youtube.com/watch?v=68SP6vfPw7I MCPE Master
* https://research.ncl.ac.uk/game/mastersdegree/workshops/ps3introductiontogcm/tutorial6.pdf GCMRenderer::SwapBuffers
* https://docplayer.net/54726301-Tutorial-4-introduction-to-gcm-and-ps3-graphics.html Finished Drawing Swap buffers
* 
* 
* TODO MENU
* have 4 tabs opened by default
* if hovering over a tab and R3 is pressed you can move/dock the menu anywhere on screen using R3 or L3
* Move adding submenus to "onFirst time open" that way we can set position and color for the main and other 3 submenus and when a new submenus is chosen just set position to center of screen or under 3 submenus
* Move MainMenu into tab components
* 
* 
* ADDONS
* check for proper cursor handling @ C:\usr\local\cell\samples\sdk\graphics\gcm\cursor
* 
* 
* BUGS
* DEBUG MODE. In debug mode assert receives a linker error in "imgui.h" macro IM_ASSERT. **Unable to compile in debug mode**
* when ImGui folder is included into project the sprx doesn't load into the game but it does show up in target manager
* 
* 
* 
* 
* 
* 
* 
* 
*/ 

CDECL_BEGIN
int Minecraft_Main(int argc, char* argv[])
{
   sys_ppu_thread_create(&gMinecraftPpuThread, [](uint64_t arg)
   {
#if NDEBUG
      sleep_for(10000);
#endif

      g_GameVariables = new GameVariables();
      g_Helpers = Helpers();

      InstallHooks();

      sys_ppu_thread_exit(0);

   }, 0, 3000, 0x8000, SYS_PPU_THREAD_CREATE_JOINABLE, "Minecraft");


   sys_ppu_thread_create(&gFailSafePpuThread, [](uint64_t arg)
   {
      while (gFalilSafeRunning)
      {
         auto UpdateExitProcessOnException = []() -> void
         {
            CellPadData padData{};
            if (cellPadGetData(0, &padData) != CELL_PAD_OK)
               return;

            if (padData.len == 0)
               return;

            if ((padData.button[CELL_PAD_BTN_OFFSET_DIGITAL1] & CELL_PAD_CTRL_SELECT)
               && (padData.button[CELL_PAD_BTN_OFFSET_DIGITAL1] & CELL_PAD_CTRL_START))
               do_umount();
         };

         UpdateExitProcessOnException();

         sleep_for(1000);
      }

      sys_ppu_thread_exit(0);

   }, 0, 0x50, 2048, SYS_PPU_THREAD_CREATE_JOINABLE, "FailSafeThread");

   return 0;
}

int Minecraft_Stop(int argc, char* argv[])
{
   gFalilSafeRunning = false;

   uint64_t retVal;
   sys_ppu_thread_join(gMinecraftPpuThread, &retVal);

   uint64_t retVal2;
   sys_ppu_thread_join(gFailSafePpuThread, &retVal2);

   RemoveHooks();
   delete g_GameVariables;

   return 0;
}
CDECL_END