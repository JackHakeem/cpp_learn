#ifndef HLQS_Player_effect_manage_h
#define HLQS_Player_effect_manage_h
#include "utils/Singleton.h"
#include "vo/PlayerEffectInfoVo.h"

class PlayerEffectManage : public Singleton<PlayerEffectManage>
{
public:
	PlayerEffectManage();
	virtual ~PlayerEffectManage();

	void setAniInfo(PlayerEffectInfoVo* info);
	PlayerEffectInfoVo* getAniInfoByType(int type);
public:
	std::map<int,PlayerEffectInfoVo*> _animateDic;
};

#endif