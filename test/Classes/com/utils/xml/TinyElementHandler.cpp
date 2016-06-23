#include "TinyElementHandler.h"


TinyElementHandler::TinyElementHandler(TiXmlElement* pEle)
{
	m_pAttr = 0;
	m_pEle = pEle;
}

TinyElementHandler::~TinyElementHandler()
{

}

void TinyElementHandler::get(unsigned int& dst)
{
	int tmpdst = 0;
	get(tmpdst);
	dst = static_cast<unsigned int>(tmpdst);
}

void TinyElementHandler::get(char& dst)
{
	if (!m_pAttr)
	{
		m_pAttr = m_pEle->FirstAttribute();
		if (m_pAttr)
			dst = atoi(m_pAttr->Value());
	}
	else
	{
		m_pAttr = m_pAttr->Next();
		if (!m_pAttr)
		{
			//没得拿了 这里应该警告了
			return;
		}
		else
		{
			dst = atoi(m_pAttr->Value());
		}
	}
}

void TinyElementHandler::get(int& dst)
{
	if (!m_pAttr)
	{
		m_pAttr = m_pEle->FirstAttribute();
		if (m_pAttr)
			dst = atoi(m_pAttr->Value());
	}
	else
	{
		m_pAttr = m_pAttr->Next();
		if (!m_pAttr)
		{
			//没得拿了 这里应该警告了
			return;
		}
		else
		{
			dst = atoi(m_pAttr->Value());
		}
	}
}
	
void TinyElementHandler::get(std::string& dst)
{
	if (!m_pAttr)
	{
		m_pAttr = m_pEle->FirstAttribute();
		if (m_pAttr)
			dst = m_pAttr->Value();
	}
	else
	{
		m_pAttr = m_pAttr->Next();
		if (!m_pAttr)
		{
			//没得拿了 这里应该警告了
			return;
		}
		else
		{
			dst = m_pAttr->Value();
		}
	}
}
