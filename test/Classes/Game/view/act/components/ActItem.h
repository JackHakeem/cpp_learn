#pragma once

#include "BaseType.h"
#include "socket/command/s38/SCMD38FNode.h"

class CCUIBackground;

class ActItem:public LayerNode
{
public:
	enum
	{
		ActItemZ_bg1,
	};

	enum
	{
		ActItemTAG_bg1,
	};
public:
	ActItem();
	~ActItem();

	bool init(SCMD38FNode node);
	virtual void visit();
	void setClipSize(CCSize size);
public:
	CCUIBackground* _bg1;
	CCSize _maxSize;
	CCSize _minSize;
	CC_SYNTHESIZE(bool , isExpand , IsExpand);
};