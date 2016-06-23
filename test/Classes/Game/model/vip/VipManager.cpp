#include "VipManager.h"

void VipManager::createVipContent( std::list<VipContentVo *> list )
{
	_vipContentDic = list;
}

VipContentVo * VipManager::getVipContent( int type, int lev )
{
	return NULL;
}

std::list<VipGiftVo *> VipManager::getVipGiftList( int vipLev )
{
	std::map<int, std::list<VipGiftVo *> >::iterator it = _vipGift.find(vipLev);
	if(it != _vipGift.end())
	{
		return it->second;
	}
	return (std::list<VipGiftVo *>) NULL;
}

void VipManager::setVipGiftList( std::list<VipGiftVo *> giftList, int vipLev )
{
	_vipGift.insert(std::map<int, std::list<VipGiftVo *> >::value_type(vipLev, giftList));
}
