#include "Submenus.hpp"

void MainMenu()
{
   g_Menu.title(L"Roulette Menu");
   g_Menu.tabmenu(L"Combat").toggleTab(CombatTab);
   g_Menu.tabmenu(L"Movement").toggleTab(MovementTab);
   g_Menu.tabmenu(L"Player").toggleTab(PlayerTab);
   g_Menu.tabmenu(L"Visual").toggleTab(VisualTab);
   g_Menu.tabmenu(L"World").toggleTab(WorldTab);
   g_Menu.tabmenu(L"Item").toggleTab(ItemTab);
   g_Menu.tabmenu(L"Enchant").toggleTab(EnchantmentTab);
   g_Menu.tabmenu(L"Misc");
   g_Menu.tabmenu(L"Host").toggleTab(HostTab);
   g_Menu.tabmenu(L"Debug").toggleTab(DebugTab);
}

void MovementTab()
{
   g_Menu.banner(L"Movement Options");
   g_Menu.option(L"Glide");
   g_Menu.option(L"High Jump");
   g_Menu.option(L"BHOP");
   g_Menu.option(L"Frost Walker").toggle(g_Helpers.frostWalker);
}

void WorldTab()
{
   g_Menu.banner(L"World Options");
   g_Menu.option(L"Gamemode < Survival >");
   g_Menu.option(L"Time: < Morning Noon, Sunset, Night >");
   g_Menu.option(L"Rain: < Off, Weak, Strong >");
   g_Menu.option(L"Lightning: < Off, Weak, Strong >");
   g_Menu.option(L"Explosion Protection: < Off, On >");
   g_Menu.option(L"Minimap: < Off, On >");
   g_Menu.option(L"Show HP: < Off, On >");
   g_Menu.option(L"Nuker");
}

void ItemTab()
{
   g_Menu.banner(L"Item Options");
   g_Menu.option(L"Diamond Sword < 64 >");
}

void EnchantmentTab()
{
   g_Menu.banner(L"Enchantment Options");
   g_Menu.option(L"Diamond Sword -> Infinite Lv.");
}

void PlayerTab()
{
   g_Menu.banner(L"Player Options");
   g_Menu.option(L"Level < 100 >");
   g_Menu.option(L"Auto Attack");
   g_Menu.option(L"Auto Advance");
   g_Menu.option(L"Fly");
   g_Menu.option(L"Invincible");
   g_Menu.option(L"Sprint");
   g_Menu.option(L"No Clip");
   g_Menu.option(L"Show Coords");
   g_Menu.option(L"No Fall");
   g_Menu.option(L"Insta Break");
}

void CombatTab()
{
   g_Menu.banner(L"Combat Options");
   g_Menu.option(L"Aimbot");
   g_Menu.option(L"Anti KnockBack");
   g_Menu.option(L"Fast Bow");
}

void VisualTab()
{
   g_Menu.banner(L"Visual Options");
   g_Menu.option(L"ESP");
   g_Menu.option(L"Freecam");
   g_Menu.option(L"Xray");
   g_Menu.option(L"FOV < 100 >");
}

void HostTab()
{
   g_Menu.banner(L"Host Options");
   g_Menu.option(L"Invulnerability").toggle(g_Helpers.selfInvulnerability);
   g_Menu.option(L"OneHitKill").toggle(g_Helpers.combatOneHitKill);
   g_Menu.option(L"Nuker").toggle(g_Helpers.nuker);
   g_Menu.option(L"Option by vin");
}

void DebugTab()
{
   g_Menu.banner(L"Debug Options");
   g_Menu.option(L"Show LocalPlayer Id").action(OptionAction::EnterPress, [] {

      DebugLocalPlayer();
   });

   g_Menu.option(L"Test Keyboard").keyboard(L"THE QUCIK", L"BROWN FOX", 120, 
   [](uint64_t param, uint64_t status, uint64_t a3) -> int
   {
      std::string text = GetKeyboardResult();

      printf("you typed '%s' using the keyboard\n", text.c_str());

      return 0;
   });
}