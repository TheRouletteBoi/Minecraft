#pragma once

#include <functional>

#include "minecraftpe/entity/player/Player.h"
#include "minecraftpe/item/ItemInstance.h"
#include "minecraftpe/level/dimension/DimensionId.h"
#include "minecraftpe/client/resources/SkinInfoData.h"
#include "minecraftpe/util/UUID.h"

class Level;
class PacketSender;
class Vec3;
class MobEffectInstance;
class Tick;
class BlockPos;

// Size : 3624
class ServerPlayer : public Player
{
public:
	char filler[20];		// 3588
	char containerCounter;	// 3608

	ServerPlayer(Level &, PacketSender &, GameType, const RakNet::RakNetGUID &, std::function<void (ServerPlayer &)>, std::unique_ptr<SkinInfoData>, mce::UUID);
	virtual ~ServerPlayer();
	virtual void normalTick();
	virtual void push(const Vec3 &);
	virtual void changeDimension(DimensionId);
	virtual void knockback(Entity *, int, float, float);
	virtual void aiStep();
	virtual void hurtArmor(int);
	virtual void onEffectAdded(MobEffectInstance &);
	virtual void onEffectUpdated(const MobEffectInstance &);
	virtual void onEffectRemoved(MobEffectInstance &);
	virtual void tickWorld(const Tick &);
	virtual void hasResource(int);
	virtual void openContainer(int, const BlockPos &);
	virtual void openContainer(int, const EntityUniqueID &);
	virtual void openFurnace(int, const BlockPos &);
	virtual void openEnchanter(int, const BlockPos &);
	virtual void openAnvil(const BlockPos &);
	virtual void openBrewingStand(int, const BlockPos &);
	virtual void openHopper(int, const BlockPos &);
	virtual void openHopper(int, const EntityUniqueID &);
	virtual void openDispenser(int, const BlockPos &, bool);
	virtual void displayLocalizableMessage(const std::string &, const std::vector<std::string> &);
	virtual void stopSleepInBed(bool, bool);
	virtual void setPlayerGameType(GameType);
	virtual void setContainerData(IContainerManager &, int, int);
	virtual void slotChanged(IContainerManager &, int, const ItemInstance &, bool);
	virtual void refreshContainer(IContainerManager &, const std::vector<ItemInstance> &);
	virtual void deleteContainerManager();
	void disconnect();
};
