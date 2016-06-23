#include "ChatTextPanel.h"

ChatTextPanel::ChatTextPanel()
{}

ChatTextPanel::~ChatTextPanel()
{}

bool ChatTextPanel::init()
{
	if (!LayerNode::init())
		return false;

	return true;
}