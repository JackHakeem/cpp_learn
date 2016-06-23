#ifndef _ActView_H_
#define _ActView_H_

#include "PopContainer.h"
#include "BaseType.h"

class HotList;
class ActView : public PopContainer
{
public:
	enum
	{

	};
	enum
	{
		TAG_HotView,
		TAG_ActView,
	};

public:
	ActView();
	~ActView();

public: 

	bool init();
public:
	//void initView();
	virtual void removeDataObjectChild();

public:
	LayerNode* _container;
	HotList* _pHot;
	HotList* _pAct;
};

#endif