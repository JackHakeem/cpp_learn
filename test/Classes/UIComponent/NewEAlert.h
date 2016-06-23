#pragma once

#include "BaseType.h"

class GoodsBasic;
class NewEAlert:public LayerNode
{
public:
	NewEAlert();
	~NewEAlert();

	static void show(std::string title="", 
	std::string content="", 
	std::string btnName="", 
	std::string pic_url="", 
	int pic_sit=0, 
	CCObject* target=0, SEL_MenuHandler fun=0,
	char*	param=0, 
	bool isModel=false);

	static void showAutoEquip(GoodsBasic* goodBasic, int mercId, int sitGrid);

	void clickClose(CCObject* pSender);

};