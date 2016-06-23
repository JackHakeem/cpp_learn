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
	int _eggId;		//����ID
	std::string _eggName;	//��������
	int _num;		//Ҫʰȡ������
	int _total;		//��������
	TextFieldTTF* _txtNum;
	GameDispatcher* _dispatcher;
};