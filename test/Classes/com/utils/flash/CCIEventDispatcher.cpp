#include "CCIEventDispatcher.h"

void CCIEventDispatcher::removeEventListener( int flag, CCNode* tar, SEL_CallFuncND selector )
{
	m_it = m_vCallFuncND.find(flag);
	if ((m_it = m_vCallFuncND.find(flag)) != m_vCallFuncND.end())
	{
		std::list<KKCallfunc>::iterator it = m_it->second.begin();
		for ( ; it != m_it->second.end(); it++ )
		{
			KKCallfunc func = *it;
			if ( (func.m_pSelectorTarget == tar) && (func.m_pCallFuncND == selector) )
			{
				m_it->second.erase( it );
				break;
			}
		}

		if ( m_it->second.size()==0 )
		{
			m_vCallFuncND.erase(m_it);
		}
	}
}
