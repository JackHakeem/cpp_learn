#ifndef _ROLEUI_H_
#define _ROLEUI_H_
#include "LayerNode.h"
#include "socket/command/s21/SCMD21F.h"

USING_NS_CC;

#define MAX_ENERGY (100)

class RoleUI : public LayerNode
{
public:
	RoleUI();
	RoleUI(std::string name,int roleLev,int crystalLev,int maxHP,int hp,int energy,int vipLev,int carrer,
		int gold, int silver, int silverLim, int practice, int popularity);
	virtual ~RoleUI();
public:
	void initView();
	void setTips();
	void setHead(int carrer);
	void setName(std::string name);
	void setRoleLev(int roleLev);
	void setCrystalLev(int crystalLev);
	void setVigourBuffCount(int vigourBuffCount, int maxVigourBuffCount);
	void setEnergy(int energy,int maxEnergy = MAX_ENERGY);
	void setVipLev(int vipLev);
	bool isAddBtnShow(int vipLev);
	void setGold(int gold);
	void setSilver(int num,int numLim);
	void setPrictice(int practice);
	void setPopularity(int popularity);
	void initEvent();
	void setHP(int HP,int maxHP);
	void onAddHandler(SCMD21F * cmd,int type);
	void onAddEnergyAlert(SCMD21F * cmd);

	//Doyang 20120731
	void onVipMenuClick(CCObject *pSender);
	ccColor3B getVipLabelColor(int vipLev);

public:
	void clickBuyGold(CCObject * pSender);
	void clickBuyEnergy(CCObject * pSender);
	void clickBuyEnergyConfirm(CCObject * pSender);
	void clickCancel(CCObject * pSender);
	void onAddEnergy(CCObject * pSender);
	void clickVigourBuff(CCObject * pSender);
	void clickGongExpBuff(CCObject * pSender);
public:
	void runMyAction(CCNode * pNode , CCAction * pAction);
	void stopMyAction(CCNode * pNode);
	CCAction * getMyAction();

public:
	enum
	{
		Z_BG = 0,
		Z_ITEM = 10,
	};
	enum
	{
		TAG_BG = 0,
		TAG_BTN = 1,
		TAG_HEAD = 10,
		TAG_LEV,
		TAG_GOLD,
		TAG_SLIVER,
		TAG_PRACTICE,
		TAG_ENERGY,
		TAG_ENERGY_PROGRESS,
	};
	CCSize _roleUISzie;
	int _type;
	SCMD21F _scmd21fCopy;
	bool _isTrialVip;

public:

protected:
private:

};

#endif