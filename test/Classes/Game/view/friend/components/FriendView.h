#ifndef _FRIENDVIEW_H_
#define _FRIENDVIEW_H_

#include "PopContainer.h"
#include "LayerNode.h"
#include "model/friend/vo/FriendInfoVo.h"

class FPContainer;
class FriendView:public PopContainer
{
public:
	enum
	{
		FriendViewZ_title,
		FriendViewZ_btn_haoyou,
		FriendViewZ_btn_black,
		FriendViewZ_btn_tuijian,
		FriendViewZ_btn0,
		FriendViewZ_arrow_left,
		FriendViewZ_arrow_right,
		FriendViewZ_page,
	};

	enum
	{
		FriendViewTAG_title,
		FriendViewTAG_btn_haoyou,
		FriendViewTAG_btn_black,
		FriendViewTAG_btn_tuijian,
		FriendViewTAG_btn0,
		FriendViewTAG_arrow_left,
		FriendViewTAG_arrow_right,
		FriendViewTAG_page,
	};

	enum
	{
		CHANGE_LIST,
		CHANGE_PAGE,
	};
	FriendView();
	~FriendView();
	bool init();
	void setPage(int32 max=1, int32 index=1);
	void updateList(std::list<FriendInfoVo>* arr, int32 page);
	void btn_haoyou(CCObject* pSender);
	void btn_tuijian(CCObject* pSender);
	void btn_black(CCObject* pSender);
	void onTabIndexChange(int32 type);
	void changeBtn(int32 type);
	void btn_addPlayer(CCObject* pSender);
	void btn_oneClickAddAllPlayer(CCObject* pSender);
	void btn_toBlack(CCObject* pSender);
	void quickAddRecommendFriends();
	void handleAddPlayerConfirm(CCObject* pSender);
	void handleAddPlayerCancel(CCObject* pSender);
	void onClickPre();
	void onClickNext();
	void updatePageShow(int max, int index);//更新当前页总页数
	void handleArrowBtnNextPage(CCObject* pSender);
	void handleArrowBtnPrePage(CCObject* pSender);
	CCNode * getNewHandItem(int id);
	virtual void clickCloseHandler(CCObject* pSender);
public:
	/**视图数据初始化的标志，初始为false更新列表后为true*/
	bool hasInit;
	int32 _pageNum;
	FPContainer* _fpContainer;
	bool _friCrystalEnabel;
	CCLayer *_pContainer;

	CCMenuItemSprite *_btn_tuijian;
	CCMenuItemSprite *_btn_Alladd;
};

#endif