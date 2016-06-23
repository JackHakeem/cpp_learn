#include "PlayerEffectManage.h"
#include "vo/PlayerEffectInfoVo.h"

PlayerEffectManage::PlayerEffectManage()
{
}

PlayerEffectManage::~PlayerEffectManage()
{
	if ( _animateDic.size() == 0 )
	{
		return;//jae
	}
	
	std::map<int,PlayerEffectInfoVo*>::iterator iter = _animateDic.begin();
	if ( iter == _animateDic.end() )
	{
		return;
	}
	
	for( ;
		iter != _animateDic.end();iter++ )
	{
		CC_SAFE_DELETE( iter->second );
		//_animateDic.erase(iter->first);
	}
	_animateDic.clear();
}

void PlayerEffectManage::setAniInfo(PlayerEffectInfoVo* info)
{
	_animateDic.insert(make_pair(info->_type,info));
}

PlayerEffectInfoVo* PlayerEffectManage::getAniInfoByType(int type)
{
	std::map<int,PlayerEffectInfoVo*>::iterator iter = _animateDic.find(type);
	if (iter != _animateDic.end())
	{
		return iter->second;
	}
	return 0;
}