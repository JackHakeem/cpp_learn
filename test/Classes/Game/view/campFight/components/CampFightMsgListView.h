#ifndef _CAMPFIGHTMSGLISTVIEW_H_
#define _CAMPFIGHTMSGLISTVIEW_H_
#include "BaseType.h"
#include "LayerNode.h"
#include "KKUIListView/KKCCUIListView.h"

class CCFMsgListView : public LayerNode, KKCCUIListViewAdapter, KKCCUIListViewItemActionListener
{
public:
	CCFMsgListView();
	~CCFMsgListView();

	virtual bool init();
	virtual std::vector<LayerNode*>* getViewList() {return &m_lsItems;}
	//ListView adapter
	//virtual int getCount();
	//virtual LayerNode* getView(int position);
	//virtual void onItemClickListener(LayerNode* item, int position);

	void AddRecords(std::string str);
private:
	void ClearCacheItems();
private:
	std::vector< LayerNode* > m_lsItems;

	KKCCUIListView* m_pListView;
	//LayerNode*    m_pSelectedItem;
};

#endif