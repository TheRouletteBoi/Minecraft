#pragma once

#include "../Mob.h"
#include "../../gamemode/GameType.h"
#include "../../util/UUID.h"
#include "Abilities.h"
#include "../../network/Packet.h"
#include "../../item/ItemInstance.h"
#include "../../block/BlockPos.h"
#include "raknet/RakNetTypes.h"

class Level;
class BaseContainerMenu;
class PlayerChunkSource;
class Inventory;
class SkinInfoData;
class PacketSender;
class BatchPacket;
class ChunkSource;
class Tick;
class BlockEntity;
class EntityDamageSource;
class TelemetryEventPacket;
class CompoundTag;
class IContainerManager;

// Size : 3588
class Player : public Mob
{
public:
	static Attribute EXHAUSTION;
	static Attribute EXPERIENCE;
	static Attribute HUNGER;
	static Attribute LEVEL;
	static Attribute SATURATION;

	int i1;								// 3272
	bool b4;							// 3276
	int score;							// 3280
	char filler2[12];					// 3284
	std::string username;				// 3296
	Abilities abilities;				// 3300
	BaseContainerMenu *activeContainer;	// 3316
	RakNet::RakNetGUID guid;			// 3320
	std::string what;					// 3336
	char filler4[4];					// 3340
	long long clientId;					// 3344
	mce::UUID uuid;						// 3352
	char filler5[20];					// 3368
	PlayerChunkSource *chunk1;			// 3388
	PlayerChunkSource *chunk2;			// 3392
	BlockSource *region;				// 3396
	BlockPos bedPos;					// 3400
	char filler6[60];					// 3412
	Inventory *inventory;				// 3472
	SkinInfoData *skin;					// 3476
	char filler7[4];					// 3480
	DimensionId respawnDimensionId;		// 3484
	bool b2;							// 3488
	ItemInstance usingItem;				// 3492
	char filler8[8];					// 3512
	PacketSender *packetSender;			// 3520
	BatchPacket *batchPacket;			// 3524
	char filler9[16];					// 3528
	BlockPos spawnPos;					// 3544
	char filler10[20];					// 3556
	GameType gameType;					// 3576
	char filler11[4];					// 3580
	int viewDistance;					// 3584

	Player(Level &, PacketSender &, GameType, const RakNet::RakNetGUID &, std::unique_ptr<SkinInfoData>, mce::UUID);
	virtual ~Player();
	virtual void remove();
	virtual std::unique_ptr<Packet> getAddPacket();
	virtual void normalTick();
	virtual void rideTick();
	virtual void getRidingHeight();
	virtual bool isInWall();
	virtual float getHeadHeight() const;
	virtual bool isImmobile() const;
	virtual bool isPushable() const;
	virtual bool isShootable();
	virtual bool isCreativeModeAllowed();
	virtual void hurt(const EntityDamageSource &, int);
	virtual void handleEntityEvent(EntityEvent);
	virtual void awardKillScore(Entity &, int);
	virtual void setEquippedSlot(ArmorSlot, int, int);
	virtual void setEquippedSlot(ArmorSlot, const ItemInstance &);
	virtual EntityType getEntityTypeId() const;
	virtual void getPortalCooldown() const;
	virtual void getPortalWaitTime() const;
	virtual void sendMotionPacketIfNeeded();
	virtual void lavaHurt();
	virtual void readAdditionalSaveData(const CompoundTag &);
	virtual void addAdditionalSaveData(CompoundTag &);
	virtual void die(const EntityDamageSource &);
	virtual bool isSleeping() const;
	virtual void getSpeed();
	virtual void setSpeed(float);
	virtual void travel(float, float);
	virtual void aiStep();
	virtual ItemInstance *getCarriedItem();
	virtual void getItemUseDuration();
	virtual void dropAllGear(int);
	virtual void drop(const ItemInstance *, bool);
	virtual void sendInventory() const;
	virtual void dropDeathLoot(int);
	virtual void dropRareDeathLoot();
	virtual void jumpFromGround();
	virtual void updateAi();
	virtual void getExperienceReward() const;
	virtual bool useNewAi();
	virtual void registerAttributes();
	virtual void prepareRegion(ChunkSource &);
	virtual void destroyRegion();
	virtual void suspendRegion();
	virtual void onPrepChangeDimension();
	virtual void onDimensionChanged();
	virtual void tickWorld(const Tick &);
	virtual void moveView();
	virtual void setName(const std::string &);
	virtual void _checkMovementStatistiscs(const Vec3 &);
	virtual void respawn();
	virtual bool isInTrialMode();
	virtual void hasResource(int);
	virtual void completeUsingItem();
	virtual void drop(const ItemInstance *);
	virtual void startCrafting(const BlockPos &);
	virtual void startStonecutting(const BlockPos &);
	virtual void startDestroying();
	virtual void stopDestroying();
	virtual void openContainer(int, const BlockPos &);
	virtual void openContainer(int, const EntityUniqueID &);
	virtual void openFurnace(int, const BlockPos &);
	virtual void openEnchanter(int, const BlockPos &);
	virtual void openAnvil(const BlockPos &);
	virtual void openBrewingStand(int, const BlockPos &);
	virtual void openHopper(int, const BlockPos &);
	virtual void openHopper(int, const EntityUniqueID &);
	virtual void openDispenser(int, const BlockPos &, bool);
	virtual void displayChatMessage(const std::string &, const std::string &);
	virtual void displayClientMessage(const std::string &);
	virtual void displayLocalizableMessage(const std::string &, const std::vector<std::string> &);
	virtual void startSleepInBed(const BlockPos &);
	virtual void stopSleepInBed(bool, bool);
	virtual void getSleepTimer();
	virtual void openTextEdit(BlockEntity *);
	virtual bool isLocalPlayer() const;
	virtual void stopLoading();
	virtual void setPlayerGameTypePacketReceived(GameType);
	virtual void setPlayerGameType(GameType);
	virtual void _crit(Entity &);
	virtual void getTelemetry() const;
	virtual void sendTelemetryPacket(const TelemetryEventPacket &);
	virtual void setContainerData(IContainerManager &, int, int) = 0;
	virtual void slotChanged(IContainerManager &, int, const ItemInstance &, bool) = 0;
	virtual void refreshContainer(IContainerManager &, const std::vector<ItemInstance> &) = 0;
	virtual void deleteContainerManager();
	virtual void onMovePlayerPacketNormal(const Vec3 &, const Vec2 &);
	static bool isValidUserName(const std::string &);
	ItemInstance *getSelectedItem() const;
	bool IsCreative() const;
	bool IsSurvival() const;
	bool IsViewer() const;
	Dimension *getDimension() const;
	bool hasRespawnPosition() const;
	BlockPos getSpawnPosition();
	void setRespawnPosition(const BlockPos &);
	void setSkin(const std::string &, const std::string &);
	void take(Entity &, int);
};
