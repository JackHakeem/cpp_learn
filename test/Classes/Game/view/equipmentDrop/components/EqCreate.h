#pragma once

#include "UIListView/CCUIListView.h"

class EqCreate:public CCUIListView
{
public:
	static EqCreate* listViewWithCCRect(const CCRect& mRect, bool isHorizontal);
};