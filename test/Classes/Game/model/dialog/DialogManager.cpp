#include "DialogManager.h"
#include "../player/RoleManage.h"

DialogManager::DialogManager()
{

}

DialogManager::~DialogManager()
{
	DIALOGVOITER it = _dialogDic.begin();

	while ( it != _dialogDic.end() )
	{
		CC_SAFE_DELETE( it->second );
		it++;
	}
}

void DialogManager::setDialogs( DialogueVo * pDialogueVo )
{
	if (!pDialogueVo) return;

	_dialogDic.insert(  make_pair( pDialogueVo->id, pDialogueVo )  );
	return;
}

DialogueVo * DialogManager::getDialogs( int iNpcID )	// dialogID
{
	DIALOGVOITER it = _dialogDic.find( iNpcID );

	if ( it != _dialogDic.end() )
	{
		std::string roleName = RoleManage::Instance()->accountInfo()->name;
		std::string strContent = it->second->content;
		char path[512] = {0};
		sprintf(path,strContent.c_str(),roleName.c_str());
		it->second->content = path;
		/*if (strContent.find("%s"))
		{
		char path[256] = {0};
		sprintf(path,strContent.c_str(),roleName.c_str());
		it->second->content = path;
		}*/
		return it->second;
	}
	return NULL;
}
