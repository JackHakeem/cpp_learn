#include "UpdatePraceticeAction.h"
#include "manager/PopManage.h"
#include "events/GameDispatcher.h"


#include "socket/network/GameServerSocket.h"
#include "model/player/RoleManage.h"

#include "manager/ViewManager.h"
#include "manager/LangManager.h"
#include "model/player/RoleManage.h"
#include "view/mainUI/components/RoleUI.h"
#include "manager/LangManager.h"
#include "utils/ValuesUtil.h"

UpdatePraceticeAction::UpdatePraceticeAction()
{
	_dispatcher = 0;
	_dispatcher = GameDispatcher::getInstance();

	_roleUI = 0;
	_roleManage = 0;
}

bool UpdatePraceticeAction::init(char* param,RoleUI* roleUI)
{
//	_param = param;

	_roleUI = roleUI;
	_roleManage = RoleManage::Instance();

	SCMD18E* thisparam = (SCMD18E*)param;
	a_newvalue = thisparam->a_newvalue;
	b_diffvalue = thisparam->b_diffvalue;
	c_isShow = thisparam->c_isShow;

	return true;
}

UpdatePraceticeAction::~UpdatePraceticeAction()
{

}

void UpdatePraceticeAction::doAction()
{
	if(b_diffvalue > 0 && c_isShow>0)
	{
		char out[100];
		sprintf(out, ValuesUtil::Instance()->getString( "ADD0003" ).c_str(), b_diffvalue);
		LangManager::msgStr(out);
	}
	else if(b_diffvalue<0 && c_isShow>0){
		char out[100];
		sprintf(out, ValuesUtil::Instance()->getString( "ADD0008" ).c_str(), abs(b_diffvalue));
		LangManager::msgStr(out);
	}	
	
	_roleManage->_accountInfo.practice(a_newvalue); 
	_roleUI->setPrictice(_roleManage->_accountInfo.practice());
}
