#ifndef _BAGUIPARTIALSCROLLVIEW_H_
#define _BAGUIPARTIALSCROLLVIEW_H_

#include "CCUIPartialScrollView.h"

//BagUIPartialScrollView * 

class BagUIPartialScrollView: public CCUIPartialScrollView
{
public:
	virtual ~BagUIPartialScrollView(){};

	BagUIPartialScrollView(const CCRect& mRect);
    static BagUIPartialScrollView* bagScrollViewWithCCRect(const CCRect& mRect);

public:

};

#endif