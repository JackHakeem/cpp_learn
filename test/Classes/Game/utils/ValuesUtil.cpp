#include "ValuesUtil.h"
#include "utils/xml/tinyxml.h"
#include "utils/xml/TinyElementHandler.h"
#include "CCFileUtils.h"

#define XML_KEY key
#define XML_VALUE text

std::string ValuesUtil::getString( std::string key )
{
	MAP_STRING_STRING::iterator it = _StringsMap.find(key);
	if(it == _StringsMap.end())
	{
		return "";
	}
	else
	{
		return (*it).second;
	}
}

void ValuesUtil::init()
{
	initStrings();
}

void ValuesUtil::initStrings()
{
	const char* filename = CCFileUtils::fullPathFromRelativePath("assets/values/strings.xml");

	if (!filename)
		return;

	TiXmlDocument xmlDoc(filename); 
	bool sus = xmlDoc.LoadFile();  
	if (!sus)
		return;

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
					break;
				}
				TinyElementHandler elehandler(pEle);

				std::string key, text;
				elehandler.get(key);
				elehandler.get(text);

				int cPos = text.find( "#" );	// from # _jae
				if ( cPos != -1 )
				{
					string splitStr = text.substr( cPos + 1, text.length() );
					int cPos2 = splitStr.find( "#" );
					cPos2 = cPos + cPos2;

					if ( cPos2 != -1 )
					{
						string tmp = text.substr( cPos+2, cPos2+1 );
						text.erase( cPos, 5 );
						tmp = getString( tmp );
						if ( tmp.length() >= 6 )
						{
							string c1 = "0x" + tmp.substr( 1, 2 );
							tmp.erase( 0, 3 );
							string c2 = "0x" + tmp.substr( 0, 2 );
							tmp.erase( 0, 2 );
							string c3 = "0x" + tmp.substr( 0, 2 );

							int r(0), g(0), b(0);
							char* outStr;
							r = strtol( c1.c_str(), &outStr, 16 );
							g = strtol( c2.c_str(), &outStr, 16 );
							b = strtol( c3.c_str(), &outStr, 16 );					

							_ColorMap.insert(  make_pair( key, ccc3(r, g, b) )  );
						}
					}
								
				}

				_StringsMap.insert(make_pair(key, text));

				break;
			}
		default:
			break;
		}
	}
}

cocos2d::ccColor3B ValuesUtil::getColor( std::string key )
{
	MAP_STRING_COLOR3B::iterator it = _ColorMap.find(key);
	if( it == _ColorMap.end() )
	{
		return ccRED;
	}
	else
	{
		return it->second;
	}
}


