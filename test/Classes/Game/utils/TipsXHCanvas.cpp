#include "TipsXHCanvas.h"
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
#include "model/zx/XHConfManager.h"

TipsXHCanvas* g_pTipsXHCanvas = 0;

TipsXHCanvas::TipsXHCanvas()
{
	
}

bool TipsXHCanvas::displayTip(CCPoint coordinate, TipBase* tips, char* param, TipBase* otherTips)
{
	if (!tips || !tips->m_myXHInfo)
		return false;

	//
	m_alert = new Alert();
	if (!m_alert) 
		return false;
	m_alert->initWithParam(CCRectMake(0, 0, 0, 0), true);
	this->addChild(m_alert);
	m_alert->release(); // Kenfly 20130204
	//
	XHTipsInfoVo* info = tips->m_myXHInfo;

	{
		//名字 lv.X  
		{
			char str[40];
			sprintf(str, ValuesUtil::Instance()->getString("ZX019").c_str(), info->name.c_str(), info->curlv);
			ccColor3B strColor;
			switch (info->color)
			{
			case 0: strColor = ccc3(192, 192, 192); break;//hui
			case 1: strColor = ccc3(33, 255, 33); break;//green
			case 2: strColor = ccc3(74, 74, 255); break;//blue
			case 3: strColor = ccc3(202, 60, 177); break;//purple
			case 4: strColor = ccc3(254, 147, 39); break;//orange
			case 5: strColor = ccc3(247, 51, 40); break;//red
			default:
				break;
			}

			m_alert->addStr(str, strColor);
		}
		//exp
		{
			int needExp = XHConfManager::Instance()->getXHExpConf(info->color, info->curlv);
			char str[40];
			sprintf(str, ValuesUtil::Instance()->getString("ZX020").c_str(), info->curExp, needExp);	
			m_alert->addStr(str, ccc3(250, 250, 250));
		}
		//属性描述
		{
			char introstr[30];
			char nameeffect[30];
			sprintf(nameeffect, "ZXEFFECT0%02d", info->effecttype);
			if (info->effectval < 1.0f)
				sprintf(introstr, "%s+%d%%", ValuesUtil::Instance()->getString( nameeffect ).c_str(), (int)(info->effectval*100));
			else
				sprintf(introstr, "%s+%d", ValuesUtil::Instance()->getString( nameeffect ).c_str(), (int)(info->effectval));
				
			m_alert->addStr(introstr, ccc3(250, 250, 250));
		}

		//排版显示
		m_alert->show();


		CCSize skillFrameSize = tips->getSrcContentSize();
		//设置本宽高
		this->setContentSize(m_alert->getBgSize());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();


		CCPoint p = coordinate;
		this->setPosition(ccp(p.x,  p.y-m_alert->getBgSize().height*1.5f));	
		//if (p.x <= POSX(960)/2)
		//{//点在左边
		//	this->setPosition(ccp(p.x+POSX(98),  p.y-m_alert->getContentSize().height+POSX(50)));				
		//}
		//else	
		//{//点在右边
		//	this->setPosition(ccp(p.x-m_alert->getBgSize().width,  p.y-m_alert->getContentSize().height+POSX(50)));			
		//}

		//
		if (this->getPosition().y < POSX(55))
		{
			float disy = POSX(55) - this->getPosition().y;
			this->setPosition(ccp(this->getPosition().x, this->getPosition().y+disy));
		}	
		if (this->getPosition().x >= POSX(960)-m_alert->getBgSize().width)
		{
			this->setPosition(ccp(POSX(960)-m_alert->getBgSize().width, this->getPosition().y));
		}	
	}

	return true;
}
