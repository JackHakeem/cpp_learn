#pragma once
#include "BaseType.h"
#include "UIListView/CCUIListViewAdapter.h"
#include "UIListView/CCUIListView.h"
#include "model/zx/XHConfManager.h"

class ZXer;
class ZXDuiView:public LayerNode, CCUIListViewAdapter
{
public:
	//enum
	//{
	//	ZXViewTAG_SLOT = 1000,

	//	ZXViewTAG_BAG = 2000,

	//	ZXViewTAG_ZXEr = 3000,
	//};

	ZXDuiView();
	~ZXDuiView();

	bool init();
	void clickClose(CCObject* pSender);

	virtual int getCount();
	virtual LayerNode * getView( int position );
	LayerNode * createListItem(int indexL, int  indexR);
	void clickBuy(CCObject* pSender);
	void updateScore(int32 val);
	void clickBackZX(CCObject* pSender);
public:
	LayerNode* _pContainer;

	CCUIListView *_pListView;

	std::vector<XHConfVo> _dataConf;
};