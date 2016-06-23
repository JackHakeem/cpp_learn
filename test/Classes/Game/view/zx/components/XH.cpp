#include "XH.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "CCUIBackground.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "Confirm.h"
#include "socket/network/GameServerSocket.h"
#include "manager/ViewManager.h"
#include "model/zx/XHConfManager.h"
#include "utils/TipHelps.h"

XH::XH()
{
	m_iXHType = 0;
	myTip = 0;
}

XH::~XH()
{
	if (myTip)
	{
		delete myTip;
		myTip = 0;
	}	
}

bool XH::init(int index, uint8 lv, uint32 curexp)
{	
	if (lv == 0)
		return false;

	if (!LayerNode::init())
	{
		return false;
	}


	m_iXHType = index;
	m_iLv = lv;
	m_iCurExp = curexp;

	XHConfVo* conf = XHConfManager::Instance()->getXHConf(index);
	if (!conf)
		return false;

	{
		char picpath[50];
		sprintf(picpath, "assets/ui/zx/xh%02d.png", index);
		SpriteNode* pPic = new SpriteNode();
		pPic->initWithFile(picpath);
		this->addChild(pPic, 0, 0);
		pPic->release();	
	}

	{
		//name
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(conf->name.c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(20));
		pLabel->setPosition(ccp(POSX(0), POSX(-10)));
		this->addChild(pLabel, 0, 1);

		switch (conf->color)
		{
		case 0: pLabel->setColor(ccc3(192, 192, 192)); break;//hui
		case 1: pLabel->setColor(ccc3(33, 255, 33)); break;//green
		case 2: pLabel->setColor(ccc3(74, 74, 255)); break;//blue
		case 3: pLabel->setColor(ccc3(202, 60, 177)); break;//purple
		case 4: pLabel->setColor(ccc3(254, 147, 39)); break;//orange
		case 5: pLabel->setColor(ccc3(247, 51, 40)); break;//red
		default:
			break;
		}
	}
	//
	{
		//lv
		char str[30];
		sprintf(str, "Lv.%d", m_iLv);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(str, CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(20));
		pLabel->setPosition(ccp(POSX(0), POSX(-30)));
		this->addChild(pLabel, 0, 1);

		switch (conf->color)
		{
		case 0: pLabel->setColor(ccc3(192, 192, 192)); break;//hui
		case 1: pLabel->setColor(ccc3(33, 255, 33)); break;//green
		case 2: pLabel->setColor(ccc3(74, 74, 255)); break;//blue
		case 3: pLabel->setColor(ccc3(202, 60, 177)); break;//purple
		case 4: pLabel->setColor(ccc3(254, 147, 39)); break;//orange
		case 5: pLabel->setColor(ccc3(247, 51, 40)); break;//red
		default:
			break;
		}
	}
	//ÉèÖÃTIPS

	if (!myTip)
	{
		myTip = new TipHelps();
	}
	myTip->init(false, 0, false, true);
	myTip->setToolTips(this, this);

	XHTipsInfoVo* info = new XHTipsInfoVo();
	info->color = conf->color;
	info->name = conf->name;
	info->curlv = m_iLv;
	info->curExp = m_iCurExp;
	info->effecttype = conf->effecttype;
	info->effectval = conf->lv[m_iLv-1];
	this->m_myXHInfo = info;

	return true;
}