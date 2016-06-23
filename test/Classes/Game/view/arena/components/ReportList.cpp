#include "ReportList.h"
#include "ArenaUI.h"
#include "model/player/RoleManage.h"
#include "socket/command/s36/SCMD361.h"
#include "RankItem.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "model/arena/ArenaConst.h"
#include "manager/LangManager.h"
#include "Confirm.h"
#include "manager/LayerManager.h"
#include "manager/TimerManage.h"

const float FontSize = 18.0f;

ReportList::ReportList()
{}

ReportList::~ReportList()
{}

bool ReportList::initWithParam(ArenaUI* pContainer)
{
	if (!LayerNode::init())
		return false;

	_pContainer = pContainer;


	return true;
}

void ReportList::update(std::vector<SCMD361Node2>& array)
{
	//DisplayObjectManager.clearChildren(this);
	//for(var i:int = 0;i< array.length;i++){
	//	createItem(array[i] as SCMD361Node2, i);
	//}
	
	//Begin chenjian 20121018 : store the data, add btn node
	_data = array;

	CCMenu* pMenu = (CCMenu*)this->getChildByTag(ReportListTAG_menu);
	if (pMenu)
		pMenu->removeFromParentAndCleanup(true);
	//else
	{
		pMenu = new CCMenu();
		pMenu->init();
		pMenu->setPosition(POSX(0), POSX(0));
		pMenu->setTouchLayer(TLE::WindowLayer_Arena -1);
		this->addChild(pMenu, ReportListZ_menu + 10, ReportListTAG_menu);
		pMenu->release();
	}
	//End chenjian 20121018

	while (_data.size() > 2)
	{
		std::vector<SCMD361Node2>::iterator it= _data.begin();
		_data.erase(it);
	}
	int size = _data.size();
	//if (size>2) size=size;//2;
	// 
	//
	//int index =0;
	for (int i = 0; i < size; i++)
	{
		createItem(_data[i], i);
	}
}

/**战报对象**/
void ReportList::createItem(SCMD361Node2 data, int sitNum)
{
	std::string str = TimerManage::formatServerTimeToDate(data.a_time);

	str+= "  ";

	if(data.c_position==0){ // 进攻方（0：本人进攻，1：本人防守）
		char tmpstr[100];
		sprintf(tmpstr, ValuesUtil::Instance()->getString("JJC019").c_str(), data.b_name.c_str());
		str += tmpstr;
	}
	else{
		char tmpstr[100];
		sprintf(tmpstr, ValuesUtil::Instance()->getString("JJC020").c_str(), data.b_name.c_str());
		str += tmpstr;
	}

	if(data.d_result>0){  // 本人胜负情况（小于0失败，大于0胜利）
		char tmpstr[100];
		sprintf(tmpstr, "%s",ValuesUtil::Instance()->getString("JJC021").c_str());
		str += tmpstr;
	}
	else{
		char tmpstr[100];
		sprintf(tmpstr, "%s",ValuesUtil::Instance()->getString("JJC022").c_str());
		str += tmpstr;
	}

	str += " ";

	if(data.e_trend==0){
		str += ValuesUtil::Instance()->getString("JJC023");
	}
	else if(data.e_trend>0){
		str += ValuesUtil::Instance()->getString("JJC024");
	}
	else{
		str += ValuesUtil::Instance()->getString("JJC025");
	}

	CCObject* tmpold = this->getChildByTag(ReportListTAG_msg0+sitNum);
	if (tmpold)
		this->removeChildByTag(ReportListTAG_msg0+sitNum, true);
	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(str.c_str(), CCSizeMake(POSX(600), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
	pLabel->setPosition(ccp(POSX(625), POSX(640-500-sitNum*70)));
	this->addChild(pLabel, ReportListZ_msg0+sitNum, ReportListTAG_msg0+sitNum);
	pLabel->setColor(ccc3(55, 21, 0));	

	//Begin chenjian 20121018  add report button
	do
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CC_BREAK_IF(! pNormalSprite || ! pPressedSprite)

		CCMenuItemSprite *_btnReport = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(ReportList::onSelectReport));

		_btnReport->setPosition(POSX(880), POSX(640-500-sitNum*70));
		_btnReport->setScaleX(0.5f);
		_btnReport->setScaleY(0.7f);

		CCMenu* pMenu = (CCMenu*)this->getChildByTag(ReportListTAG_menu);
		CC_BREAK_IF(! pMenu);
		pMenu->addChild(_btnReport, sitNum, sitNum);
		//_btnReset->release();

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC050").c_str(), CCSizeMake(POSX(200), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
		CC_BREAK_IF(! pLabel);
		pLabel->setPosition(ccp(_btnReport->getContentSize().width/2, _btnReport->getContentSize().height/2));
		_btnReport->addChild(pLabel);
		pLabel->setColor(ccc3(255, 255, 255));
		pLabel->setScaleX(1.5);
		pLabel->setScaleY(1.5);

		pMenu->setIsVisible(false); //LH20130110

	} while (0);
	//End chenjian 20121018

}		

//Begin chenjian 20121018
void ReportList::onSelectReport(CCObject* pSender)
{
	int tag = (int)((CCNode*)pSender)->getTag();
	if (_data.size() > tag)
	{
		_pContainer->reportArena(_data[tag].f_report1, _data[tag].g_report2);
	}
}
//End chenjian 20121018