#include "Menu.hpp"

MenuTab g_MenuTab;

void MenuBase::OnGameTick()
{
   if (!IsInitialized())
      Initialize();

   Tick();
}

bool MenuBase::IsInitialized()
{
   return m_Initialized;
}

void MenuBase::Initialize()
{
   if (m_OnMain)
      m_OnMain();

   m_Initialized = true;
}

void MenuBase::RegisterOnMain(Function onMain)
{
   m_OnMain = onMain;
}

void MenuBase::RegisterOnFirstTimeOpen(Function onFirstTime)
{
   m_OnFirstTimeOpen = onFirstTime;
}

bool MenuBase::IsOpenPressed()
{
   return IsButtonBinds(BUTTON_L1, BUTTON_PAD_UP);
}

bool MenuBase::IsEnterPressed()
{
   if (ButtonPressed(BUTTON_CROSS))
   {
      PlayUISoundSelect();
      return true;
   }

   return false;
}

bool MenuBase::IsLeftPressed()
{
   if (ButtonPressed(BUTTON_PAD_LEFT))
   {
      PlayUISoundScroll();
      return true;
   }

   return false;
}

bool MenuBase::IsRightPressed()
{
   if (ButtonPressed(BUTTON_PAD_RIGHT))
   {
      PlayUISoundScroll();
      return true;
   }

   return false;
}

bool MenuBase::IsLeftOrRightPressed()
{
   if (ButtonPressed(BUTTON_PAD_LEFT) || ButtonPressed(BUTTON_PAD_RIGHT))
   {
      PlayUISoundScroll();
      return true;
   }

   return false;
}

bool MenuBase::IsSquarePressed()
{
   if (ButtonPressed(BUTTON_SQUARE))
   {
      PlayUISoundSelect();
      return true;
   }

   return false;
}

void MenuBase::OnOpen()
{
   if (m_FirstTimeOpen)
   {
      if (m_OnFirstTimeOpen)
         m_OnFirstTimeOpen();

      m_FirstTimeOpen = false;
   }

   m_Opened = true;

   PlayUISoundSelect();
}

void MenuBase::OnClose()
{
   m_Opened = false;

   PlayUISoundBack();
}

void MenuBase::OnScrollUp()
{
   PlayUISoundScroll();
}

void MenuBase::OnScrollDown()
{

   PlayUISoundScroll();
}

void MenuBase::OnTabPrevious()
{

   PlayUISoundSelect();
}

void MenuBase::OnTabNext()
{

   PlayUISoundSelect();
}

void MenuBase::UpdateButtons()
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
      OnTabPrevious();
   }
   if (ButtonPressed(BUTTON_R1))
   {
      OnTabNext();
   }

   if (IsOpenPressed())
      OnClose();
}

void MenuBase::WhileOpen()
{
   UpdateButtons();
}

void MenuBase::WhileClosed()
{
   if (IsOpenPressed())
      MenuBase::OnOpen();
}

void MenuBase::Tick()
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






MenuTab::MenuTab(Function mainmenu, Function firstTab, Function secondTab, Function thirdTab, Function fourthTab) 
   : MenuBase(), m_MainMenu(mainmenu), m_FirstTab(firstTab), m_SecondTab(secondTab), m_ThirdTab(thirdTab), m_FourthTab(fourthTab)
{

}

MenuTab::~MenuTab()
{

}

void MenuTab::OnGameTick()
{
   MenuBase::OnGameTick();
}

void MenuTab::UpdateGUI()
{
   m_TotalOption = m_PrintingOption;
   m_PrintingOption = 0;
   m_BaseY = m_PosY;
   m_MainMenu();
}

void MenuTab::OnOpen()
{
   MenuBase::OnOpen();

   m_CurrentOption = 1;
}

void MenuTab::OnClose()
{

}

void MenuTab::OnScrollUp()
{
   m_CurrentOption--;
   if (m_CurrentOption < 1)
      m_CurrentOption = m_TotalOption;
}

void MenuTab::OnScrollDown()
{
   m_CurrentOption++;
   if (m_CurrentOption > m_TotalOption)
      m_CurrentOption = 1;
}

void MenuTab::OnTabPrevious()
{

}

void MenuTab::OnTabNext()
{

}

bool MenuTab::hovered()
{
   return m_CurrentOption == m_PrintingOption;
}

bool MenuTab::pressed()
{
   if (hovered())
   {
      return IsEnterPressed();
   }
   return false;
}

void MenuTab::title(const std::wstring& text)
{
   DrawShadowText(text, m_PosX, m_BaseY + (m_TitleHeight / 2), m_TitleTextColor, false);
   m_BaseY += m_OptionHeight;
}

MenuTab& MenuTab::option(const std::wstring& text)
{
   m_PrintingOption++;
   DrawTabOptions(text);
   return *this;
}

MenuTab& MenuTab::toggle(bool var)
{
   return *this;
}

void MenuTab::DrawTabOptions(const std::wstring& text)
{
   size_t haultIndex = 0;
   if ((m_CurrentOption < m_StartInfiniteScroll && m_PrintingOption <= m_OptionsPerPage) || m_TotalOption <= m_OptionsPerPage)
   {
      haultIndex = m_PrintingOption;
   }
   else
   {
      if (m_CurrentOption >= m_StartInfiniteScroll)
      {
         if (m_CurrentOption > (m_TotalOption - m_EndInfiniteScroll))
         {
            haultIndex = m_StartInfiniteScroll + (m_EndInfiniteScroll - (m_TotalOption - m_PrintingOption));
         }
         else
         {
            haultIndex = m_StartInfiniteScroll + (m_PrintingOption - m_CurrentOption);
         }
      }
   }
   if (haultIndex > m_OptionsPerPage || haultIndex <= 0)
      return;

   DrawRect(
      m_PosX,
      m_BaseY + (m_OptionHeight / 2),
      70,
      170,
      m_OptionBackgroundColor);

   DrawText(text,
      m_PosX,
      m_BaseY + (m_OptionHeight / 2),
      hovered() ? m_OptionTextColorHighlighted : m_OptionTextColor);

   m_BaseY += m_OptionHeight;
}

// Required due to pure virtualness
extern "C" void __cxa_pure_virtual()
{
   while (true) {}
}