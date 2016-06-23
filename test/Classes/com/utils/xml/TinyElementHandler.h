#ifndef _TINYELEMENTHANDLER_H_
#define _TINYELEMENTHANDLER_H_

#include "tinystr.h"
#include "tinyxml.h"
#include <string>

class TinyElementHandler
{
public:
	TinyElementHandler(TiXmlElement* pEle);
	~TinyElementHandler();

	void get(unsigned int& dst);
	void get(int& dst);
	void get(char& dst);
	void get(std::string& dst);

private:
	TiXmlElement*	m_pEle;
	TiXmlAttribute* m_pAttr;
};

#endif 