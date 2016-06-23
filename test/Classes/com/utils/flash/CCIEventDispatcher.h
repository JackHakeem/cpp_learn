#pragma once
#include "cocos2d.h"
#include <map>
#include <list>

USING_NS_CC;
    
#define callfunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)
#define callfuncND_selector(_SELECTOR) (SEL_CallFuncND)(&_SELECTOR)

class Event
{
public:

	enum
	{
		COMPLETE = 0,
		CHANGE_THREATEN,
		CHANGE,
		CHANGE_GOLD,
		CHANGE_GOLDCOUNT,
		CHANGE_SILVER,
		CHANGE_SILVER_LIM,
		CHANGE_PRACTICE,
		CHANGE_POPULARITY,
		CHANGE_STONE,
		CHANGE_ENERGY,
		CHANGE_VIPLEV,
		CHANGE_CRYSTAL_LEV,
		CHANGE_HONOR_TITLE,
		CHANGE_CRYSTAL_CD_NUM,
		CHANGE_TRIAN_SIT_NUM,
		ADDED_TO_STAGE,
		CHANGE_VIGOUR_BUFF,
	};

};

class KKCallfunc
{
public:
	KKCallfunc() {m_pSelectorTarget = 0; m_pCallFuncND = 0; m_data = 0;}
	~KKCallfunc() {}

	void execute()
	{
		if (m_pSelectorTarget && m_pCallFuncND) 
		{
			(m_pSelectorTarget->*m_pCallFuncND)(m_pSelectorTarget, m_data);
		}
	}

public:
	CCNode*   m_pSelectorTarget;
	SEL_CallFuncND m_pCallFuncND;
	void* m_data;
};

class CCIEventDispatcher
{
public:
	CCIEventDispatcher(){};
	~CCIEventDispatcher()
	{
		m_vCallFuncND.clear();
	}

	void addEventListener(int flag, CCNode* tar, SEL_CallFuncND selector)//SEL_CallFuncND fun
	{
		KKCallfunc newone;
		newone.m_pSelectorTarget = tar;
		newone.m_pCallFuncND = selector;
		newone.m_data = 0;

		m_it = m_vCallFuncND.find(flag);
		if (m_it == m_vCallFuncND.end())
		{
			std::list<KKCallfunc> funList;
			funList.push_back(newone);
			m_vCallFuncND.insert(std::make_pair(flag, funList));
		}
		else
		{
			std::list<KKCallfunc>::iterator it = m_it->second.begin();
			for ( ; it != m_it->second.end(); it++ )
			{
				KKCallfunc func = *it;
				if ( (func.m_pSelectorTarget == tar) && (func.m_pCallFuncND == selector) )
				{
					//CCAssert(func.m_pSelectorTarget != tar, "Same event add twice!");
					return;
				}
			}

			m_it->second.push_back(newone);
		}
	}

	void removeEventListener(int flag)
	{
		if ((m_it = m_vCallFuncND.find(flag)) != m_vCallFuncND.end())
		{
			m_vCallFuncND.erase(m_it);
		}
	}

	//jae note 20120725
	void removeEventListener(int flag, CCNode* tar, SEL_CallFuncND selector);

	void dispatchEvent(int flag, void* data)
	{
		if ((m_it = m_vCallFuncND.find(flag)) != m_vCallFuncND.end())
		{
			std::list<KKCallfunc> funList = m_it->second;
			std::list<KKCallfunc>::iterator it;
			for(it = funList.begin(); it != funList.end(); ++ it)
			{
				KKCallfunc fun = (KKCallfunc) *it;
				fun.m_data = data;
				fun.execute();
			}
		}
	}

	bool hasEventListener(int flag)
	{
		return m_vCallFuncND.find(flag) == m_vCallFuncND.end();
	}

public:
	/*static CCIEventDispatcher * Instance()
	{
	if (0 == ms_pInstance)
	{
	ms_pInstance = new CCIEventDispatcher();
	}

	return ms_pInstance;
	}

	static void DestroyInstance()
	{
	if (ms_pInstance) {		
	delete ms_pInstance;
	ms_pInstance = 0;
	}
	}*/

private:

	/*static CCIEventDispatcher *		ms_pInstance;*/


private:
	std::map<int, std::list<KKCallfunc> >::iterator m_it;
	std::map<int, std::list<KKCallfunc> > m_vCallFuncND;
};


