#include "WorldAssetFactory.h"

#include "../../../game/world/World.h"

std::unique_ptr<Object> WorldAssetFactory::CreateBlankObject()
{
	return std::make_unique<World>();
}
