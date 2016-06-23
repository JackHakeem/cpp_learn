#ifndef _WORLD_SCENE_H_
#define _WORLD_SCENE_H_
#include "LayerNode.h"
#include "BaseScene.h"
#include "view/interfaces/IElement.h"
#include "WorldExit.h"
#include "ChildExitContainer.h"
#include "WorldBgBitmap.h"

class WorldScene : public BaseScene
{
public:
	bool _isTeamRoomPop;
	bool _childShow;
	float radius1;
	float radius2;
	ChildExitContainer* _childExitCon;
	WorldBgBitmap* _worldbg;

public:
	WorldScene();
	void addReturnButton();
	void onReturnButtonDown(CCObject* pSender);
	void addRole(float scale = 0.7);
	virtual void addElement(IElement* child, int zOrder = 0);
	void roleWalkCompleteHandler(CCNode* n, void* data);
	virtual void roleMoveElement(IElement* element);
	virtual void buildScene(int width, int height, int mapRank, int offsetX, int offsetY,std::string path, CCPoint focusPos);
	virtual void clickSceneHandler(CCPoint point);
	//virtual void moveSceneHandler();
	virtual void addExit(ExitVo* exitVo);
	WorldExit* getExit(int id);
	//virtual void setElemenetPosition(int vx, int vy, dis:DisplayObject);
	void showChildScene(IElement* element);
	void removeChildExitCon();
	void showChildSceneAutoFindPath(int id);
	void isTeamRoomPop(bool value);
	bool isTeamRoomPop();
	CCNode* getNewHandItem(int id, bool isPid = false);
	//void setChildExitStarLev(int childId, int starLev);
	virtual void  dispose();
	void showChildSceneHandle(std::vector<WorldExitData>& array, IElement& currElement);
	virtual CCPoint getElemenetPosition(float vx, float vy);
	void clickExit(CCNode *n, void* data);
};
#endif