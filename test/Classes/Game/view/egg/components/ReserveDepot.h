#pragma once

#include "BaseType.h"

class GoodsItem;
class GameDispatcher;

class ReserveDepot:public LayerNode
{
public:
	ReserveDepot();
	~ReserveDepot();

	bool init();
	void updateEggNum(int num);
	void buildList(int page=1);
	void updatePage(int page);
	void close(CCObject* pSender);
	void getAllHandler(CCObject* pSender);
	void prevHandler(CCObject* pSender);
	void nextHandler(CCObject* pSender);
public:
	CCLabelTTF* _txtNum;
	CCLabelTTF* _pageText;
	/** 以蛋蛋id为键，保存物品格子 */
	std::map<int, GoodsItem*> _eggDic;
	/** 保存当前点击的蛋蛋 */
	int _curEggId;
	/** 一共60个物品格子 */
	int totalGrid;
	/** 一共5页 */
	int totalPage;

	int _curPage;

	LayerNode* _goodsContainer;	// 物品格子容器
	GameDispatcher* _dispatcher;
};