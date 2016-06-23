#ifndef _POPCONTAINER_H_
#define _POPCONTAINER_H_

#include "BaseType.h"
#include "SpriteNode.h"

class WindowLayer;

class PopContainer:public LayerNode
{
public:
	enum
	{
		NeedBg_NO = 0,
		NeedBg_YES = 1,
	};
	enum
	{
		CLOSE_CONTAINER = 1011,
		OPEN_CONTAINER,
		HELP_CONTENT
	};
	PopContainer();
	virtual ~PopContainer(){};
	virtual void popUp(WindowLayer* layer);
	
	virtual void clickCloseHandler(CCObject* pSender);
	virtual void close();
	virtual void reinit(){};

	CC_PROPERTY(bool, _isPop, isPop)

	virtual void removeDataObjectChild(){};

	virtual void backHandlerByCurrentUIStage(){;}

	virtual int32 getSelfTag() {return 0;}

	virtual	bool handleBack(){return false;}

	virtual void changeStage(int32 stage){}

	CC_PROPERTY(int32, _NeedBg, NeedBg)
	CC_PROPERTY(CCSize, _popContentSize, PopContentSize)
	CC_PROPERTY(int32, _UIStage, UIStage)

	// LH20121026
	CC_SYNTHESIZE(bool, _isNeedClose, IsNeedClose)

public:
	int32	key;
};

#endif