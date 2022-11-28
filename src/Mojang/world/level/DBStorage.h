#pragma once

#include "minecraftpe/level/LevelStorage.h"

class DBStorage : public LevelStorage
{
public:
	virtual ~DBStorage();
	virtual void loadLevelData(LevelData &);
	virtual void createChunkStorage(std::unique_ptr<ChunkSource>, StorageVersion);
	virtual void saveLevelData(LevelData &);
	virtual void getFullPath() const;
	virtual void savePlayerData(const std::string &, std::string &&);
	virtual void saveData(const std::string &, std::string &&);
	virtual bool isCorrupted() const;
	virtual void loadData(const std::string &);
	virtual void getState() const;
	virtual void loadPlayerData(const std::string &);
	virtual void loadAllPlayerIDs();
	virtual void save(Player &);
	virtual void getLevelId() const;
	virtual void getBackupFiles();
	virtual void openStorage();
	virtual void closeStorage();
	virtual bool isStorageOpen() const;
};
