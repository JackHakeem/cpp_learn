#include "SilverMineManage.h"
#include "utils/GlobalScale.h"
void SilverMineManage::addBasicCfgByID(BasicMineVo infonode)
{
	if(480 == GlobalScale::Instance()->getStandardWidth())
	{
		infonode.x += 84;
		infonode.y -= 16;
	}
	_basicDic.insert(std::make_pair(infonode.mineId, infonode));
}
