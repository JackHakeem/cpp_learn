#ifndef _BANKITEMINFOSHOW_H_
#define _BANKITEMINFOSHOW_H_

#include "BaseType.h"
#include "Alert.h"

class BankGoods;
class BankView;

class BankItemInfoShow: public LayerNode
{
public:
	BankItemInfoShow();
	bool initWithBankGoods(BankGoods* pBankGoods, BankView* bankView);

	void tick(ccTime dt);

	void clickhandle(CCObject* pSender);

public:
	float dieCount;
	Alert* m_alert;
	BankGoods* m_pBankGoods;
};

#endif
