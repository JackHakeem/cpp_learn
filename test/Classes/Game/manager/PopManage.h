#ifndef _POPMANAGE_H_
#define _POPMANAGE_H_

#include "BaseType.h"
#include "PopEventName.h"

class WindowLayer;
class PopContainer;
class PopUIBg;
class PopManage
{
public:


	PopManage();
	~PopManage(){}
public:
	void setlayer(WindowLayer* pLayer);
	void popUp(PopContainer* popCon);
	void popBack(PopContainer* popCon);
	void adjustCordinate();
	bool isViewPop(int32 key);
	int32 getCurPopNum();
	void handleBackHandler();
	void handleCloseHandler();
	// LH20121026
	void setIsNeedClose(int index ,  bool var);
	bool hasPopedConteainer();


	CCNode * getBtnX();
public:
	WindowLayer* layer;

	PopContainer* popList[PopEventName::MAX_COUNT];//Popup window
	int8 withList[PopEventName::MAX_COUNT][10];
	int8 withOpenList[PopEventName::MAX_COUNT][10];
	int8 withBackList[PopEventName::MAX_COUNT][10];
	static int32 g_tagflag;
	PopUIBg* _PopUIBg;

	

	
};

extern PopManage* g_pPopManage;
/*
		
		public function popUp(popCon:PopContainer):void
*/
#endif 