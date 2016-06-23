#include "UpdatePopularityAction.h"
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

UpdatePopularityAction::UpdatePopularityAction()
{
	_dispatcher = 0;
	_dispatcher = GameDispatcher::getInstance();

	_roleUI = 0;
	_roleManage = 0;
}

bool UpdatePopularityAction::init(char* param,RoleUI* roleUI)
{
//	_param = param;

	_roleUI = roleUI;
	_roleManage = RoleManage::Instance();

	SCMD18F* thisparam = (SCMD18F*)param;
	a_newvalue = thisparam->a_newvalue;
	b_diffvalue = thisparam->b_diffvalue;
	c_isShow = thisparam->c_isShow;

	return true;
}

UpdatePopularityAction::~UpdatePopularityAction()
{

}

void UpdatePopularityAction::doAction()
{
	if(b_diffvalue > 0 && c_isShow>0)
	{
		char out[100];
		sprintf(out, ValuesUtil::Instance()->getString( "ADD0006" ).c_str(), b_diffvalue);
		LangManager::msgStr(out);
	}
	else if(b_diffvalue<0 && c_isShow>0){
		char out[100];
		sprintf(out, ValuesUtil::Instance()->getString( "ADD0007" ).c_str(), abs(b_diffvalue));
		LangManager::msgStr(out);
	}	
	
	_roleManage->_accountInfo.popularity(a_newvalue); 
	_roleUI->setPopularity(_roleManage->_accountInfo.popularity());
}
