#pragma once

#include "../Entity.h"

class ItemEntity : public Entity
{
public:
	static int LIFETIME;

public:
	ItemEntity(BlockSource &);
	ItemEntity(BlockSource &, float, float, float, const ItemInstance &);
	virtual ~ItemEntity();
	virtual void normalTick();
	virtual void playerTouch(Player &);
	virtual bool isPushable() const;
	virtual void hurt(EntityDamageSource const &, int);
	virtual int getEntityTypeId() const;
	virtual bool isItemEntity();
	virtual void getHandleWaterAABB() const;
	virtual void burn(int);
	virtual void readAdditionalSaveData(CompoundTag const&);
	virtual void addAdditionalSaveData(CompoundTag &);
	void _validateitem();
	bool checkInTile(float, float, float);
	float getLifeTime();
};
