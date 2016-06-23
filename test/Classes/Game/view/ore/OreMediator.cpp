#include "OreMediator.h"
#include "components/OreView.h"
//#include "socket/command/c40/CCMD40C.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "manager/ViewManager.h"
#include "socket/command/c43/CCMD430.h"
#include "manager/GlobalManage.h"


OreMediator::OreMediator() : _oreNum(1)
{
	m_pOreView = 0;
}

OreMediator::~OreMediator()
{}

void OreMediator::OpenView()
{
	if (m_pOreView)
	{
		m_pOreView->release();
		m_pOreView = 0;
	}

	m_pOreView = new OreView();
	m_pOreView->init();
	ViewManager::getInstance()->oreView = m_pOreView;

	m_pOreView->setisPop(!m_pOreView->getisPop());
	m_pOreView->release();


	//
	CCMD430 cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );
}

void OreMediator::UpdateOre(uint32 stoneNum, uint32 oreNum, uint32 buyCount)
{
	if (m_pOreView)
	{
		m_pOreView->UpdateOre(stoneNum, oreNum, buyCount);
	}
	
	// update 
	_oreNum = oreNum;
}

void OreMediator::HandleResponse(uint32 flag)
{
	if (m_pOreView)
	{
		m_pOreView->HandleResponse(flag);
	}	
}

void OreMediator::UpdatePlantProgress(uint32 progress)
{
	if (m_pOreView)
	{
		m_pOreView->UpdatePlantProgress(progress);
	}	
}

int OreMediator::getOreNumber()
{
	return _oreNum;
}