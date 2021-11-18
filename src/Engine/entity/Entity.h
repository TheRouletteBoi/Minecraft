#pragma once

#include <string>
#include <vector>
#include "SynchedEntityData.h"
#include "../util/AABB.h"
#include "../util/Vec2.h"
#include "../util/Vec3.h"

enum ArmorSlot;
enum EntityEvent;
enum MaterialType;
enum class DimensionId;
class Level;
class BlockSource;
class Random;
class Material;
class Player;
class EntityDamageSource;
class CompoundTag;
class ItemInstance;
class EntityPos;
class EntityLink;
class BlockPos;
class EntityUniqueID;
class ChangeDimensionPacket;
class Matrix;

// Size : 324
class Entity
{
public:
   void* m_vTable; //0x0000 
	uintptr_t m_this; //0x0004 
   MultiplayerLocalPlayer* m_multiplayerLocalPlayer; //0x0008 
   uint32_t entityId; //0x000C 
   char _0x0010[96];
   MultiPlayerLevel* m_multiPlayerLevel; //0x0070 
   Color m_color; //0x0074 
   char _0x0084[98];
   Vec2 m_prevViewAngles; //0x00E0 
   char _0x00E8[4];
   uintptr_t* m_vehicle; //0x00EC 
	uintptr_t* m_vehicle2; //0x00F0 
   char _0x00F4[4];
   MultiPlayerLevel* m_multiPlayerLevel2; //0x00F8 
   char _0x00FC[4];
   Vec3 m_pos; //0x0100 
   Vec3 m_lastPos; //0x010C 
   Vec3 m_motion; //0x0118 
   Vec3 m_rotation; //0x0124 
   Vec3 m_lastRotation; //0x0130 
   Vec3 m_pos3; //0x013C 
   Vec2 m_viewAngles; //0x0148 
   Vec2 m_viewAngles2; //0x0150 
   Matrix* m_matrix; //0x0158 
   uint8_t N59AD4F87; //0x015C 
   uint8_t N59B24B77; //0x015D 
   uint8_t m_OnGround; //0x015E 
   uint8_t m_OnGround2; //0x015F 
   char _0x0160[4];
   uint8_t m_fireTicks; //0x0164 
   uint8_t m_fireTicks2; //0x0165 
   uint8_t N59BCF42D; //0x0166 
   uint8_t N59BCE6CD; //0x0167 
   char _0x0168[44];
   uint8_t m_isInWeb; //0x0194 
   uint8_t m_isOutsideBorder; //0x0195 
   uint8_t N59BE0FD5; //0x0196 
   uint8_t N59BE03CD; //0x0197 
   char _0x0198[68];
   uint8_t m_collision; //0x01DC 
   char _0x01DD[15];
   uint8_t m_isInwater; //0x01EC 
   uint8_t m_headInWater; //0x01ED 
   uint16_t m_unknown001; //0x01EE 
   char _0x01F0[8];
	uintptr_t* m_dataItems; //0x01F8 
   uint32_t* m_SynchedEntityData; //0x01FC 
   char _0x0200[320];
   uint32_t* m_ModifiableAttributeMap; //0x0340 
   char _0x0344[40];
   ItemInstance* m_itemInstance; //0x036C 
   char _0x0370[12];
   ItemInstance* m_itemInstance2; //0x037C 
   char _0x0380[880];
   uint8_t m_portalWaitTime; //0x06F0 
   uint8_t m_isOnGround; //0x06F1 
   uint8_t m_setCanFly; //0x06F2 
   uint8_t N59C4BBB3; //0x06F3 
   char _0x06F4[12];
   uint32_t m_xpLevel; //0x0700 
   uint32_t m_xpAmount; //0x0704 
   char _0x0708[236];
   uint16_t N59C3298B; //0x07F4 
   uint16_t m_hostPrivilegesFlags; //0x07F6		  0xF990 = invisible   0xF810 = visible   0xF830 = can fly   0xF850 = disable exhaustion  0xFA10 = creative  0x1A00 = in mini game
   char _0x07F8[232];
   float m_timeInPortal; //0x08E0 
   char _0x08E4[420];

public:
	Entity(Level &);
	Entity(BlockSource &);
	virtual ~Entity();
	virtual void _postInit();
	virtual void reset();
	virtual void getOwnerEntityType();
	virtual void remove();
	virtual void setPos(Vec3 const &);
	virtual void getPos() const;
	virtual void getPosOld() const;
	virtual void getPosExtrapolated(float) const;
	virtual void getVelocity() const;
	virtual void move(Vec3 const &);
	virtual void checkBlockCollisions(AABB const &);
	virtual void checkBlockCollisions();
	virtual void moveRelative(float, float, float);
	virtual void lerpTo(Vec3 const &, Vec2 const &, int);
	virtual void lerpMotion(Vec3 const &);
	virtual void turn(Vec2 const &);
	virtual void interpolateTurn(Vec2 const &);
	virtual void getAddPacket();
	virtual void normalTick();
	virtual void baseTick();
	virtual void rideTick();
	virtual void positionRider(Entity &) const;
	virtual float getRidingHeight();
	virtual float getRideHeight() const;
	virtual void startRiding(Entity &);
	virtual void addRider(Entity &);
	virtual void removeRider(Entity &);
	virtual void intersects(Vec3 const &, Vec3 const &);
	virtual bool isFree(Vec3 const &, float);
	virtual bool isFree(Vec3 const &);
	virtual bool isInWall();
	virtual bool isInvisible();
	virtual void canShowNameTag();
	virtual void setNameTagVisible(bool);
	virtual void getNameTag() const;
	virtual void setNameTag(std::string const &);
	virtual bool isInWater() const;
	virtual bool isInWaterOrRain();
	virtual bool isInLava();
	virtual bool isUnderLiquid(MaterialType) const;
	virtual void makeStuckInWeb();
	virtual float getHeadHeight() const;
	virtual void getShadowHeightOffs();
	virtual void getShadowRadius() const;
	virtual bool isSkyLit(float);
	virtual void getBrightness(float);
	virtual void interactPreventDefault();
	virtual void interactWithPlayer(Player &);
	virtual bool canInteractWith(Player &);
	virtual void getInteractText(Player &);
	virtual void playerTouch(Player &);
	virtual void push(Entity &, bool);
	virtual void push(Vec3 const &);
	virtual bool isImmobile() const;
	virtual bool isSilent();
	virtual bool isPickable();
	virtual bool isPushable() const;
	virtual bool isShootable();
	virtual bool isSneaking() const;
	virtual bool isAlive();
	virtual bool isOnFire() const;
	virtual bool isCreativeModeAllowed();
	virtual bool isSurfaceMob() const;
	virtual void shouldRenderAtSqrDistance(float);
	virtual void hurt(EntityDamageSource const &, int);
	virtual void animateHurt();
	virtual void doFireHurt(int);
	virtual void onLightningHit();
	virtual void handleEntityEvent(EntityEvent);
	virtual void getPickRadius();
	virtual void spawnAtLocation(int, int);
	virtual void spawnAtLocation(int, int, float);
	virtual void spawnAtLocation(ItemInstance const &, float);
	virtual void awardKillScore(Entity &, int);
	virtual void setEquippedSlot(ArmorSlot, int, int);
	virtual void setEquippedSlot(ArmorSlot, ItemInstance const &);
	virtual void save(CompoundTag &);
	virtual void saveWithoutId(CompoundTag &);
	virtual void load(CompoundTag const &);
	virtual void loadLinks(CompoundTag const &, std::vector<EntityLink> &);
	virtual int getEntityTypeId() const = 0;
	virtual void queryEntityRenderer();
	virtual void getSourceUniqueID();
	virtual void setOnFire(int);
	virtual void getHandleWaterAABB() const;
	virtual void handleInsidePortal();
	virtual void getPortalCooldown() const;
	virtual void getPortalWaitTime() const;
	virtual void getDimensionId() const;
	virtual void changeDimension(DimensionId);
	virtual void changeDimension(ChangeDimensionPacket &);
	virtual void getControllingPlayer() const;
	virtual void checkFallDamage(float, bool);
	virtual void causeFallDamage(float);
	virtual void playSound(std::string const &, float, float);
	virtual void onSynchedDataUpdate(int);
	virtual void canAddRider(Entity &) const;
	virtual void sendMotionPacketIfNeeded();
	virtual void stopRiding(bool);
	virtual void buildDebugInfo(std::string &) const;
	virtual void setSize(float, float);
	virtual void setPos(EntityPos const &);
	virtual void outOfWorld();
	virtual void markHurt();
	virtual void burn(int);
	virtual void lavaHurt();
	virtual void readAdditionalSaveData(CompoundTag const &) = 0;
	virtual void addAdditionalSaveData(CompoundTag &) = 0;
	virtual void _playStepSound(BlockPos const &, int);
	virtual void checkInsideBlocks(float);
	virtual void pushOutOfBlocks(Vec3 const &);
	virtual void updateWaterState();
	virtual void doWaterSplashEffect();
	virtual void updateInsideBlock();
	virtual void onBlockCollision(int);
	void _findRider(Entity &) const;
	void _init();
	void _manageRiders(BlockSource &);
	void _sendLinkPacket(const EntityLink &) const;
	void _tryPlaceAt(const Vec3 &);
	void _updateOwnerChunk();
	void checkTileCollisions();
	void distanceSqrToBlockPosCenter(const BlockPos &);
	void distanceTo(Entity *);
	void distanceTo(float, float, float);
	void distanceToSqr(Entity *);
	void distanceToSqr(float, float, float);
	void enableAutoSendPosRot(bool);
	void getCenter(float);
	void getInterpolatedPosition(float) const;
	void getInterpolatedPosition2(float) const;
	void getInterpolatedRotation(float) const;
	void getLinks() const;
	void getRandomPointInAABB(Random &);
	Vec2 &getRotation() const;
	void getStatusFlag(int) const;
	void getStatusFlag(int, bool);
	void getUniqueID() const;
	void getViewVector(float) const;
	void getViewVector2(float) const;
	bool hasUniqueID() const;
	bool isControlledByLocalInstance() const;
	bool isInClouds() const;
	bool isInstanceOf(int) const;
	bool isMob() const;
	bool isRide() const;
	bool isRider(Entity &) const;
	bool isRiding() const;
	void moveTo(const Vec3 &, const Vec2 &);
	bool operator==(Entity &);
	void removeAllRiders();
	void saveLinks() const;
	//void sendMotionPacketIfNeeded();
	void sendMotionToServer();
	//void setOnFire(int);
	void setRegion(BlockSource &);
	void setUniqueID(EntityUniqueID);
	void shouldRender();
};
