#pragma once

#include "CCUIPartialScrollView.h"

class CustomComboBox: public CCUIPartialScrollView
{
public:
	virtual ~CustomComboBox(){};

	CustomComboBox(const CCRect& mRect);
	bool initWithParam(CCNode* target, SEL_CallFuncND selector, void* data);
    static CustomComboBox* customComboBoxWithCCRect(const CCRect& mRect);
	void visit();
	bool getIsTouchInContentLayer( CCTouch *pTouch);
	void moveToNextPageClick(CCObject* pSender);
	void moveToPreviousPageClick(CCObject* pSender);
	void handleTouchEndPagePre();
	void handleTouchEndPageNext();
	void handleTouchEnd2Page();
	int getTagByIndex(int index);
	void refreshLvBoxLabel();
	void execute();
public:
	int dataProvider(int tag, const char* value);

	std::vector<int> m_realtag2tag;
	int m_screen_last;
	CC_PROPERTY(int, _selectedIndex, selectedIndex)
public:
	CCNode*   m_pSelectorTarget;
	SEL_CallFuncND m_pCallFuncND;
	void* m_data;
};