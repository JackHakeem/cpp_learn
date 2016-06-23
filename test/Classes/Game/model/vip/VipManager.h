#ifndef _VIP_MANAGER_H_
#define _VIP_MANAGER_H_
#include "utils/Singleton.h"
#include "vo/VipContentVo.h"
#include "BaseType.h"
#include "vo/VipGiftVo.h"

class VipManager : public Singleton<VipManager>
{
public:
	VipManager() {}
	~VipManager() {}

	void createVipContent(std::list<VipContentVo *> list);
	VipContentVo *getVipContent(int type, int lev);
	std::list<VipGiftVo *> getVipGiftList(int vipLev);

	void setVipGiftList(std::list<VipGiftVo *> giftList, int vipLev);
public:
	std::list<VipContentVo *> _vipContentDic;
	std::map<int, std::list<VipGiftVo *> > _vipGift;
};
#endif