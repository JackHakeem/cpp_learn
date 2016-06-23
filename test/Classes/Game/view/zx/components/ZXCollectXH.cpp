#include "ZXCollectXH.h"

void ZXCollectXH::removeself(CCNode* pSender)
{
	this->removeFromParentAndCleanup(true);
}