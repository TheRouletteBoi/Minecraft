#pragma once

#include <memory>
#include "../gamemode/GameType.h"

class GameCallbacks;
class SkinInfoFactory;
class Vibration;
class SoundPlayer;
class Whitelist;
class LevelSettings;
class ServerCommandParser;
class GameMode;
class Level;
class NetEventCallback;
class PacketSender;
class RakNetInstance;
class ServerNetworkHandler;
class Player;
class MultiPlayerGameMode;
class MultiPlayerLevel;
class MultiplayerLocalPlayer;


// Size : 0x0068
class Minecraft
{
public:
   uint32_t* m_dataFixerUpper; //0x0000 
   MultiPlayerGameMode* m_multiPlayerGameMode; //0x0004 
   char _0x0008[8];
   uint32_t m_displayWidth; //0x0010 
   uint32_t m_displayHeight; //0x0014 
   uint32_t m_displayWidth2; //0x0018 
   uint32_t m_displayHeight2; //0x001C 
   uintptr_t* m_worldTime; //0x0020 
   char _0x0024[8];
   MultiPlayerLevel* m_multiPlayerLevel; //0x002C 
   uint32_t* m_levelRenderer; //0x0030 
   MultiplayerLocalPlayer* m_multiplayerLocalPlayer; //0x0034 
   uintptr_t* m_SmartPointerMultiplayerLocalPlayer; //0x0038 
   uintptr_t* _0x003C; //0x003C 
   char _0x0040[4];
   MultiplayerLocalPlayer* m_multiplayerLocalPlayer2; //0x0044 
   uintptr_t* m_SmartPointerMultiplayerLocalPlayer2; //0x0048 
   char _0x004C[24];
   MultiPlayerGameMode* m_multiPlayerGameMode2; //0x0064 
   char _0x0068[0x98];
   uintptr_t m_fontRender; //0x00FC

public:
	Minecraft(GameCallbacks &, SkinInfoFactory &, Vibration &, SoundPlayer &, Whitelist const &, std::string const &);
	~Minecraft();
	void createGameMode(GameType, Level &);
	void createLevel(std::string const &, std::string const &, LevelSettings const &);
	ServerCommandParser *getCommandParser();
	GameMode *getGameMode();
	Level *getLevel();
	void *getLevelSource();
	NetEventCallback *getNetEventCallback();
	PacketSender *getPacketSender();
	RakNetInstance *getRakNetInstance();
	std::string getServerName();
	ServerNetworkHandler *getServerNetworkHandler();
	void *getTimer();
	void *getUser();
	void hostMultiplayer(void*, void*, Player *, void*, bool, int, int); // std::unique_ptr<Level>, std::unique_ptr<GameMode>, Player *, std::unique_ptr<NetEventCallback>, bool, int, int
	void init(std::string const &);
	void initAsDedicatedServer();
	bool isModded();
	bool isOnlineClient();
	void onClientStartedLevel(void*); // std::unique_ptr<Level>
	void resetGameSession();
	void restartMultiplayerHost(int, int);
	void setGameModeReal(GameType);
	void setLeaveGame();
	void setupServerCommands();
	void startClientGame(void*); // std::unique_ptr<NetEventCallback>
	void stopGame();
	void teardown();
	void tick(int, int);
	void update();
};
