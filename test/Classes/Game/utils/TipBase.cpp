#include "TipBase.h"

TipBase::TipBase():myInfo(0),_myInfo(0),m_myXHInfo(0)
{}

TipBase::~TipBase()
{}

CCSize TipBase::getSrcContentSize()
{
    CCSize size = CCSizeMake(0, 0);
	return size;
}