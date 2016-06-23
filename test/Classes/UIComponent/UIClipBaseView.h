//************************************************************************
// ClipBaseView component, only show the view with it's content size on window.
// By Yang Liangjie
//************************************************************************

#ifndef _UI_CLIP_BASE_VIEW_H_
#define _UI_CLIP_BASE_VIEW_H_

#include "BaseType.h"
#include "cocos2d.h"

class UIClipBaseView : public LayerNode
{
public:
	virtual void visit();
};
#endif