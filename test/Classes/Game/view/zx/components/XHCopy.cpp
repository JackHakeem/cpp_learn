#include "XHCopy.h"
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
#include "XH.h"

XHCopy::XHCopy()
{
	m_pOrg = 0;
}

XHCopy::~XHCopy()
{}

bool XHCopy::init(XH* org)
{
	if (!LayerNode::init() || !org)
	{
		return false;
	}

	m_pOrg = org;

	XHConfVo* conf = XHConfManager::Instance()->getXHConf(m_pOrg->m_iXHType);
	if (!conf)
		return false;

	{
		char picpath[50];
		sprintf(picpath, "assets/ui/zx/xh%02d.png", m_pOrg->m_iXHType);
		SpriteNode* pPic = new SpriteNode();
		pPic->initWithFile(picpath);
		this->addChild(pPic, 0, 0);
		pPic->release();	
		pPic->setScale(1.4f);
	}

	return true;
}