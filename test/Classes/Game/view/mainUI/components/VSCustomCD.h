#ifndef _VS_CUSTOMCD_H__
#define _VS_CUSTOMCD_H__
#include "CustomCD.h"

class VSCustomCD : public CustomCD
{
public:
	VSCustomCD( int type );
	virtual ~VSCustomCD();

	virtual void CDCallback();

public:
	CC_SYNTHESIZE(int , _isCDReady , IsCDReady);
};



#endif