#ifndef HLQS_FigureMainView_H_
#define HLQS_FigureMainView_H_

#include "PopContainer.h"
#include "FigureView.h"

USING_NS_CC;

class FigureMainView: public PopContainer
{
public:
	FigureMainView();
	~FigureMainView();

	bool init();
	void closeView();
	void clickCloseHandler(CCObject* pSender);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void moveBy(CCPoint pos);
	int getType();
	void setType(int);
	void changeStage(int32 stage);
	virtual	bool handleBack();
	virtual void removeDataObjectChild();
public:

	enum
	{
		RENDERZ_FigureContainer = 0,
		RENDERZ_buttonClose,
		RENDERZ_figureview,

	};

	enum
	{
		TAG_FIGUREVIEW=50,
		TAG_TAB = 100,
	};

	//CC_PROPERTY(int32, _TouchState, TouchState)	

	CCSize m_viewSize;
	FigureView* _figureV;
	int _currentId;

	CCLayer* _currentView;

	int _viewType;
};

#endif