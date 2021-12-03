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


class BaseTab
{
public:


};

class TabComponent : public BaseTab
{
public:

};



class Menu
{
public:
   struct TabComponent
   {
      TabComponent() = default;

      TabComponent(Function tabFn, bool isRunning) : tabFn(tabFn), isRunning(isRunning)
      {

      }

      TabComponent(Function tabFn, bool isRunning, int32_t tabPosX, int32_t tabPosY)
         : tabFn(tabFn), isRunning(isRunning), TabPosX(tabPosX), TabPosY(tabPosY)
      {

      }

      bool hovered()
      {
         return CurrentOption == PrintingOption;
      }

      bool pressed()
      {
         if (hovered())
         {
            return IsEnterPressed();
         }
         return false;
      }

      void banner(const std::wstring& text)
      {
         DrawShadowText(text,
            TabPosX,
            TabBaseY + (TabTitleHeight / 2),
            TabTitleTextColor, false);
         TabBaseY += TabTitleHeight;
      }

      TabComponent& option(const std::wstring& text)
      {
         PrintingOption++;
         DrawMenuOption(text);
         return *this;
      }

      TabComponent& toggle(bool& var)
      {
         DrawMenuToggle(var);

         if (pressed())
         {
            var ^= 1;
         }

         return *this;
      }

      TabComponent& toggle(bool& var, Function onEnable, Function onDisable)
      {
         DrawMenuToggle(var);

         if (pressed())
         {
            var ^= 1;

            if (var)
            {
               if (onEnable != nullptr)
                  onEnable();
            }
            else
            {
               if (onDisable != nullptr)
                  onDisable();
            }
         }

         return *this;
      }

      TabComponent& local(bool var)
      {
         DrawMenuToggle(var);
         return *this;
      }

      TabComponent& action(OptionAction opt, Function fn)
      {
         if (hovered())
         {
            if (opt == OptionAction::EnterPress && IsEnterPressed())
            {
               fn();
               return *this;
            }
            else if (opt == OptionAction::LeftPress && IsLeftPressed())
            {
               fn();
               return *this;
            }
            else if (opt == OptionAction::RightPress && IsRightPressed())
            {
               fn();
               return *this;
            }
            else if (opt == OptionAction::LeftOrRightPress && IsLeftOrRightPressed())
            {
               fn();
               return *this;
            }
            else if (opt == OptionAction::SquarePress && IsSquarePressed())
            {
               fn();
               return *this;
            }
         }
         return *this;
      }

      TabComponent& scroller(const std::vector<std::wstring>& display, int& index)
      {
         int min = 0;
         int max = static_cast<int>(display.size()) - 1;
         processOptionItemControls<int>(index, min, max, 1);

         if (index > static_cast<int>(display.size()) || index < 0)
            return *this;

         DrawMenuTextScroller(display[index].c_str());
         return *this;
      }

      TabComponent& keyboard(const std::wstring& windowTitle, const std::wstring& defaultText, size_t maxInputLength, KeyboardHandler handler)
      {
         if (pressed())
         {
            DisplayKeyboard(windowTitle, defaultText, maxInputLength, reinterpret_cast<void*>(handler));
         }
         return *this;
      }

      void DrawMenuOption(const std::wstring& text)
      {
         size_t haultIndex = 0;
         if (CurrentOption < StartInfiniteScroll && PrintingOption <= OptionsPerPage || TotalOptions <= OptionsPerPage)
         {
            haultIndex = PrintingOption;
         }
         else
         {
            if (CurrentOption >= StartInfiniteScroll)
            {
               if (CurrentOption > (TotalOptions - EndInfiniteScroll))
               {
                  haultIndex = StartInfiniteScroll + (EndInfiniteScroll - (TotalOptions - PrintingOption));
               }
               else
               {
                  haultIndex = StartInfiniteScroll + (PrintingOption - CurrentOption);
               }
            }
         }
         if (haultIndex > OptionsPerPage || haultIndex <= 0)
            return;

         DrawText(text,
            TabPosX,
            TabBaseY + (TabOptionHeight / 2),
            hovered() ? Color(255, 0, 0, 255) : Color(255, 255, 255, 255));

         TabBaseY += TabOptionHeight;
      }

      void DrawMenuToggle(bool var)
      {

      }

      void DrawMenuTextScroller(const std::wstring& var)
      {

      }


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





      Function tabFn;
      bool isRunning;

      // middle of screen 
      // x = 166
      // y = 90

      int32_t TabPosX = 90;
      int32_t TabPosY = 3;
      int32_t TabBaseY = 0;
      int32_t TabTitleHeight = 16;
      int32_t TabOptionHeight = 10;
      Color TabTitleTextColor{ 0, 255, 255, 255 };

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
      Color ToggleColorOn{ 0, 255, 0, 100 };
      Color ToggleColorOff{ 255, 0, 0, 100 };
   };

public:
   explicit Menu() = default;
   explicit Menu(Function mainmenu, Function firstTab, Function secondTab, Function thirdTab, Function fourthTab);
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
   Menu& toggleTab(const TabComponent& comp);
   void AddTabToListIfNotInList(const TabComponent& comp);
   TabComponent& GetTabComponent(Function fn);

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
   
   void AddTabToListIfNotInListNew(Function fn, int32_t xPos, int32_t yPos);
   void DrawTabOptions(const std::wstring& text);
   void DrawTabToggle(bool var);

private:
   bool m_Initialized{};
   bool m_Opened{};
   bool m_FirstTimeOpen = true;
   Function m_OnMain{};
   Function m_MainMenu{};
   Function m_FirstTab{};
   Function m_SecondTab{};
   Function m_ThirdTab{};
   Function m_FourthTab{};
   Function m_OnFirstTimeOpen{};
   std::vector<TabComponent> m_TabList; // std::map doesn't work on PS3 so we will use a vector

   // Main Menu Dimensions
   uint32_t m_MainMenuPosX = 10;
   uint32_t m_MainMenuPosY = 50;
   uint32_t m_MainMenuWidth = 5;
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
   Color m_MainMenuTitleTextColor{ 255, 165, 0, 255 };

   // Main Menu Options
   uint32_t m_MainMenuOptionHeight = 10;
   Color m_MainMenuTabTextColor{ 255, 255, 255, 255 };
   Color m_MainMenuTabTextColorHighlighted{ 255, 0, 0, 255 };
   Color m_MainMenuTabBackgroundColor{ 128, 128, 128, 100 };

   // Tab Options
   Function m_ActiveTab{};
};

extern Menu g_Menu;
extern Menu::TabComponent g_CombatTab;
extern Menu::TabComponent g_MovmentTab;
extern Menu::TabComponent g_PlayerTab;
extern Menu::TabComponent g_VisualTab;
extern Menu::TabComponent g_WorldTab;
extern Menu::TabComponent g_ItemTab;
extern Menu::TabComponent g_EnchantmentTab;
extern Menu::TabComponent g_HostTab;
extern Menu::TabComponent g_DebugTab;