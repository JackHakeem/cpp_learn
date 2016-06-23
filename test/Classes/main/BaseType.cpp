 #include "BaseType.h"
//#include "third_party/win32/iconv/iconv.h"

USING_NS_CC;

int GBKToUTF8(std::string & gbkStr, const char* toCode, const char* fromCode)
{
//	if (gbkStr.size() <= 0)
//		return 0;
//
//	iconv_t iconvH;
//	iconvH = iconv_open(fromCode, toCode);
// 
//	if (iconvH == 0)
//	{
//			return -1;
//	}
//	const char* strChar = gbkStr.c_str();
//	const char** pin = &strChar;
//	size_t strLength = gbkStr.length();
//	char* outbuf = (char*) malloc(strLength*4);
// 
//	char* pBuff = outbuf;
// 
//	memset( outbuf, 0, strLength*4);
//	size_t outLength = strLength*4;
//	if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))
//	{
//			iconv_close(iconvH);
//			return -1;
//	}
// 
//	gbkStr = pBuff;
//	iconv_close(iconvH);
	return 0;
}

cocos2d::CCPoint getScreenPos(cocos2d::CCNode* obj, bool pixels)
{
	cocos2d::CCPoint pos = ccp(0, 0);
	if (pixels)
	{
		while(obj)
		{
			pos = ccpAdd(pos, obj->getPositionInPixels());
			obj = obj->getParent();
		}
	}
	else
	{
		while(obj)
		{
			pos = ccpAdd(pos, obj->getPosition());
			obj = obj->getParent();
		}		
	}

	return pos;
}

