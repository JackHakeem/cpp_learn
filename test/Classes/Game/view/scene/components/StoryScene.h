#ifndef _STORYSCENE_H_
#define _STORYSCENE_H_

#include "cocos2d.h"
#include "ImageContain.h"
#include "model/scene/vo/StoryScript.h"
#include "Element.h"
#include "Scene.h"
#include "manager/TimerManage.h"
#include "events/GameDispatcher.h"
#include "model/scene/vo/StoryVo.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "CustomButton.h"
#include "Player.h"
#include "MapNPC.h"
#include "Item.h"
#include "BaseScene.h"
#include "MapElement.h"

USING_NS_CC;

class Scene;
class StoryProxy;
class SceneProxy;
class CCUIBackground;
class SceneInfoVo;
class NPCChat;
class LiveThing;
struct _VOICE_;

class StoryScene : public BaseScene
{
public:
	StoryScene(Scene &scene,StoryVo &storyVo,SceneInfoVo * pInfoVo);
	virtual bool init();

	void dlgStep(ccTime dt);
	void resetTimer();
	void setFocus(CCPoint targetPosPixs);
	void addEndButton();
	void addToStage(CCObject *);
	void setBaseCoordinate(int x, int y);
	void quickEndStroy(CCObject *);
	virtual void clickSceneHandler(CCObject *);
	void showNext(StoryScript &storyNode);
	void doDialog();
	void walkCompleteHandler(CCNode *,void *);
	void showDialog(std::string content,std::string elemName,std::string halfBodyUrl);
	Element *getElement(StoryScript &storyNode);
	void hideDialogs();
	void onEnterBattle(CCNode *,void *);
	void onContentComplete(CCNode *,void *);
	void skipNext();
	void clear();
	virtual Player *addPlayerHandler(char * data);
	virtual MapNPC *addNPC(char * data);
	Item *addItem(char * data);
	void removeItem(int id);
	Item *getItem(int id);
	void showNewhandLeader();
	void clickNewHandTips(CCObject *);
	virtual void dispose();

	//void disappear(target:DisplayObject, disType:int=0);
	void fillContent();
	void dd();
	std::string getMcNameByResId(int resId);

	//
	void showAllUI(bool bValue);

	void speak(LiveThing * thing,_VOICE_ *_voice);

	//virtual void registerWithTouchDispatcher();
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	enum
	{
		SHOW_NEXT = 0,
	};

public:
	
	MovieClip	*	_skin_left;
	MovieClip	*	_skin_right;
	MovieClip	*	_skin;
	ImageContain*	_headImageContain;
	CCMenu *	_endBtn;
	CCLabelTTF * _pEndText;
	int			_w;
	int			_h;
	CCLayer	*	_container;
	StoryScript*	_storyNode;		
	Element	*	_element; 		
	int			_si;				 
	StoryVo	*	_storyVo;			
	Scene	*	_scene;			
	GameDispatcher * _dispatcher;  
	TimerManage *	_timerManage;
	bool			_isNewhandLeader;	

	int _caret;
	std::string _content;


	CCSize _screenSize;

	StoryProxy * _storyProxy;
	SceneProxy * _sceneProxy;
	CCUIBackground * _pNewHandTipsBg;
	CCUIBackground * _pUIBack;

	SceneInfoVo *_sceneInfoVo;
	CCPoint _preStoryFocusPos;

	NPCChat * _pCurNPCChat;
	CCNode * _curNewTips;
};

#endif