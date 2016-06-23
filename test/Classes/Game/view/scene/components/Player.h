
#ifndef HLQS_Player_h
#define HLQS_Player_h

//#include "Element.h"
#include "utils/findPath/FindPath8.h"
#include "LiveThing.h"
#include "model/player/vo/PlayerBaseVo.h"
#include "CCLabelTTF.h"
#include "CCStrokeLabel/CCStrokeLabel.h"

class Player : public LiveThing
{
public:

    Player();
	Player(PlayerBaseVo* playerVo);
    ~Player();
    virtual int getThingType() {return 2;}

    CCSprite * loadPlayer();
    CCSprite * getPlayerSprite();
    void playAnimation();
    void stopAnimation();
    
    //void playerMove(char** map_desc, int &h, int &w);
	void playerMove();
    void setFindPath8(char** map_desc, int &h, int &w);
	
	
	//add from flash
	void setPlayerName(CCNode* n, void* data);
	void setPlayerVo(PlayerBaseVo& playerVo, float scale = 1.0f);
	virtual void showHP(bool value);
	void showRes();
	void updateGuildName(CCNode* n, void* data);
	void clothLoadCompleteHandler(CCNode* n, void* data);
	void layout();
	virtual void dispose();
	virtual void moveComplete();
	void completeHandler();
	void movePath(std::vector<CCPoint>& path, float delay = 0.0f);
	void moveTo(CCPoint point, float delay = 0.0f);
	void addPath(std::vector<CCPoint>& path);
	void changePath(std::vector<CCPoint>& path);
	virtual void updateAction(bool repeat = true);
	std::vector<CCPoint>* getCurrentPath();
	virtual bool isHit();
	bool isHit(CCPoint point);
	void hide();
	void show();
	virtual void setGlow(bool value);
	float distance(Player* player);
	void setColor(ccColor3B col);
	virtual bool toAttack();
	void endAttackFun();
	virtual bool toHited(bool iscrit = false);
	void endHitFun();
	virtual void updateInfo();
	virtual bool hitTest(CCPoint point);
	virtual void toShade (bool value);
	virtual void setSelect(bool value);
	void icon(int value);
	int icon();
	virtual void poseChange();

	void setRoleSpeed(int nSpeed);
	void initDirArrow();
	void removeDirArrow();
	void resetDirArrow(int dir);
	void dirArrowVisible(bool visible);
	void goVisible(bool visible);

	void playEffect(int type);
	void removeEffect(CCNode * pTarget,void *pType);

	void showOnePNGEffect(int type);
	void removeOnePNGEffect(int type);

	void setRoleVipIcon(int vipLev);

public:
    CCAnimation* walkAnimation[5];
	std::vector<CCAnimation*> walk;
    CCAnimation* standAnimation[5];
    CCAction *m_action;
    
    CCAnimation* roleAnimation;
    
    int m_direction;

    vector<CCPoint> m_path;
	vector<CCPoint> _path;
	FindPath8 _fp8;
	char** mapData;

	//edit by edwardliu, from flash
	PlayerBaseVo _playerVo;
	CCLayer* _bodyLayer;
	CCLayer* _horseLayer;
	CCLayer _playerContainer;
	CCStrokeLabel* _nameTxt;
	CCStrokeLabel* _guildTxt;
	bool _isHide;
	std::string _clothURL;
	int _clothNum;
	std::string _weaponURL;
	int _stations;
	float _scale;
	bool _preGoVisible;
	CCSprite* _hpBar;
	bool _isOnbusiness;

	enum
	{
		TAG_PLAYER_ANI_SPRITE = 121,
		TAG_PLAYER_onePNG = 150,
		TAG_VIP_ICON = 165,
	};
    
};

#endif
