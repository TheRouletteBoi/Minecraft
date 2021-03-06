#pragma once

#include <deque>
#include <string>
#include "Screen.h"

class MinecraftClient;

namespace Touch
{
	class HeaderButton;
};

class ImageWithBackground;

// Size : 224
class ChatScreen : public Screen
{
public:
	static std::deque<std::string> sentMessages;

public:
   char filler1[20];		// 0
   MinecraftClient* mc;	// 20
   char filler2[112];		// 24
   std::string message;	// 136

public:
	ChatScreen(bool);
	virtual ~ChatScreen();
	virtual void onSetKeyboardHeight(float);
	virtual void removed();
	virtual void handleButtonPress(short);
	virtual void handleBackEvent(bool);
	virtual void handleTextChar(std::string const &, bool);
	virtual void setTextboxText(std::string const &);
	virtual void renderGameBehind() const;
	virtual void closeOnPlayerHurt() const;
	virtual void render(int, int, float);
	virtual void init();
	virtual void setupPositions();
	virtual void tick();
	virtual void _buttonClicked(Button &);
	void sendChatMessage();
	void drawChatMessages(int);
	void guiMessagesUpdated();
	void updateGuiMessages();
	void updateKeyboardVisibility();
	void updateToggleKeyboardButton();
};
