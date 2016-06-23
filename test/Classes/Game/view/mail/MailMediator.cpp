#include "MailMediator.h"
#include "socket/command/s1a/SCMD1A1.h"
#include "socket/command/s1a/SCMD1A3.h"
#include "model/mail/MailProxy.h"
#include "manager/ViewManager.h"
#include "socket/command/s1a/SCMD1AE.h"
#include "socket/command/s1a/SCMD1A7.h"
#include "socket/command/s1a/SCMD1A5.h"
#include "socket/command/s1a/SCMD1A9.h"
#include "control/mail/MailProxyCommand.h"
#include "model/mail/MailConst.h"
#include "socket/command/c1a/CCMD1A0.h"
#include "socket/command/c1a/CCMD1A4.h"
#include "socket/command/c1a/CCMD1A2.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c1a/CCMD1A6.h"
#include "model/backpack/BagProxy.h"
#include "Message.h"
#include "utils/ValuesUtil.h"
#include "socket/command/c1a/CCMD1A8.h"
#include <math.h>
#include "components/MailView.h"
#include "manager/GlobalManage.h"
#include "socket/network/GateServerSocket.h"
#include "socket/command/s1a/SCMD1AB.h"
#include "socket/command/c1a/CCMD1AA.h"
#include "../notify/NotifyManager.h"
#include "../notify/NotifyType.h"
#include "manager/PopEventName.h"

#define LAST_New_MailCount (60)

MailMediator::MailMediator()
{
	_mailView = 0;
	_reqNum = LAST_New_MailCount;
	_curMailType = MailConst::MAIL_TYPE_ALL;
	_unreadNum = 0;

	GameDispatcher::getInstance()->addEventListener( PopEventName::SHOW_UI_EMAIL, this,
		callfuncND_selector(MailMediator::showMailView) );
}

MailMediator::~MailMediator()
{

}

void MailMediator::handleNotification( int M2Vcmd, char* data )
{
	MailProxy * pMailProxy = (MailProxy *)g_pFacade->retrieveProxy(AppFacade_Mail_Proxy);
	switch(M2Vcmd)
	{
	case UPDATE_MAIL_LIST:
		{
			SCMD1A1 * cmd = (SCMD1A1 *)data;
			uint32 mailType = cmd->a_mailType;
			uint32 mailCount = cmd->b_mailCount;
			int startNum = cmd->c_startNum;
			updateMailList(mailType,mailCount, startNum);
		}
		break;
	case SHOW_MAIL_CONTENT:
		{
			SCMD1A3 * cmd = (SCMD1A3 *)data;
			uint32 id = cmd->a_mailId;
			_mailView = ViewManager::getInstance()->_mailView;
			if(_mailView && _mailView->getisPop())
			{
				if (pMailProxy)
				{
					_mailView->resetReadPanel(*(pMailProxy->getMailContent(id)));
				}
			}

			requestMailCount();
		}
		break;
	case SHOW_MAIL_COUNT:
		//获得邮件数量，在游戏场景显示新邮件...
		{
			SCMD1AB * cmd = (SCMD1AB *)data;
			uint16 unreadNum = cmd->a_unreadNum;
			uint16 totalNum = cmd->b_totalNum;
			uint16 playerMailNum = cmd->c_playerMailNum;
			uint16 systemMailNum = cmd->d_systemMailNum;

			_unreadNum = cmd->a_unreadNum;

			switch(_curMailType)
			{
			case MailConst::MAIL_TYPE_ALL:
				_totalPage = totalNum;
				break;
			case MailConst::MAIL_TYPE_SYSTEM:
				_totalPage = systemMailNum;
				break;
			case MailConst::MAIL_TYPE_PLAYER:
				_totalPage = playerMailNum;
				break;
			}
			// request mail
			requestMailList();

			// update mail icon in game view
			// add code here
			updateMailText(unreadNum);

			// show notify
			if (unreadNum > 0)
			{
				if ((_mailView && !_mailView->getisPop())
					|| !_mailView)
				{
					NotifyManager::Instance()->addNotification(NotifyType::NType_Mail);
				}
			}
		}
		break;
	}
}

void MailMediator::sockAttachResult(SCMD1AE * data)
{
	_mailView = ViewManager::getInstance()->_mailView;
		
	if (data->b_result)
	{
		onMailItemClick(data->a_mailId);

		Message::Instance()->show(ValuesUtil::Instance()->getString("MAIL026"),ccc3(12,233,25),1.0f);
	}
	else
	{
		BagProxy * bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
		if (bagProxy->getSpaceGridNum()<=0)
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("EQU001"),ccc3(240,44,22),1);
			return;
		}
		Message::Instance()->show(ValuesUtil::Instance()->getString("MAIL027"),ccc3(233,12,25),1.0f);
	}

}

void MailMediator::sockSendMailResult(SCMD1A7 * data)
{
	int result = data->a_result;

	switch (result)
	{
		case 0://成功
			{
				_mailView = ViewManager::getInstance()->_mailView;
				if(_mailView && _mailView->getisPop())
				{
					MailContentVo contentVo;
					_mailView->resetWritePanel(contentVo);
				}
				Message::Instance()->show(ValuesUtil::Instance()->getString("MAIL029"),ccc3(12,233,25),1.0f);
			}
			break;
		case MailConst::ERR_MAIL_RECVER_NOEXIST: //收件人不存在
			{
				Message::Instance()->show(ValuesUtil::Instance()->getString("MAIL030"),ccc3(233,12,25),1.0f);
			}
			break;
		case MailConst::ERR_MAIL_SEND_FAILED://邮件发送失败
			{
				Message::Instance()->show(ValuesUtil::Instance()->getString("MAIL031"),ccc3(233,12,25),1.0f);
			}
			break;
	}
}

void MailMediator::sockMailDelete(SCMD1A5 * data)
{
	requestMailCount();//重新请求当前页

	MailView * pMailView = ViewManager::getInstance()->_mailView;
	if (pMailView && pMailView->getisPop())
	{
		MailContentVo contentVo;
		pMailView->resetReadPanel(contentVo);
	}
}

void MailMediator::sockMailReceive(SCMD1A9 * data)
{
	requestMailCount();

	Message::Instance()->show(ValuesUtil::Instance()->getString("MAIL038"),ccc3(12,233,25),3.0f);
	/*
	//如果邮箱打开而且当前在第一页，或者邮箱空，立即更新
	_mailView = ViewManager::getInstance()->_mailView;
	if(_mailView && _mailView->getisPop() && (_curPage == 1 || _curPage == 0))
	{
		_curPage = 1; // ?
		requestMailList();
	}
	else if(!_mailView || !_mailView->getisPop())
	{ 
		//外面的场景ui提示，如果邮箱已打开则不提示
// 		if(ViewManager.getInstance().smallMapUI)
// 		{
// 			ViewManager.getInstance().smallMapUI.receiveNewMail();
// 		}
	}
	*/
}

void MailMediator::sockMailList(SCMD1A1 * data)
{
	sendNotification(Facade_Command,AppFacade_Mail_Command,(char *)data, MailProxyCommand::UPDATE_MAIL_LIST);
}

void MailMediator::sockMailContent(SCMD1A3 * data)
{
	sendNotification(Facade_Command,AppFacade_Mail_Command,(char *)data, MailProxyCommand::UPDATE_MAIL_CONTENT);
}

void MailMediator::sockMailCount(SCMD1AB * data)
{
	sendNotification(Facade_Command,AppFacade_Mail_Command,(char *)data, MailProxyCommand::INIT_MAIL_COUNT);
}

void MailMediator::defaultMailList()
{
	/*
	_curPage = 1;
	_curMailType = MailConst::MAIL_TYPE_ALL;
	_mailView = ViewManager::getInstance()->_mailView;
	if (_mailView)
	{
		_mailView->setPageText(0, 0);
	}
	requestMailList();
	*/
}

void MailMediator::onChangePage(CCObject * pSender)
{
	/*
	int num = e.param as int;
	_curPage += num;
	//			_totalPage = Math.ceil(_mailProxy.getMailTypeNum(_curMailType)/6) ;
	if(_curPage<1 || _curPage>_totalPage){
		_curPage -= num;
		return;
	}
	requestMailList();
	*/
}

void MailMediator::onMailTypeClick(uint32 tabType)
{
	/*
	if(_curMailType != tabType)
	{
		_curMailType = tabType;
		_curPage = 1;
		_totalPage = 0;
		_mailView = ViewManager::getInstance()->_mailView;
		if (_mailView)
		{
			_mailView->setPageText(0, 0);
		}
		requestMailList();
	}
	*/
}

void MailMediator::requestMailCount()
{
	CCMD1AA packet1aa;
	GateServerSocket * pSocket = GateServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&packet1aa);
	}
}

void MailMediator::requestMailList()
{
	CCMD1A0 cmdList;
	cmdList.a_mailType = (uint8)_curMailType;
	cmdList.b_startNum = (uint16)0;
	cmdList.c_mailNum = _reqNum;
	if (_totalPage < _reqNum)
	{
		cmdList.c_mailNum = _totalPage;
	}
	GateServerSocket * pSocket = GateServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmdList);
	}
}

void MailMediator::onGetAttachRequest(uint32 mailId)
{
	CCMD1A8 cmd;
	cmd.a_mailId = mailId;
	GateServerSocket * pSocket = GateServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}

void MailMediator::onMailDeleteClick(std::list<uint> mailList)
{
	CCMD1A4 cmdDel;
	cmdDel.a_mailIdList = mailList;
	GateServerSocket * pSocket = GateServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmdDel);
	}
}

void MailMediator::onMailItemClick(uint32 id)
{
	CCMD1A2 cmdContent;
	cmdContent.a_mailId = (uint32)id;
	GateServerSocket * pSocket = GateServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmdContent);
	}
}

void MailMediator::onSendMailClick(std::string recvName,std::string mailTitle,std::string mailContent)
{
	CCMD1A6 cmdSend;
	cmdSend.a_recvName = recvName;
	cmdSend.b_mailTitle = mailTitle;
	cmdSend.c_mailContent = mailContent;
	GateServerSocket * pSocket = GateServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmdSend);
	}
}

void MailMediator::onMailAttachClick(unsigned int attachId)
{
	if(attachId > MailConst::OTHER_ITEM_ID)
	{
		BagProxy * bagProxy = (BagProxy *)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
		if (!bagProxy){return;	}
		if (bagProxy->getSpaceGridNum()<=0)//背包满
		{
			_mailView = ViewManager::getInstance()->_mailView;
			if (_mailView)
			{
				//_mailView->enabledAttach();
			}

			Message::Instance()->show(ValuesUtil::Instance()->getString("EQU001"),ccc3(240,44,22),1);
			return;
		}

		/*
		int totalGrid = bagProxy->_goodsNumber;
		int emptyGrid = 0;
		for (emptyGrid =0;emptyGrid<totalGrid;emptyGrid++)
		{
			if (!bagProxy->_goodsList[emptyGrid]->id)
			{
				break;
			}
		}
		*/
	}

	CCMD1A8 cmdAttach;
	cmdAttach.a_mailId = (uint32)attachId;
	GateServerSocket * pSocket = GateServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmdAttach);
	}
}

//void popHandler(CCObject * pSender);	/*全局消息，当键盘按下时显示或者关闭邮件窗口*/
//void loadMailSkin(CCObject * pSender);

void MailMediator::showMailView()
{
	_mailView = ViewManager::getInstance()->_mailView;
	if(!_mailView)
	{
		_mailView=new MailView();
		if (!_mailView || !_mailView->init())
		{
			return;
		}
		ViewManager::getInstance()->_mailView = _mailView;
	}

	_mailView->setisPop(!_mailView->getisPop());



	_curMailType = MailConst::MAIL_TYPE_ALL;
	requestMailCount();
	_mailView->onAllMailTabClick(0);

	if (_mailView->getisPop())
	{
		// refresh some info
		// add code
		g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
	}
	else
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
		defaultMailList();
		startListener();
	}
}

void MailMediator::startListener()
{

}

//void onCloseView(CCObject * pSender);

void MailMediator::updateMailText(int num)
{
	CCLabelTTF * pNewMailText = ViewManager::getInstance()->_mailText;
	CCSprite * pMailLight = ViewManager::getInstance()->_mailLight;
	if (pNewMailText)
	{
		char path[32] = {0};
        sprintf(path, "%d", num);
		pNewMailText->setString(path);

		if (num > 0)
		{
			pNewMailText->setOpacity(255);
			CCFiniteTimeAction * actionScaleOut = CCScaleTo::actionWithDuration(0.5f,1.3f);
			CCFiniteTimeAction * actionScaleIn = CCScaleTo::actionWithDuration(0.5f,0.8f);
			CCAction* pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(actionScaleIn, actionScaleOut));
			pNewMailText->runAction(pAction);
		}
		else
		{
			pNewMailText->stopAllActions();
			pNewMailText->cleanup();
			pNewMailText->setOpacity(0);
		}
	}

	if (pMailLight)
	{
		if (num > 0)
		{
			CCFiniteTimeAction * actionFadeOut = CCFadeOut::actionWithDuration(0.5f);
			CCFiniteTimeAction * actionFadeIn = actionFadeOut->reverse();
			CCAction* pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(actionFadeIn, actionFadeOut));
			pMailLight->runAction(pAction);
		}
		else
		{
			pMailLight->stopAllActions();
			pMailLight->cleanup();
			pMailLight->setOpacity(0);
		}
	}
	
}

void MailMediator::updateMailList(uint32 mailType, uint32 mailCount, int startNum)
{
	_curMailType = mailType;
	/*
	_totalPage = ceil((float)mailCount/6);
	_curPage = startNum/6 + 1;
	if(_totalPage == 0)
	{
		_curPage = 0;
	}
	else if(_curPage>_totalPage)
	{
		_curPage = 1;
		requestMailList();
		return;
	}
	*/
	_mailView = ViewManager::getInstance()->_mailView;
	if(_mailView && _mailView->getisPop())
	{
		//_mailView->setNoneMailText(_totalPage == 0);
		//_mailView->setPageText(_curPage, _totalPage);

		_mailView->setMailListContent(_curMailType);
		//_mailView->setMailListContent(MailConst::MAIL_TYPE_ALL);
		//_mailView->setMailListContent(MailConst::MAIL_TYPE_SYSTEM);
		//_mailView->setMailListContent(MailConst::MAIL_TYPE_PLAYER);
	}
}