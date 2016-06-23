#ifndef _CAMPFIGHTPLAYERLISTVIEW_H_
#define _CAMPFIGHTPLAYERLISTVIEW_H_
#include "BaseType.h"
#include "LayerNode.h"
#include "UIListView/CCUIListView.h"

enum CampFightType
{
	CAMP_ICE = 0,
	CAMP_FIRE = 1,
};

class CCFPlayerListView : public LayerNode, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	CCFPlayerListView();
	~CCFPlayerListView();

	virtual bool init();

	//ListView adapter
	virtual int getCount();
	virtual LayerNode* getView(int position);
	virtual void onItemClickListener(LayerNode* item, int position);

	void AddItem(LayerNode* item);
	void RemoveAllItems();
	void Refresh();
	
	void SetCamp(CampFightType c_){m_camp = c_;}
private:
	std::vector< LayerNode* > m_lsItems;
	CCUIListView* m_pListView;
	LayerNode*    m_pSelectedItem;
	CampFightType m_camp;
};

#endif
