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

class Menu
{
public:
   struct TabComponent
   {
      TabComponent(Function tabFn, bool isRunning) : tabFn(tabFn), isRunning(isRunning)
      {

      }

      Function tabFn;
      bool isRunning;

      int32_t TabPosX = 90;
      int32_t TabPosY = 3;
      int32_t TabBaseY = 0;
      uint32_t TabTitleHeight = 16;
      uint32_t TabOptionHeight = 10;
      Color TabTitleTextColor{ 255, 255, 255, 255 };

      size_t PrintingOption = 0;
      size_t CurrentOption = 0;
      size_t SavedCurrentOption = 0;
      size_t TotalOptions = 0;
      size_t StartInfiniteScroll = 8;
      size_t EndInfiniteScroll = 6;
      size_t OptionsPerPage = 14;
      uint32_t OptionHeight = 50;
      Color TextColor{ 255, 255, 255, 255 };
      Color TextColorHighlighted{ 255, 0, 0, 255 };
      Color BackgroundColor{ 10, 10, 10, 170 };
      Color BackgroundColorHighlighted{ 0, 0, 255, 170 };
      Color ToggleColorOn{ 0, 255, 0, 255 };
      Color ToggleColorOff{ 255, 0, 0, 255 };
   };

public:
   explicit Menu() = default;
   explicit Menu(Function mainmenu, Function firstTab, Function secondTab, Function thirdTab);
   ~Menu() noexcept = default;

   void RegisterOnMain(Function onMain);
   void RegisterOnFirstTimeOpen(Function onFirstTime);
   void OnGameTick();

   bool IsEnterPressed();
   bool IsLeftPressed();
   bool IsRightPressed();
   bool IsLeftOrRightPressed();
   bool IsSquarePressed();
   bool tabPressed();
   bool tabHovered();
   void title(const std::wstring& text);
   Menu& tabmenu(const std::wstring& text);
   Menu& toggleTab(Function fn);
   bool pressed();
   bool hovered();
   void banner(const std::wstring& text);
   Menu& option(const std::wstring& text);
   Menu& toggle(bool& var);
   Menu& toggle(bool& var, Function onEnable, Function onDisable);
   Menu& local(bool var);
   Menu& action(OptionAction opt, Function fn);
   Menu& scroller(const std::vector<std::wstring>& display, int& index);
   Menu& keyboard(const std::wstring& windowTitle, const std::wstring& defaultText, size_t maxInputLength, KeyboardHandler handler);

private:
   bool IsInitialized();
   void Initialize();
   void Tick();
   void UpdateUI();
   bool IsOpenPressed();
   void UpdateDrawing();
   void UpdateEditTabPlacement();
   void UpdateButtons();
   void WhileOpen();
   void WhileClosed();
   void OnOpen();
   void OnClose();
   void OnScrollUp();
   void OnScrollDown();
   void OnTabLeft();
   void OnTabRight();
   bool IsTabDisplayed(Function fn);
   void AddTabToListIfNotInList(Function fn);
   TabComponent& GetTabComponent(Function fn);
   void DrawTabOptions(const std::wstring& text);
   void DrawTabToggle(bool var);
   void DrawMenuOption(const std::wstring& text);
   void DrawMenuToggle(bool var);
   void DrawMenuTextScroller(const std::wstring& var);
   template <typename T>
   void processOptionItemControls(T& var, T min, T max, T step)
   {
      if (hovered())
      {
         if (IsLeftPressed())
         {
            if (var <= min)
               var = max;
            else
               var -= step;
         }

         if (var < min)
            var = max;

         if (IsRightPressed())
         {
            if (var >= max)
               var = min;
            else
               var += step;
         }

         if (var > max)
            var = min;
      }
   }

private:
   bool m_Initialized{};
   bool m_Opened{};
   bool m_FirstTimeOpen = true;
   Function m_OnMain{};
   Function m_MainMenu{};
   Function m_FirstTab{};
   Function m_SecondTab{};
   Function m_ThirdTab{};
   Function m_OnFirstTimeOpen{};
   std::vector<TabComponent> m_TabList; // std::map doesn't work on PS3 so we will use a vector

   // Main Menu Dimensions
   uint32_t m_MainMenuPosX = 10;
   uint32_t m_MainMenuPosY = 50;
   uint32_t m_MainMenuWidth = 55;
   uint32_t m_MainMenuBaseY = 0;
   size_t m_MainMenuPrintingTab = 0;
   size_t m_MainMenuCurrentTab = 0;
   size_t m_MainMenuSavedCurrentTab = 0;
   size_t m_MainMenuTotalTabs = 0;
   size_t m_MainMenuTabStartInfiniteScroll = 8;
   size_t m_MainMenuTabEndInfiniteScroll = 6;
   size_t m_MainMenuTabOptionsPerPage = 14;
   bool m_CanEditTabPlacement = false;

   // Main Menu Title
   uint32_t m_MainMenuTitleHeight = 16;
   Color m_MainMenuTitleTextColor{ 255, 255, 255, 255 };

   // Main Menu Options
   uint32_t m_MainMenuOptionHeight = 10;
   Color m_MainMenuTabTextColor{ 255, 255, 255, 255 };
   Color m_MainMenuTabTextColorHighlighted{ 255, 0, 0, 255 };
   Color m_MainMenuTabBackgroundColor{ 10, 10, 10, 170 };
   Color m_MainMenuTabBackgroundColorHighlighted{ 0, 0, 255, 170 };

   // Tab Options
   Function m_ActiveTab{};
};

extern Menu g_Menu;