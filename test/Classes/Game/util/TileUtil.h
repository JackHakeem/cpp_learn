#ifndef HLQS_TileUtil_h
#define HLQS_TileUtil_h

#include "cocos2d.h"
#include "utils/Singleton.h"

using namespace cocos2d;

class TileUtil: public Singleton<TileUtil>
{
private:
	int m_picWidth;
	int m_picHeight;
	int m_tileWidth;
	int m_tileHeight;
	int m_originTileWidth;
	int m_originTileHeight;
	int m_originPicWidth;
	int m_originPicHeight;
	
public:
	//const static int tileWidth = 60;
	//const static int tileHeight = 30;
	
public:
	TileUtil();
	~TileUtil();

	float changeXToTile(float num);
	float changeYToTile(float num);
	float changeXToPixs(float num);
	float changeYToPixs(float num);

	void setPicWidth( int w );
	void setPicHeight( int h );
	int getPicWidth();
	int getPicHeight();
	int getTileWidth();
	int getTileHeight();

	CCPoint changeTileToPixs(CCPoint pt);
	CCPoint changePixsToTile(CCPoint pt);

	int getOriginTileHeight();
	int getOriginTileWidth();
	int getOriginPicHeight();
	int getOriginPicWidth();
};

#endif