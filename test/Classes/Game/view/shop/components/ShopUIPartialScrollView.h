#ifndef _SHOPUIPARTIALSCROLLVIEW_H_
#define _SHOPUIPARTIALSCROLLVIEW_H_

#include "CCUIPartialScrollView.h"

class ShopUIPartialScrollView: public CCUIPartialScrollView
{
public:
	virtual ~ShopUIPartialScrollView(){};

	ShopUIPartialScrollView(const CCRect& mRect);
    static ShopUIPartialScrollView* bagScrollViewWithCCRect(const CCRect& mRect);

public:

};

#endif