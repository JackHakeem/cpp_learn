#ifndef _BAGUIPARTIALSCROLLVIEW_H_
#define _BAGUIPARTIALSCROLLVIEW_H_

#include "CCUIPartialScrollView.h"

class BankUIPartialScrollView: public CCUIPartialScrollView
{
public:
	virtual ~BankUIPartialScrollView(){};

	BankUIPartialScrollView(const CCRect& mRect);
    static BankUIPartialScrollView* bankScrollViewWithCCRect(const CCRect& mRect);

public:

};

#endif