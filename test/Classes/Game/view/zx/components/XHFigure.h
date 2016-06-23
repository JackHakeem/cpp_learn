#pragma once
#include "CCUIPartialScrollView.h"


class XHFigure:public CCUIPartialScrollView
{
public:

	enum 
	{
		TAG_MODEL = 99,
	};
	

public:
	XHFigure();
    ~XHFigure();
	XHFigure(const CCRect& mRect);
	static XHFigure* figureScrollViewWithCCRect(const CCRect& mRect);

	bool init();
	void showModel(int figureID,int page);
	int getCurScreenFigureId();
public:
	void handleTouchEndPagePre();
	void handleTouchEndPageNext();
 	virtual void registerWithTouchDispatcher();
	void refreshFigureEquipXH();
public:
	std::map<int, int> m_vPage2Figure;
};