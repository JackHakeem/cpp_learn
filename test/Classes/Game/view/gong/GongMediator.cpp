#include "GongMediator.h"
#include "components/GongRankingView.h"
#include "components/GongMBView.h"
#include "socket/command/c44/CCMD445.h"
#include "socket/command/s44/SCMD446.h"
#include "socket/command/c44/CCMD449.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/s44/SCMD44A.h"

GongMediator::GongMediator()
{
	m_pRankingView = 0;
	m_pMBView = 0;
}
	
void GongMediator::openRankingView()
{
	if (m_pRankingView)
	{
		m_pRankingView->release();
		m_pRankingView = 0;
	}

	m_pRankingView = new GongRankingView();
	m_pRankingView->init();

	m_pRankingView->setisPop(!m_pRankingView->getisPop());
	m_pRankingView->release();

	//
	CCMD445 cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );
}

void GongMediator::updateRankingView(SCMD446* packet)
{
	if (!packet)
		return;

	m_pRankingView->update(packet->a_wave, packet->b_ranking);
}

void GongMediator::openMBView()
{
	if (m_pMBView && m_pMBView->getParent())
	{
		m_pMBView->setisPop(!m_pMBView->getisPop());
		m_pMBView = 0;
	}
	else if (m_pMBView)
	{
		m_pMBView->release();
		m_pMBView = 0;
	}

	m_pMBView = new GongMBView();
	m_pMBView->init();

	m_pMBView->setisPop(!m_pMBView->getisPop());
	if (m_pMBView->retainCount() > 1)
		m_pMBView->release();

	//
	CCMD449 cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );	
}

void GongMediator::updateMBView(SCMD44A* packet)
{
	if (!packet)
		return;

	m_pMBView->update(packet->a_heroname, packet->e_names);	
}
