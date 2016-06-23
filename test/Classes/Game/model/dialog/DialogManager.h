#ifndef _DIALOGMANAGER_H
#define _DIALOGMANAGER_H

#include "vo/DialogueVo.h"
#include "utils/Singleton.h"
//using namespace util;

class DialogManager : public Singleton<DialogManager>
{
public:
	DialogManager();
	~DialogManager();

public:
	DialogueVo* allocVo() { return new DialogueVo(); };

	void setDialogs( DialogueVo * pDialogueVo );
	DialogueVo * getDialogs( int iNpcID );

private:
	std::map<int, DialogueVo *> _dialogDic;
};

typedef std::map<int, DialogueVo *>::iterator DIALOGVOITER;

#endif