#include "TipsSkillCanvas.h"
#include "utils/ValuesUtil.h"
#include "utils/TipHelps.h"
#include "utils/TipBase.h"
#include "model/skill/vo/UpGradeInfo.h"
#include "model/skill/SkillTipsTool.h"
#include "model/skill/vo/SkillType.h"
#include "view/figure/components/SkillItem.h"
#include "utils/ScaleUtil.h"
#include "view/recruit/RecruitMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/recruit/components/RecruitView.h"

TipsSkillCanvas* g_pTipsSkillCanvas = 0;

TipsSkillCanvas::TipsSkillCanvas()
{
	
}

bool TipsSkillCanvas::displayTip(CCPoint coordinate, TipBase* tips, char* param, TipBase* otherTips)
{
	if (!tips || !tips->_myInfo)
		return false;

	//
	m_alert = new Alert();
	if (!m_alert) 
		return false;
	m_alert->initWithParam(CCRectMake(0, 0, 0, 0), true);
	this->addChild(m_alert);
	m_alert->release(); // Kenfly 20130204
	//
	UpGradeInfo* skillInfo = tips->_myInfo;
	SUBSKILLTIPS* subTips = skillInfo->subTips;
	if (!skillInfo)
		return false;

	{
		//名字
		{
			std::string tmpstr = subTips->name;
			m_alert->addStr(tmpstr, subTips->color_name);
		}
		//等级
		{
			if (subTips->rank==SkillType::PASSVIE)
			{
				if(subTips->lev>0)
				{
					if(skillInfo->needLevel==0)
					{
						char str[40];
						sprintf(str, ValuesUtil::Instance()->getString("SKLC026").c_str(), subTips->lev);
						std::string tmpstr = str;
						m_alert->addStr(tmpstr, ccc3(255, 102, 0));
					}
					else
					{
						std::string tmpstr1 = ValuesUtil::Instance()->getString("SKLC027");
						CCLog("%s", tmpstr1.c_str());
						char str[40];
						sprintf(str, ValuesUtil::Instance()->getString("SKLC027").c_str(), subTips->lev);
						std::string tmpstr = str;
						m_alert->addStr(tmpstr, ccc3(255, 102, 0));
					}
				}
			}
		}
		//描述
		{
			std::string tmpstr = subTips->desc;
			m_alert->addStr(tmpstr, ccc3(51, 204, 0));		
		}
		//
		{
			std::string needLevTip="";
			if (subTips->style == 1)//人物面板上技能的提示信息
			{
				// add by LH 0726
				if (subTips->rank==SkillType::SKILL)
				{
					RecruitMediator* pMeditor = (RecruitMediator*)g_pFacade->retrieveMediator(AppFacade_RECRUIT_PROXY_CHANGE);
					if (pMeditor && pMeditor->_recruitView && pMeditor->_recruitView->getisPop() )
					{
						;
					}
					else
						m_alert->addButton(
							ValuesUtil::Instance()->getString("SKLC001").c_str(), 
							(SkillItem*)param, menu_selector(SkillItem::handleEquip));
				}
			}
			else if (subTips->style == 2)//技能列表中的提示信息 
			{
				std::string tmpstr = ValuesUtil::Instance()->getString("SKLC028");
				m_alert->addStr(tmpstr, ccc3(255, 255, 255));

				if (subTips->rank==SkillType::PASSVIE)
				{
					if (skillInfo->needLevel == 0)
					{
						std::string tmpstr = ValuesUtil::Instance()->getString("SKLC029");
						m_alert->addStr(tmpstr, ccc3(255, 0, 0));						
					}
					else
					{
						char str[40];
						sprintf(str, ValuesUtil::Instance()->getString("SKLC031").c_str(), skillInfo->needLevel);
						std::string tmpstr = str;
						m_alert->addStr(tmpstr, ccc3(255, 0, 0));						
					}
					
					RecruitMediator* pMeditor = (RecruitMediator*)g_pFacade->retrieveMediator(AppFacade_RECRUIT_PROXY_CHANGE);
					if (pMeditor && pMeditor->_recruitView && pMeditor->_recruitView->getisPop() )
					{
						;
					}
					else
						m_alert->addButton(ValuesUtil::Instance()->getString("SKLC001").c_str(), (SkillItem*)param, menu_selector(SkillItem::handleEquip));//menu_selector(BagGoods::OnTimer) 
				}
				else if (subTips->rank == SkillType::SKILL)
				{
					if (skillInfo->active)
					{
						std::string tmpstr = ValuesUtil::Instance()->getString("SKLC042");
						m_alert->addStr(tmpstr, ccc3(157, 157, 157));							
					}
					else
					{
					//	std::string tmpstr = ValuesUtil::Instance()->getString("SKLC040");
					//	m_alert->addStr(tmpstr, ccc3(255, 0, 0));						
					}
				}
			}
		}


		//排版显示
		m_alert->show();


		CCSize skillFrameSize = tips->getSrcContentSize();
		//设置本宽高
		this->setContentSize(m_alert->getBgSize());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();


		CCPoint p = coordinate;

		if (p.x <= POSX(960)/2)
		{//点在左边
			this->setPosition(ccp(p.x+POSX(98),  p.y-m_alert->getContentSize().height+POSX(50)));				
		}
		else	
		{//点在右边
			this->setPosition(ccp(p.x-m_alert->getBgSize().width,  p.y-m_alert->getContentSize().height+POSX(50)));			
		}

		//
		if (this->getPosition().y < POSX(55))
		{
			float disy = POSX(55) - this->getPosition().y;
			this->setPosition(ccp(this->getPosition().x, this->getPosition().y+disy));
		}	

	}

	return true;
}
