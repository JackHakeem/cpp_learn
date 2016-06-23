#ifndef _DIALOGVIEW_H
#define _DIALOGVIEW_H

#include "cocos2d.h"
#include "PopContainer.h"
#include "model/dialog/vo/NPCDialogueVo.h"
#include "UIListView/CCUIListView.h"
#include "UIListView/CCUIListViewAdapter.h"
#include "LayerNode.h"
#include "model/dialog/vo/TaskNodeVo.h"
#include "UIListView/CCUIListViewItemActionListener.h"
#include "model/shop/vo/shopVo.h"
#include "DialogItem.h"

using namespace cocos2d;

class DialogView :public PopContainer, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	DialogView();
	~DialogView();

	bool init();
	LAYER_NODE_FUNC(DialogView);
	void setData( NPCDialogueVo* value );

	int _npcId;
	bool _autoPop;
	bool _noStory;
	int npcId();

	CCNode *getNewHandItem(int typeId);
private:
	void showString( std::string str, float x, float y, ccColor3B ccCol, int fontSize, bool bold = false );

	void buildTaskBtns();

	// Button
	void clickShopItemHandler();		// Function interaction list

	virtual void removeDataObjectChild();

	// Listview adapter
	virtual int getCount();
	virtual LayerNode * getView( int position );

	virtual void onItemClickListener( LayerNode *itemCell, int position );

	virtual void onItemTouchListener( LayerNode *itemCell, int position );

	virtual void onItemTouchCancelListener( LayerNode *itemCell, int position );

	
	NPCDialogueVo* _npcDialogueVo;

	std::string _NameTxt;			//npcName display

	std::string _headImageContain; // head show container
	std::string _dialogContent; // dialog box contents
	std::string _answerContent; // reward content
	std::string _dialogTxt; // NPC dialogue text display
	std::string _dialogTxt_Answer; // NPC dialogue text display
	std::string _taskBtnContainer; // interactive button displays container
	std::string _answerBtnContainer; // interactive button displays container
	std::string awardTxt;
	std::string _goodsContainer; // rewards container
	std::string _chatList; // shop name, the NPC list of words appear
	std::string _closeBtn;			// close button

	//CCLabelTTF* m_pLabelNPCName;
	//CCSprite*	m_pSpriteHeadImage;
	//CCLabelTTF* m_pLabelNPCContent;

	TaskNodeVo *pFocusTask;
	//Doyang 20120710
	//std::vector<TaskNodeVo *> _taskList;

	CCUIListView *_pDialogListView;
	std::vector<LayerNode *> _listViewItemsList;

	void clickTaskOpeItemHandler(TaskNodeVo *pTask);
	void addTaskOpeItem(int type, TaskNodeVo *pTask);
	void showDialog(TaskNodeVo *pTask, DialogueNodeVo *pDialog);
	void showTask(TaskNodeVo *pTask, DialogueNodeVo *pDialog);
	void receiveTask(TaskNodeVo *pTask, DialogueNodeVo *pDialog);
	void finishTask(TaskNodeVo *pTask, DialogueNodeVo *pDialog);
	void noFinishTask(TaskNodeVo *pTask, DialogueNodeVo *pDialog);

	void closeDialog();
	void registerWithTouchDispatcher( void );
	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
};


#endif