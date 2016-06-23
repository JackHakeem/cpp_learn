#ifndef _SMALLMAPUI_H_
#define _SMALLMAPUI_H_

#include "BaseType.h"

class SmallMapUI : public LayerNode
{
public:
	SmallMapUI();
	~SmallMapUI();
	void initWithParam(std::string name, CCPoint location);
	void configUI(std::string name, CCPoint location);

	void townMapClick(CCObject* pSender);
	CCNode *getNewHandItem(int btnId);
};

#endif