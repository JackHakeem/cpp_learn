#include "RenderManage.h"

RenderManage::RenderManage()
{
	_isStop = true;
	start();
}

void RenderManage::start()
{
	/*if(_isStop)
		return;*/
	if(_isStop)
	{
		_isStop = false;
		this->schedule(schedule_selector(RenderManage::nextStep));
	}
}

void RenderManage::nextStep(ccTime dt)
{
	std::vector<IRender*>::iterator iter = _dic.begin();
	for(; iter != _dic.end(); ++iter)
	{
		if(*iter == NULL)
			continue;
		(*iter)->step();
	}
}

void RenderManage::stop()
{
	if(!_isStop)
	{
		_isStop=true;
		this->unschedule(schedule_selector(RenderManage::nextStep));
	}
}

void RenderManage::add(IRender* render)
{
	_dic.push_back(render);
}
void RenderManage::remove(IRender* render)
{
	std::vector<IRender*>::iterator iter = _dic.begin();
	for(; iter != _dic.end(); ++iter)
	{
		if((*iter) != NULL && (*iter) == render)
		{
			_dic.erase(iter);
			break;
		}
	}
}
int RenderManage::length()
{
	return _dic.size();
}

bool RenderManage::isStart()
{
	return !_isStop;
}

RenderManage::~RenderManage()
{
	_dic.clear();

	if ( this->getParent() )
	{
		this->removeFromParentAndCleanup(true);
	}
}
