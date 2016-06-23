#ifndef _REPORTVIEW_H_
#define _REPORTVIEW_H_

#include <string>
#include "PopContainer.h"
#include "BaseType.h"
#include "ReportVo.h"
#include "events/GameDispatcher.h"

class ReportView : public PopContainer
{
public:


    ReportView();
    ~ReportView(){}
	   
public:
    bool init();
private:
	enum
	{
		TAG_BACKGROUND = 100,
	};

    int _curPage;

	CCNode* _pLeftPage;
    CCNode* _pRightPage;
	bool canTurnPage;
protected:
	virtual void clickCloseHandler(CCObject* pSender);
    void onClose(CCObject* pSender);
    void onReportFirst(CCObject* pSender);
	void onReportThird(CCObject* pSender);
    void onPageUp(CCObject* pSender);
    void onPageDown(CCObject* pSender);

	void showPage(CCNode* pPage, int pageNum, bool bShowBtn = false);
public:
	void updateView();
	void setCurrentPage(int page) { _curPage = page; }

	void updateReportList(const std::vector<ReportHeadVo>& vec);

public:
    LayerNode* _container;
	GameDispatcher* dispatcher;

public:
	ReportVo datas;

private:
	void pageUpCallback(CCNode* pNode);
	void pagetDownCallback(CCNode* pNode);
	//void actionCompleteHandle(CCNode* pNode);
	void pageUpCompleteHandle(CCNode* pNode);
	void pageDownCompleteHandel(CCNode* pNode);
};

#endif
