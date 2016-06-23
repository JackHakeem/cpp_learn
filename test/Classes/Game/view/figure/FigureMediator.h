#ifndef HLQS_FigureMediator_H_
#define HLQS_FigureMediator_H_
#include "view/BaseMediator.h"
#include "view/figure/components/FigureMainView.h"

USING_NS_CC;
class FigureMediator: public BaseMediator
{
public:
	FigureMediator();
	virtual void handleNotification(int M2Vcmd, char* data);
	void showEquipInfo();
	void openFigureView();
	void openView();
	void updateEquip(char* data);
	void putOnEquipment(int typeId, int sitGrid);
	void updateSkillTip(char* data);
	void updateTip(char* data);
	void updateAttributeView(char* data);
	void updateWashView(char* data);
	void closeFigureView();
	void sockEquipInfo(char* cmd);
	void sockEquipItemUpdate(char* cmd);
	void sockEqipSkillUpdate(char* cmd);
	void sockSaveWashValue(char* cmd);
	void sockRefreshWashValue(char* cmd);
	void sockRebornResult(char* cmd);
	void sockPriceResult(char* cmd);
	void sockUpdateExp(char* cmd);
	void sockMercSkillExchange(char* cmd);
	void sockBuyIdentifyGrid(char* cmd);
	void sockSaveIdentifyValue(char* cmd);
	void sockMercIdentifyInfo(char* cmd);
	void attPointChange(char* cmd);
	int getType();

public:
	void sendOnClotheRequest(uint32 figureID,uint8 sitGrid);
	void sendDownClotheRequest(uint32 figureID);
	void sendDownClotheRequest(uint32 figureID,uint8 sitGrid,uint8 bagGrid);
	void sendRebornRequest(uint32 figureID);
	void sendWashRequest(uint32 figureID,uint8 type,uint8 useItem);
	void sendSaveRequest(uint32 figureID);
	void sendPriceRequest(uint32 type);
	void sendMercIdentifyInfoRequest();
	void sendIdentifyRequest(int mechID , int type);
	void sendSaveIdentifyRequest();
	void sendBuyGridRequest();

	void figurePopHandle(CCNode *pNode, void *data);
	void openFigure( CCNode *pNode, void *data );
public:
	enum 
	{
		UPDATE_EQUIP_INFO = 0,
		EQUIP_UPDATE,
		PUT_ON_EQUIP,
		EQUIPMENT_ITEM_TIP_UPDATE,
		FIGURE_SKILL_CHANGE,
		SKILL_ITEM_TIP_UPDATE,
		EXCHANGE_SKILL,
		REFRESH_WASH_VALUE,
		SAVE_WASH_VALUE,
		OTHER_ITEM_TIP_UPDATE,
	};

	FigureMainView* _figureMainView;
};

#endif