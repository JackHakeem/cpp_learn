#include "SkillPic.h"
#include "model/skill/SkillManager.h"
#include "model/skill/vo/UpGradeInfo.h"
#include "model/skill/SkillProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "utils/ScaleUtil.h"

SkillPic::SkillPic()
{
	_skillVo = 0;
}

bool SkillPic::initSkillPic( int skillId )
{
	_skillId = skillId;
	_skillVo = SkillManager::Instance()->getSkill( _skillId );
	if( !_skillVo )  return false;
	SkillProxy* pSkillProxy = (SkillProxy*)g_pFacade->retrieveProxy( AppFacade_SKILL_PROXY );
	if ( !pSkillProxy ) 	return false;
	UpGradeInfo* upInfo = pSkillProxy->getUpGradeInfo( _skillId, _skillVo->rank );
	if( !upInfo )  return false;
	//var tips:String = SkillTipsTool.createBaseTips(upInfo);

	char strFmt[54];
	sprintf( strFmt, "skill/%d.png", _skillVo->id );
	
	if ( !this->initWithSpriteFrameName(strFmt) )
	{
		return false;
	}
	this->setPosition( ccp( POSX(105/2+6), POSX(105/2+6) ) );
	//myTip = new TipHelps(false, 0, true);
	//myTip.setToolTips(this, tips);

	CC_SAFE_DELETE(upInfo); // ADD BY L.H. LEAK

	return true;
}

//  "在命之水晶达到30级时，您的佣兵将获得第二个特技"
void SkillPic::GreyandNewtip( string tips )
{
	//Utils.applyBlackAndWhiteFilter(this);
	//if(myTip){
	//	myTip.dispose();
	//	myTip = null;
	//}
	//myTip = new TipHelps();
	//myTip.setToolTips(this, tips);

}
