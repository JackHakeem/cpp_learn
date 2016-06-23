#ifndef _NODEOBJECT_H_
#define _NODEOBJECT_H_
#include "BaseType.h"


/**
	 * Save the corresponding character formation position Numbers
	 * @author yanwudong
	 * 
	 */	
class NodeObject
{

public:
	uint32 sitGrid ;
	uint32 figureId ;

public:
	NodeObject();
	virtual ~NodeObject();
};


#endif