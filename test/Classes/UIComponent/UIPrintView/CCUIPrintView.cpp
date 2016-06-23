#include "CCUIPrintView.h"
#include "utils/ScaleUtil.h"
#include "CCUIPrintLine.h"
#include "utils/Timer.h"

CCUIPrintView::CCUIPrintView()
{
	_nLineCount = 0;
	_nByteCount = 0;
	_nMaxLineCount = 0;
	_nVisitWidth = 0;
	setFontSize(20.0f);
	setPrintString("");
	setPrintRect(CCRectMake(0,0,0,0));
	for (int i = 0;i<64;i++)
	{
		_pLinePtr[i] = 0;
	}
	for (int i = 0;i<64;i++)
	{
		_strLineArr[i] = 0;
	}
}

CCUIPrintView::~CCUIPrintView()
{
	cleanup();
}

CCUIPrintView * CCUIPrintView::initUIPrintViewWithCCRect(CCRect &rect,std::string strText,float time,float fontsize)
{
	CCUIPrintView * pPrintView = new CCUIPrintView();
	if (pPrintView && pPrintView->init())
	{
		pPrintView->setPrintRect(rect);
		pPrintView->setDeltaTime(time);
		pPrintView->setFontSize(fontsize);
		pPrintView->setPrintString(strText);
		pPrintView->loadItems();
		//pPrintView->run();
		return pPrintView;
	}
	CC_SAFE_DELETE(pPrintView);
	return 0;
}

bool CCUIPrintView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	return true;
}

void CCUIPrintView::loadItems()
{
	CCRect rect = getPrintRect();
	CCSize rectSize = rect.size;
	float fontSize = getFontSize();
	float LineSize = fontSize * 1.2f;

	std::string strText = getPrintString();
	_strList = createLineString(strText);
	std::vector<std::string> strList = _strList;
	int count = 0;
	std::vector<string>::iterator iter =  strList.begin();
	for (;iter != strList.end();iter++)
	{
		_strLineArr[count] = (*iter).c_str();
		++count;
	}

	int nLineCount = strList.size();
	_nMaxLineCount = nLineCount;
	float nOffsetY = (LineSize/2.0f) * (nLineCount-1);
	for(int i = 0; i < nLineCount; i++)
	{
		float posY = nOffsetY - i* LineSize;
		
		CCUIPrintLine * pPrintLine = CCUIPrintLine::initUIPrintLineWithCCRect(rect.size, strList.front(), fontSize);
		pPrintLine->setPosition(ccp(POSX(0),posY));
		strList.erase(strList.begin());
		pPrintLine->setTag(TAG_LAB_TXT+i);
		this->addChild(pPrintLine);
		_pLinePtr[i] = pPrintLine;
		if (i == nLineCount-1 )
		{
			_pLinePtr[i ]->setIsLastLine(true);
		}
		pPrintLine->release();
	}
}

std::vector<string> CCUIPrintView::createLineString(std::string strText)
{ 
	std::string strtmp = strText; 
	std::vector<string> strList;

	float fontSize = getFontSize();
	CCSize rectSize = getPrintRect().size;
	int length = strText.length();

	float sumWidth = 0;
	int widthByte = 0;
	int lineByte = 0;
	int beginPos = 0;
	int pos = beginPos;
	while (sumWidth < length)
	{
		while (((widthByte * fontSize/2.0f) < rectSize.width) && (pos < length))
		{
			if (strText[pos] & 0x80)
			{
				widthByte += 3;
				pos += 3;
			}
			else
			{
				widthByte += 1;
				pos += 1;
			}
		}
		strtmp = strText; 
		std::string str = strtmp.substr(beginPos,widthByte);
		strList.push_back(str);

		beginPos += widthByte;
		pos = beginPos;

		sumWidth += widthByte;
		widthByte = 0;
	}
	
	return strList;
}

void CCUIPrintView::step(ccTime dt)
{
	float fontSize = getFontSize();
	CCRect rect = getPrintRect();
	if (_nLineCount >= _nMaxLineCount)
	{
		doFollow();
		return;
	}
	std::string str = _strList.front();//_strLineArr[_nLineCount];
	int len =  str.length();
	if ( (_nVisitWidth >= rect.size.width) || (_nByteCount >= len))
	{
		_pLinePtr[_nLineCount]->visit(CCSizeMake(rect.size.width, fontSize * 1.2f));
		if (_nLineCount >= (_nMaxLineCount-1))
		{
			doFollow();
			return;
		}

		++_nLineCount;

		if (_strList.empty())
		{
			doFollow();
			return;
		}
		_strList.erase(_strList.begin());
		str =  _strList.front();//_strLineArr[_nLineCount];

		if (str.empty())
		{
			doFollow();
			return;
		}
		_nByteCount = 0;
	}

	CCSize size;

	_nByteCount += 3; // add LH0814
	
	size = CCSizeMake(_nByteCount * fontSize/2, fontSize * 1.2f);

	_nVisitWidth = size.width;
	
	_pLinePtr[_nLineCount]->visit(size);
}

void CCUIPrintView::doFollow()
{
	this->stop();
	_nByteCount = 0;
	_nLineCount = 0;

	callBackFun();
}

void CCUIPrintView::run()
{
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(CCUIPrintView::step),this,getDeltaTime(),false);
}

void CCUIPrintView::stop()
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(CCUIPrintView::step),this);
}