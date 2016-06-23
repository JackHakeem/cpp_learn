#ifndef _CC_UI_TASK_PANEL_ITEM_H_
#define _CC_UI_TASK_PANEL_ITEM_H_
#include "cocos2d.h"
#include "CCLayer.h"
#include "../LayerNode.h"
#include "../CCUIBackground.h"

class CCUITaskPanelItem : public LayerNode
{
public:
	static CCUITaskPanelItem* initWithWidthHeight(float width, float height,
		float clipWidth, float clipHeight,
		const float parentMinClipHeight, const float parentMaxClipHeight);
	virtual void visit();
	virtual bool init();

	void setClipSize(CCSize clipSize);
	CCSize getClipSize();
	bool isExpand();
	void endExpanded();
	void endCollapsed();
	void setIsFocus(bool isFocus);
protected:
	CC_SYNTHESIZE(float, minHeight, MinHeight);
	CC_SYNTHESIZE(float, maxHeight, MaxHeight);
	CC_SYNTHESIZE(CCPoint, parentWorldSpaceBottomLeftPoint, ParentWorldSpaceBottomLeftPoint)
private:
	CCUITaskPanelItem(float expandedWidth, float expandedHeight, float collapsedWidth, float collapsedHeight,
		const float parentMinClipHeight, const float parentMaxClipHeight);
	
	bool _isFocus;
	CCUIBackground *_frameLayer;
	CCSize _clipSize;
	float _parentMinClipHeight, _parentMaxClipHeight;

	float _clipX, _clipY, _clipHeight, _clipWidth, _topY;
	bool _isExpanded;
};
#endif