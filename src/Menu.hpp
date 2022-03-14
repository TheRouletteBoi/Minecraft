#pragma once
#include <string>
#undef vector
#include <vector>
#include <cmath>
#include "Enums.hpp"
#include "Helpers.hpp"

using Function = void(*)();
using KeyboardHandler = int(*)(uint64_t param, uint64_t status, uint64_t a3);

enum class OptionAction
{
   EnterPress,
   LeftPress,
   RightPress,
   LeftOrRightPress,
   SquarePress
};

class MenuBase
{
public:
   MenuBase() = default;
   virtual ~MenuBase() { }

   virtual void OnGameTick();
   virtual void UpdateGUI() = 0;
   virtual void OnOpen();
   virtual void OnClose();
   virtual void OnScrollUp();
   virtual void OnScrollDown();
   virtual void OnTabPrevious();
   virtual void OnTabNext();

   void RegisterOnMain(Function onMain);
   void RegisterOnFirstTimeOpen(Function onFirstTime);
   bool IsInitialized();
   void Initialize();
   bool IsOpenPressed();
   bool IsEnterPressed();
   bool IsLeftPressed();
   bool IsRightPressed();
   bool IsLeftOrRightPressed();
   bool IsSquarePressed();
   void WhileOpen();
   void WhileClosed();
   void UpdateButtons();
   void Tick();

protected:
   bool m_Initialized{};
   bool m_Opened{};
   bool m_FirstTimeOpen = true;
   Function m_OnFirstTimeOpen{};
   Function m_OnMain{};
};

class MenuTab : public MenuBase
{
public:
   MenuTab() = default;
   MenuTab(Function mainmenu, Function firstTab, Function secondTab, Function thirdTab, Function fourthTab);
   ~MenuTab();

   virtual void OnGameTick() override;
   virtual void UpdateGUI() override;
   virtual void OnOpen() override;
   virtual void OnClose() override;
   virtual void OnScrollUp() override;
   virtual void OnScrollDown() override;
   virtual void OnTabPrevious() override;
   virtual void OnTabNext() override;

   bool hovered();
   bool pressed();
   void title(const std::wstring& text);
   MenuTab& option(const std::wstring& text);
   MenuTab& toggle(bool var);
   void DrawTabOptions(const std::wstring& text);

private:
   Function m_MainMenu{};
   Function m_FirstTab{};
   Function m_SecondTab{};
   Function m_ThirdTab{};
   Function m_FourthTab{};

   uint32_t m_PosX = 10;
   uint32_t m_PosY = 50;
   uint32_t m_Width = 5;
   uint32_t m_BaseY = 0;

   // Scrolling
   size_t m_PrintingOption = 0;
   size_t m_CurrentOption = 0;
   size_t m_TotalOption = 0;
   size_t m_StartInfiniteScroll = 8;
   size_t m_EndInfiniteScroll = 6;
   size_t m_OptionsPerPage = 14;

   // Title
   uint32_t m_TitleHeight = 16;
   Color m_TitleTextColor{ 255, 165, 0, 255 };

   // Options
   uint32_t m_OptionHeight = 10;
   Color m_OptionTextColor{ 255, 255, 255, 255 };
   Color m_OptionTextColorHighlighted{ 255, 0, 0, 255 };
   Color m_OptionBackgroundColor{ 128, 128, 128, 100 };
};

/*class MenuComponent : public MenuBase
{
public:
   MenuComponent() = default;
   MenuComponent(Function tab);
   ~MenuComponent();

   virtual void OnGameTick() override;
   virtual void UpdateGUI() override;
};*/

extern MenuTab g_MenuTab;