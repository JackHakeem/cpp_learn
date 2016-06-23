#ifndef CAMPFIGHTMSGLISTVIEWITEM_H_
#define CAMPFIGHTMSGLISTVIEWITEM_H_

#include "LayerNode.h"

class CampFightMsgListViewItem : public LayerNode
{
public:
	CampFightMsgListViewItem();
	~CampFightMsgListViewItem();

	static CampFightMsgListViewItem* itemStrFactory(
		char* content, ccColor3B color , 
		float width = 400, float size = 20.0f);
	bool init(char* content, ccColor3B color , 
		float width = 400, float size = 20.0f);
private:

};

#endif