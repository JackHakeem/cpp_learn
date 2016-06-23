#ifndef _MSGITEM_H_
#define _MSGITEM_H_
#include "LayerNode.h"
#include "BaseType.h"
//#include "ccTypes.h"

class CMsgItem : public LayerNode
{
public:
	CMsgItem();
	~CMsgItem();
	bool init(char* content, ccColor3B color);
protected:
private:
	CCLayer* m_pContainer;
};
#endif