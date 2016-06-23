#pragma once
#include "BaseType.h"
#include "socket/command/s46/SCMD464_466Node.h"

class ZXer;
class ZXView:public LayerNode
{
public:
	enum
	{
		ZXViewTAG_SLOT = 1000,

		ZXViewTAG_BAG = 2000,

		ZXViewTAG_ZXEr = 3000,

		ZXViewTAG_ZXSCORE = 4000,

		ZXViewTAG_ZXFREECOUNT = 4001,
	};
	
	enum
	{
		ZXViewBankTAG_name = 10,
		ZXViewBankTAG_pic = 11,
	};

	ZXView();
	~ZXView();

	bool init();
	void clickClose(CCObject* pSender);
	void clickBackXH(CCObject* pSender);
	void clickOneKeyZX(CCObject* pSender);
	void clickOneKeyCollect(CCObject* pSender);
	void clickOneKeySell(CCObject* pSender);
	void clickDuiHuan(CCObject* pSender);
	void clickBankXH(CCObject* pSender);
	void updateZXerState(int state);
	void buildBankXH(std::list<SCMD464_465Node>& a_XHList);
	void updateScore(int32 val);
	void updateZXerFreeCountToday(uint32 val);
public:
	LayerNode* _pContainer;
	LayerNode* m_pBank[12];
	SCMD464_465Node m_iXHWorldID[12];
	ZXer* m_pZXer[5];
	bool m_bFirstOpenXH;

};