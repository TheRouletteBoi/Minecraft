#pragma once

#include <memory>

#include "SkinInfoData.h"

class SkinInfoFactory
{
public:
	//void **vtable;	// 0

	virtual std::unique_ptr<SkinInfoData> createSkin() = 0;
};
