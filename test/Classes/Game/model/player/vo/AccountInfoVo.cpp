#include "AccountInfoVo.h"

void AccountInfoVo::gold(int value)
{
	_gold = value;
	dispatchEvent(Event::CHANGE_GOLD, NULL);
}