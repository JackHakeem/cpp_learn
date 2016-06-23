#pragma once

#include "BaseType.h"
#include "utils/Singleton.h"

#define CETEXMEMSIZE 30

class ceView:public LayerNode, public Singleton<ceView>
{
public:
	ceView();
	~ceView();

	bool init();
	void update(float dt);
	void insertNode(char* str);
	void clickShow(CCObject* pSender);
	void cleanStrs();
public:
	CCLabelTTF* m_pTexMem[CETEXMEMSIZE];
	cocos2d::CCLayerColor* pbg;
	int progress;
};