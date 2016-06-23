#ifndef _Story_Chat_UI_Print_View_
#define _Story_Chat_UI_Print_View_
#include "UIPrintView/CCUIPrintView.h"

class StoryChatUIPrintView : public CCUIPrintView
{
public:
	StoryChatUIPrintView();
	virtual ~StoryChatUIPrintView();
	static StoryChatUIPrintView * initUIPrintViewWithCCRect(CCRect rect,std::string strText,float time,float fontsize);

public:
	virtual void callBackFun();
};

#endif