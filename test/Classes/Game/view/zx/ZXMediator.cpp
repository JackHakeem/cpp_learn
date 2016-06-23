#include "ZXMediator.h"
#include "components/XHView.h"
#include "components/ZXView.h"
#include "components/ZXDuiView.h"
#include "socket/command/c46/CCMD468.h"
#include "socket/network/GameServerSocket.h"

ZXMediator::ZXMediator()
{
	m_pXHView = 0;
	m_iScore = 0;
}

ZXMediator::~ZXMediator()
{}


void ZXMediator::OpenXHView()
{
	m_pXHView = new XHView();
	m_pXHView->init();
	m_pXHView->setisPop(!m_pXHView->getisPop());
	m_pXHView->release();

	//
	CCMD468 cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );
}
	
void ZXMediator::updateScore(uint32 score)
{
	m_iScore = score;

	ZXView* pZXView = (ZXView*)LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ZX);
	if (pZXView)
	{
		pZXView->updateScore(m_iScore);
	}	
	
	ZXDuiView* pZXDuiView = (ZXDuiView*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_ZXDuiView);
	if (pZXDuiView)
	{
		pZXDuiView->updateScore(m_iScore);
	}
}