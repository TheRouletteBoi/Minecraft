#include "Submenus.hpp"

void MainMenu()
{
   g_Menu.title(L"Roulette Menu");
   g_Menu.tabmenu(L"Combat").toggleTab(g_CombatTab);
   g_Menu.tabmenu(L"Movement").toggleTab(g_MovmentTab);
   g_Menu.tabmenu(L"Player").toggleTab(g_PlayerTab);
   g_Menu.tabmenu(L"Visual").toggleTab(g_VisualTab);
   g_Menu.tabmenu(L"World").toggleTab(g_WorldTab);
   g_Menu.tabmenu(L"Item").toggleTab(g_ItemTab);
   g_Menu.tabmenu(L"Enchant").toggleTab(g_EnchantmentTab);
   g_Menu.tabmenu(L"Misc");
   g_Menu.tabmenu(L"Host").toggleTab(g_HostTab);
   g_Menu.tabmenu(L"Debug").toggleTab(g_DebugTab);
}

void MovementTab()
{
   g_Menu.GetTabComponent(MovementTab).banner(L"Movement Options");
   g_Menu.GetTabComponent(MovementTab).option(L"Glide");
   g_Menu.GetTabComponent(MovementTab).option(L"High Jump");
   g_Menu.GetTabComponent(MovementTab).option(L"BHOP");
   g_Menu.GetTabComponent(MovementTab).option(L"Frost Walker");// .toggle(g_Helpers.frostWalker);
}

void WorldTab()
{
   g_Menu.GetTabComponent(WorldTab).banner(L"World Options");
   g_Menu.GetTabComponent(WorldTab).option(L"Gamemode < Survival >");
   g_Menu.GetTabComponent(WorldTab).option(L"Time: < Morning Noon, Sunset, Night >");
   g_Menu.GetTabComponent(WorldTab).option(L"Rain: < Off, Weak, Strong >");
   g_Menu.GetTabComponent(WorldTab).option(L"Lightning: < Off, Weak, Strong >");
   g_Menu.GetTabComponent(WorldTab).option(L"Explosion Protection: < Off, On >");
   g_Menu.GetTabComponent(WorldTab).option(L"Minimap: < Off, On >");
   g_Menu.GetTabComponent(WorldTab).option(L"Show HP: < Off, On >");
   g_Menu.GetTabComponent(WorldTab).option(L"Nuker");
}

void ItemTab()
{
   g_Menu.GetTabComponent(ItemTab).banner(L"Item Options");
   g_Menu.GetTabComponent(ItemTab).option(L"Diamond Sword < 64 >");
}

void EnchantmentTab()
{
   g_Menu.GetTabComponent(EnchantmentTab).banner(L"Enchantment Options");
   g_Menu.GetTabComponent(EnchantmentTab).option(L"Diamond Sword -> Infinite Lv.");
}

void PlayerTab()
{
   g_Menu.GetTabComponent(PlayerTab).banner(L"Player Options");
   g_Menu.GetTabComponent(PlayerTab).option(L"Level < 100 >");
   g_Menu.GetTabComponent(PlayerTab).option(L"Auto Attack");
   g_Menu.GetTabComponent(PlayerTab).option(L"Auto Advance");
   g_Menu.GetTabComponent(PlayerTab).option(L"Fly");
   g_Menu.GetTabComponent(PlayerTab).option(L"Invincible");
   g_Menu.GetTabComponent(PlayerTab).option(L"Sprint");
   g_Menu.GetTabComponent(PlayerTab).option(L"No Clip");
   g_Menu.GetTabComponent(PlayerTab).option(L"Show Coords");
   g_Menu.GetTabComponent(PlayerTab).option(L"No Fall");
   g_Menu.GetTabComponent(PlayerTab).option(L"Insta Break");
}

void CombatTab()
{
   g_Menu.GetTabComponent(CombatTab).banner(L"Combat Options");
   g_Menu.GetTabComponent(CombatTab).option(L"Aimbot");
   g_Menu.GetTabComponent(CombatTab).option(L"Anti KnockBack");
   g_Menu.GetTabComponent(CombatTab).option(L"Fast Bow");
}

void VisualTab()
{
   g_Menu.GetTabComponent(VisualTab).banner(L"Visual Options");
   g_Menu.GetTabComponent(VisualTab).option(L"ESP");
   g_Menu.GetTabComponent(VisualTab).option(L"Freecam");
   g_Menu.GetTabComponent(VisualTab).option(L"Xray");
   g_Menu.GetTabComponent(VisualTab).option(L"FOV < 100 >");
}

void HostTab()
{
   g_Menu.GetTabComponent(HostTab).banner(L"Host Options");
   g_Menu.GetTabComponent(HostTab).option(L"Invulnerability");// .toggle(g_Helpers.selfInvulnerability);
   g_Menu.GetTabComponent(HostTab).option(L"OneHitKill");// .toggle(g_Helpers.combatOneHitKill);
   g_Menu.GetTabComponent(HostTab).option(L"Nuker");// .toggle(g_Helpers.nuker);
   g_Menu.GetTabComponent(HostTab).option(L"Option by vin");
}

void DebugTab()
{
   g_Menu.GetTabComponent(DebugTab).banner(L"Debug Options");
   g_Menu.GetTabComponent(DebugTab).option(L"Show LocalPlayer Id");/*.action(OptionAction::EnterPress, [] {

      DebugLocalPlayer();
   });

   g_DebugTab.option(L"Test Keyboard").keyboard(L"THE QUCIK", L"BROWN FOX", 120,
   [](uint64_t param, uint64_t status, uint64_t a3) -> int
   {
      std::string text = GetKeyboardResult();

      printf("you typed '%s' using the keyboard\n", text.c_str());

      return 0;
   });*/
}