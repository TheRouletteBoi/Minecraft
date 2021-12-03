#include "Menu.hpp"

Menu g_Menu;
Menu::TabComponent g_CombatTab;
Menu::TabComponent g_MovmentTab;
Menu::TabComponent g_PlayerTab;
Menu::TabComponent g_VisualTab;
Menu::TabComponent g_WorldTab;
Menu::TabComponent g_ItemTab;
Menu::TabComponent g_EnchantmentTab;
Menu::TabComponent g_HostTab;
Menu::TabComponent g_DebugTab;

Menu::Menu(Function mainmenu, Function firstTab, Function secondTab, Function thirdTab, Function fourthTab)
   : m_MainMenu(mainmenu), m_FirstTab(firstTab), m_SecondTab(secondTab), m_ThirdTab(thirdTab), m_FourthTab(fourthTab)
{

}

void Menu::OnGameTick()
{
   if (!IsInitialized())
      Initialize();

   Tick();
}

bool Menu::IsInitialized()
{
   return m_Initialized;
}

void Menu::Initialize()
{
   if (m_OnMain != nullptr)
      m_OnMain();

   m_Initialized = true;
}

void Menu::RegisterOnMain(Function onMain)
{
   m_OnMain = onMain;
}

void Menu::RegisterOnFirstTimeOpen(Function onFirstTime)
{
   m_OnFirstTimeOpen = onFirstTime;
}

bool Menu::IsEnterPressed()
{
   if (ButtonPressed(BUTTON_CROSS))
   {
      PlayUISoundSelect();
      return true;
   }

   return false;
}

bool Menu::IsLeftPressed()
{
   if (ButtonPressed(BUTTON_PAD_LEFT))
   {
      PlayUISoundScroll();
      return true;
   }

   return false;
}

bool Menu::IsRightPressed()
{
   if (ButtonPressed(BUTTON_PAD_RIGHT))
   {
      PlayUISoundScroll();
      return true;
   }

   return false;
}

bool Menu::IsLeftOrRightPressed()
{
   if (ButtonPressed(BUTTON_PAD_LEFT) || ButtonPressed(BUTTON_PAD_RIGHT))
   {
      PlayUISoundScroll();
      return true;
   }

   return false;
}

bool Menu::IsSquarePressed()
{
   if (ButtonPressed(BUTTON_SQUARE))
   {
      PlayUISoundSelect();
      return true;
   }

   return false;
}

bool Menu::IsOpenPressed()
{
   return IsButtonBinds(BUTTON_L1, BUTTON_PAD_UP);
}

void Menu::UpdateDrawing()
{
   m_MainMenuTotalTabs = m_MainMenuPrintingTab;
   m_MainMenuPrintingTab = 0;
   m_MainMenuBaseY = m_MainMenuPosY;
   m_MainMenu();


   UpdateEditTabPlacement();
   for (const auto& tab : m_TabList)
   {
      if (tab.isRunning)
      {
         GetTabComponent(tab.tabFn).TotalOptions = GetTabComponent(tab.tabFn).PrintingOption;
         GetTabComponent(tab.tabFn).PrintingOption = 0;
         GetTabComponent(tab.tabFn).TabBaseY = GetTabComponent(tab.tabFn).TabPosY;

         tab.tabFn();
      }
   }
}

void Menu::UpdateEditTabPlacement()
{
   if (m_CanEditTabPlacement)
   {
      // 360 max for right
      // 0 max for left
      // 
      // -5 max for up
      // 220 max for down

      // check if we are out of bounds 
      /*if (m_TabPosX > 350 || m_TabPosX < 0)
         return;

      if (m_TabPosY > 220 || m_TabPosY < 0)
         return;*/

      double stickX = GetLeftJoyStickX();
      double stickY = -GetLeftJoyStickY();

      if (stickX != 0.0)
      {
         int32_t xAdvance = GetTabComponent(m_ActiveTab).TabPosX + stickX * 5.0;
         if (xAdvance < 350 || xAdvance < 0)
         {
            GetTabComponent(m_ActiveTab).TabPosX += stickX * 5.0;
         }
      }

      if (stickY != 0.0)
      {
         int32_t yAdvance = GetTabComponent(m_ActiveTab).TabPosY + stickY * 5.0;
         if (yAdvance < 220 || yAdvance < 0)
         {
            GetTabComponent(m_ActiveTab).TabPosY += stickY * 5.0;
         }
      }

   }
}

void Menu::UpdateButtons()
{
   if (ButtonPressed(BUTTON_CIRCLE))
   {
      OnClose();
   }
   if (ButtonPressed(BUTTON_PAD_UP))
   {
      OnScrollUp();
   }
   if (ButtonPressed(BUTTON_PAD_DOWN))
   {
      OnScrollDown();
   }
   if (ButtonPressed(BUTTON_L1))
   {
      OnTabLeft();
   }
   if (ButtonPressed(BUTTON_R1))
   {
      OnTabRight();
   }

   if (IsOpenPressed())
      OnClose();
}

void Menu::WhileOpen()
{
   UpdateDrawing();
   UpdateButtons();
}

void Menu::WhileClosed()
{
   //if (IsOpenPressed())
      OnOpen();
}


void Menu::AddTabToListIfNotInListNew(Function fn, int32_t xPos, int32_t yPos)
{
   // search for tab function
   auto searchTab = std::find_if(m_TabList.begin(), m_TabList.end(), [&fn](const TabComponent& tab)
      {
         return tab.tabFn == fn;
      });

   // if not found then add it to the map
   if (searchTab == m_TabList.end())
      m_TabList.push_back(TabComponent(fn, true, xPos, yPos));
}

void Menu::OnOpen()
{
   if (m_FirstTimeOpen)
   {
      if (m_OnFirstTimeOpen)
         m_OnFirstTimeOpen();

      AddTabToListIfNotInListNew(m_FirstTab, 90, 3);
      AddTabToListIfNotInListNew(m_SecondTab, 161, 3);
      AddTabToListIfNotInListNew(m_ThirdTab, 234, 3);
      AddTabToListIfNotInListNew(m_FourthTab, 329, 3);

      m_FirstTimeOpen = false;
   }

   m_Opened = true;

   // Tabs
   m_MainMenuCurrentTab = (m_MainMenuSavedCurrentTab == 0) ? 1 : m_MainMenuSavedCurrentTab;

   m_ActiveTab = m_MainMenu;

   // Tab Options
   GetTabComponent(m_ActiveTab).CurrentOption = (GetTabComponent(m_ActiveTab).SavedCurrentOption == 0) ? 1 : GetTabComponent(m_ActiveTab).SavedCurrentOption;

   PlayUISoundSelect();
}

void Menu::OnClose()
{
   m_Opened = false;

   // Tabs
   m_MainMenuSavedCurrentTab = m_MainMenuCurrentTab;

   // Tab Options
   GetTabComponent(m_ActiveTab).SavedCurrentOption = GetTabComponent(m_ActiveTab).CurrentOption;

   PlayUISoundBack();
}

void Menu::OnScrollUp()
{
   // Tabs
   m_MainMenuCurrentTab--;
   if (m_MainMenuCurrentTab < 1)
      m_MainMenuCurrentTab = m_MainMenuTotalTabs;

   // Tab Options
   GetTabComponent(m_ActiveTab).CurrentOption--;
   if (GetTabComponent(m_ActiveTab).CurrentOption < 1)
      GetTabComponent(m_ActiveTab).CurrentOption = GetTabComponent(m_ActiveTab).TotalOptions;

   PlayUISoundScroll();
}

void Menu::OnScrollDown()
{
   // Tabs
   m_MainMenuCurrentTab++;
   if (m_MainMenuCurrentTab > m_MainMenuTotalTabs)
      m_MainMenuCurrentTab = 1;

   // Tab Options
   GetTabComponent(m_ActiveTab).CurrentOption++;
   if (GetTabComponent(m_ActiveTab).CurrentOption > GetTabComponent(m_ActiveTab).TotalOptions)
      GetTabComponent(m_ActiveTab).CurrentOption = 1;

   PlayUISoundScroll();
}

void Menu::OnTabLeft()
{

   PlayUISoundSelect();
}

void Menu::OnTabRight()
{

   PlayUISoundSelect();
}

bool Menu::tabPressed()
{
   if (tabHovered())
   {
      return IsEnterPressed();
   }
   return false;
}

void Menu::AddTabToListIfNotInList(const TabComponent& comp)
{
   // search for tab function
   auto searchTab = std::find_if(m_TabList.begin(), m_TabList.end(), [comp](const TabComponent& tab)
   {
      return tab.tabFn == comp.tabFn;
   });

   // if not found then add it to the map
   if (searchTab == m_TabList.end())
      m_TabList.push_back(comp);
}

bool Menu::tabHovered()
{
   return m_MainMenuCurrentTab == m_MainMenuPrintingTab;
}

void Menu::title(const std::wstring& text)
{
   DrawShadowText(text, m_MainMenuPosX, m_MainMenuBaseY + (m_MainMenuTitleHeight / 2), m_MainMenuTitleTextColor, false);
   m_MainMenuBaseY += m_MainMenuTitleHeight;
}

Menu& Menu::tabmenu(const std::wstring& text)
{
   m_MainMenuPrintingTab++;
   DrawTabOptions(text);
   return *this;
}

Menu& Menu::toggleTab(const TabComponent& comp)
{
   DrawTabToggle(comp.isRunning);

   if (tabPressed())
   {
      //AddTabToListIfNotInList(comp);

      // search for tab function and if found activate the tab
      auto currentTab = std::find_if(m_TabList.begin(), m_TabList.end(), [comp](const TabComponent& tab)
      {
         return tab.tabFn == comp.tabFn;
      });

      if (currentTab != m_TabList.end())
         (*currentTab).isRunning ^= 1;
   }

   if (tabHovered() && comp.isRunning && ButtonPressed(BUTTON_L3))
      m_CanEditTabPlacement ^= 1;

   return *this;
}

Menu::TabComponent& Menu::GetTabComponent(Function fn)
{
   // search for tab function
   auto tab = std::find_if(m_TabList.begin(), m_TabList.end(), [&fn](const TabComponent& tabComp)
   {
      return tabComp.tabFn == fn;
   });

   if (tab != m_TabList.end())
      return *tab;

   static TabComponent tabComponent(nullptr, false);
   return tabComponent;
}

void Menu::DrawTabOptions(const std::wstring& text)
{
   size_t haultIndex = 0;
   if ((m_MainMenuCurrentTab < m_MainMenuTabStartInfiniteScroll && m_MainMenuPrintingTab <= m_MainMenuTabOptionsPerPage) || m_MainMenuTotalTabs <= m_MainMenuTabOptionsPerPage)
   {
      haultIndex = m_MainMenuPrintingTab;
   }
   else
   {
      if (m_MainMenuCurrentTab >= m_MainMenuTabStartInfiniteScroll)
      {
         if (m_MainMenuCurrentTab > (m_MainMenuTotalTabs - m_MainMenuTabEndInfiniteScroll))
         {
            haultIndex = m_MainMenuTabStartInfiniteScroll + (m_MainMenuTabEndInfiniteScroll - (m_MainMenuTotalTabs - m_MainMenuPrintingTab));
         }
         else
         {
            haultIndex = m_MainMenuTabStartInfiniteScroll + (m_MainMenuPrintingTab - m_MainMenuCurrentTab);
         }
      }
   }
   if (haultIndex > m_MainMenuTabOptionsPerPage || haultIndex <= 0)
      return;

   DrawRect(
      m_MainMenuPosX,
      m_MainMenuBaseY + (m_MainMenuOptionHeight / 2),
      70,
      170,
      m_MainMenuTabBackgroundColor);

   DrawText(text,
      m_MainMenuPosX,
      m_MainMenuBaseY + (m_MainMenuOptionHeight / 2),
      tabHovered() ? m_MainMenuTabTextColorHighlighted : m_MainMenuTabTextColor);

   m_MainMenuBaseY += m_MainMenuOptionHeight;
}

void Menu::DrawTabToggle(bool var)
{
   //float yPosAtOption = m_MainMenuBaseY - m_MainMenuOptionHeight;
}

void Menu::Tick()
{
   UpdateUI();
}

void Menu::UpdateUI()
{
   if (m_Opened)
   {
      WhileOpen();
   }
   else
   {
      WhileClosed();
   }
}