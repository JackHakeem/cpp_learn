#ifndef HLQS_Element_h
#define HLQS_Element_h
#include "BaseType.h"
#include "model/scene/vo/PoseState.h"
#include "model/scene/vo/DirState.h"
#include "utils/BitmapMovieClip.h"
#include "view/interfaces/IElement.h"
#include "model/com/vo/ResourceVo.h"

using namespace cocos2d;

#define TILE_WIDTH 60
#define TILE_HEIGHT 30

class Element: public IElement
{
public:
	
public:
    CCPoint startPoint;

    CCPoint endPoint;

    CCPoint m_mapPoint;

    
    CCPoint m_mapStartPoint;
    CCPoint m_mapEndPoint;


	//from flash
	float _angle;//
	float stepX; //每次移动的偏移量x
	float stepY; //每次移动的偏移量y
	float _speed;  //速度（像素/秒）
	int moveTime; //移动次数
    
	PoseState* poseState;
	DirState* dirState;

	int oldTime;
	float _tmpx;
	float _tmpy;
	bool canRedraw;
	bool isLoading;
	bool hasDispose;// 是否调用了dispose 避免step 渲染

	std::string _eleName;
	//std::vector<int> _otherInfos;
	//std::string _type;
	bool _isInteractive;
	CCPoint _endPoint;
	ResourceVo _res;

public:
    Element();
    ~Element();
    bool init();

    CCSprite *m_baseSprite;
    
    void setBaseSpritePos(float x,float y);
    
    void setStartPoint(float x,float y);
    CCPoint * getStartPoint();
    
    void setEndPoint(float x,float y);
    CCPoint * getEndPoint();
    
    CCPoint getMapEndPoint();
    CCPoint getMapStartPoint();
    
    CCPoint setEndPointByScreen(CCPoint cp, CCPoint pos_map, CCPoint pos_layer, float height, float width);
    void setStartPointByScreen(CCPoint cp, CCPoint pos_map, CCPoint pos_layer, float height, float width);
    void setStartPointByMapCell(CCPoint cell, CCPoint pos, CCPoint pos_layer, float height, float width);
    //void setStartPointByMapCell(CCPoint cp);
    void setStartPointByMap(CCPoint map, CCPoint pos,  CCPoint pos_layer, float height, float width);

    CCPoint getMapCurrentCell();
    CCPoint* getMapCurrentPoint();

    void setCurrentStartPoint(CCPoint pos, float h, float w);

	//from flash
	void changePoseHandler(CCNode* n, void* data);
	void changeDirHandler(CCNode* n, void* data);
	void redraw();
	virtual void dispose();
	void nextPosition();
	void updatePosition();
	void move1(CCPoint point, int delay = 0);
	void dirToPoint(CCPoint point);
	virtual void moveComplete();
	void update(bool repeat = true);
	virtual void layout();
	virtual void updateAction(bool repeat = true);
	void updateInfo();
	static BitmapMovieClip* loadDefautRes();
	void speed(float value);
	float speed();
	//void id(int value);
	//int id();
	void eleName(std::string value);
	std::string eleName();

	ResourceVo getResource();
	void setResource(ResourceVo &info);
	//void otherInfos(std::vector<int>& value);
	//std::vector<int>* otherInfos();
	//void type(std::string value);
	//virtual std::string type();
	virtual void isInteractive(bool value);
	virtual bool isInteractive();
	virtual bool isHit(CCPoint point);
	virtual void setGlow(bool value);
	virtual void step();
	void stop();
	virtual void setSelect(bool value);
	virtual bool hitTest(CCPoint point);
	void mapStartPoint(CCPoint pos);
	virtual void poseChange();

	Element(const Element&);
	Element& operator = (const Element&);
};

#endif
