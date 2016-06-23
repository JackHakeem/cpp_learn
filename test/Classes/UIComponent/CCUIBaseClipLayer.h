#ifndef _CC_UI_BASE_CLIP_LAYER_H_
#define _CC_UI_BASE_CLIP_LAYER_H_
#include "LayerNode.h"
#include "cocos2d.h"

USING_NS_CC;

class CCUIBaseClipLayer : public LayerNode
{
public:
	static CCUIBaseClipLayer *initWithRect(const cocos2d::CCRect &rect);

	virtual bool init();
	virtual void visit();

protected:
	CC_SYNTHESIZE(cocos2d::CCRect, clipLayerRect, ClipLayerRect);
private:
	CCUIBaseClipLayer(const cocos2d::CCRect &rect);

};
#endif