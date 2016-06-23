#include "FocusNode.h"

int g_FocusGIDFactory = 0;

FocusNode::FocusNode()
{
	_MyFocusGID = g_FocusGIDFactory++;
}