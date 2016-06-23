#pragma once

#include "BaseType.h"

class TextFieldTTF;
class GameDispatcher;
class NumSelectBox:public LayerNode
{
public:
	NumSelectBox();
	~NumSelectBox();

	bool init();
	void maxHandler(CCObject* pSender);
	void pickHandler(CCObject* pSender);

	void close(CCObject* pSender);
	void setInfo(int eggId, std::string name, int num);


public:
	CCLabelTTF* _txtItemNum;
	int _eggId;		//蛋蛋ID
	std::string _eggName;	//蛋蛋名字
	int _num;		//要拾取的数量
	int _total;		//蛋蛋总数
	TextFieldTTF* _txtNum;
	GameDispatcher* _dispatcher;
};