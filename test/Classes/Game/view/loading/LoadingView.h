#ifndef _LoadingView_H_
#define _LoadingView_H_

#include "cocos2d.h"
#include "CCUIBackground.h"
USING_NS_CC;


class LoadingView : public CCLayer
{
public:
	LoadingView();
	~LoadingView();

	virtual bool init();
	void loadOneProgress( CCObject* pObj, void* pData );
	void visit();
public:

	enum LayerTag
	{
		TAG_PARENT,
		TAG_LOADING,
		TAG_LOADING_CUR,
	};

	CCLayer *pParentLayer;
	CCUIBackground* _proBg;
	CCSprite* _curSprite;
};
#endif