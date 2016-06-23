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
	/** �Ե���idΪ����������Ʒ���� */
	std::map<int, GoodsItem*> _eggDic;
	/** ���浱ǰ����ĵ��� */
	int _curEggId;
	/** һ��60����Ʒ���� */
	int totalGrid;
	/** һ��5ҳ */
	int totalPage;

	int _curPage;

	LayerNode* _goodsContainer;	// ��Ʒ��������
	GameDispatcher* _dispatcher;
};