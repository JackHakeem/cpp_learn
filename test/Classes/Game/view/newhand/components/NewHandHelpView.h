#ifndef _NEWHAND_HELP_VIEW_H_
#define _NEWHAND_HELP_VIEW_H_

#include "cocos2d.h"
#include "BaseType.h"
#include "utils/Singleton.h"

class HelpScriptVo;

class NewHandHelpView : public CCLayer , public Singleton<NewHandHelpView>
{
public:
	NewHandHelpView();
	~NewHandHelpView();

	virtual bool init();

	void loadItems();

	void addButtons();
	void setBodyIcon(std::string strPath);
	void setTitle(std::string strTitle);
	void setContent(std::string strContent);
	void setBtnText(std::string strBtnTxt);

	HelpScriptVo * getHelpScript(int var);
	void showOKButton(bool var);
	void showPreNextButton(bool pre, bool next);
	void showPanel(HelpScriptVo * pHelpVo);
	void doAction(HelpScriptVo * pHelpVo);

	void resetView(int id);
	void initView();
	void onCloseView(CCObject * pSender);
	void onPreView(CCObject * pSender);
	void onNextView(CCObject * pSender);

	void onDo(CCObject * pSender);

	void resetView(CCNode * pNode , void * pData);

public:
	CCSize _winSize;
	int _curId;
	enum
	{
		TAG_BodyIcon = 10,
		TAG_Title,
		TAG_Content,
		TAG_Btn,
		TAG_Btn_Text,
		TAG_Btn_Pre,
		TAG_Btn_Next,
	};
};
#endif
