#ifndef _DIALOG_ITEM_H_
#define _DIALOG_ITEM_H_
#include "LayerNode.h"


enum DialogItemType
{
	DIALOG_ITEM_TASK_BEGIN = 0,
	DIALOG_ITEM_TASK_REC,
	DIALOG_ITEM_TASK_ACCEPT,
	DIALOG_ITEM_TASK_SUBMIT,
	DIALOG_ITEM_TASK_NOFINISH,
	DIALOG_ITEM_SHOP
};

class DialogItem : public LayerNode
{
public:
	DialogItem(){}
	
	void setType(DialogItemType type) { _type = type; }

	DialogItemType getType() { return _type; }

private:
	DialogItemType _type;
};
#endif