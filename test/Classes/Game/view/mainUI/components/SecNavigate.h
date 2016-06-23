#ifndef HLQS_SecNavigate_H_
#define HLQS_SecNavigate_H_
#include "LayerNode.h"
#include "CCUIBackground.h"

class ChatBtnMenu;
class SecNavigate: public LayerNode
{
public:
	SecNavigate();
	void initView();
	
	void popUIHandler330(CCObject* pSender);
	void popUIHandler320(CCObject* pSender);
	void popUIHandler327Levy( CCObject* pSender );
	void popUIHandler331(CCObject* pSender);
	void popUIHandler327( CCObject* pSender );
	void popUIHandlerArenaOpen( CCObject* pSender );
	void popUIHandlerChatOpen( CCObject* pSender );
	void popUIHandlerFirstPurchaseOpen( CCObject* pSender );
	CCNode *getNewHandItem(int btnId);
	void addButton(int type, int sitNum, bool isTween);
	void addButtonAward();
	void popUIHandlerAward(CCObject* obj);
	void removeBtnAward();
	void popUIHandlerAct(CCObject* pSender);
	//Begin chenjian 20121011
    void popUIHandlerReportOpen(CCObject* pSender);
	void setIsReportBtnVisible(bool value);
	//End chenjian 20101011

	void popUIHandlerDailyTaskEx(CCObject* pSender);
	void setIsShowCenterTopItems(bool var);

	void popUIHandlerLoginReward(CCObject* pSender);

	void popUIHandlerOre(CCObject* pSender);
	
	void addButtonByLev(int lev);
	void fadeDailyTaskExBtn(bool fade);
	void hideBtnAward();
	void removeButton(int tag);
	void popUIHandlerTrader( CCObject* pSender );
public:

	enum
	{
		TAG_DAILY_TASK_EX = 320,
		TAG_FIRST_PURCASE = 322,
		TAG_LOGIN_REWARD = 323,
		TAG_ENTRANCE = 324,
		TAG_EGG = 325,
		TAG_LEVY = 327,
		TAG_GOLD_LEVY = 328,
		TAG_ACT = 349,
		TAG_GONG = 331,
		TAG_TRADER = 339,
		TAG_MAPAWARD = 1000,
	};


	CCMenu *_btnConvey;
	CCMenu *_btnReport;
	CCMenu *_btnTrader;
	ChatBtnMenu* _btnChatBtnMenu;

	//Doyang 20120719
	std::list<int> _buttonIds;
};
#endif
