#include "TileUtil.h"
#include "utils/ScaleUtil.h"

//POSX edwardliu

TileUtil::TileUtil()
{
	m_picWidth = POSX(256);
	m_picHeight = POSX(256);
	m_tileWidth = POSX(60);
	m_tileHeight = POSX(30);
	m_originTileWidth = 60;
	m_originTileHeight = 30;
	m_originPicWidth = 256;
	m_originPicHeight = 256;
}

float TileUtil::changeXToTile(float num)
{
	return int(num / (float)m_tileWidth);
}

float TileUtil::changeYToTile(float num)
{
	return int(num / (float)m_tileHeight);
}

float TileUtil::changeXToPixs(float num)
{
	return num * (float)m_tileWidth + (float)m_tileWidth / 2;
}

float TileUtil::changeYToPixs(float num)
{
	return num * (float)m_tileHeight + (float)m_tileHeight / 2;
}
		
CCPoint TileUtil::changeTileToPixs(CCPoint point)
{
	return ccp(changeXToPixs(point.x), changeYToPixs(point.y));
}
		
CCPoint TileUtil::changePixsToTile(CCPoint point)
{
	return ccp(changeXToTile(point.x), changeYToTile(point.y));
}

int TileUtil::getPicWidth()
{
	return m_picWidth;
}

int TileUtil::getPicHeight()
{
	return m_picHeight;
}

int TileUtil::getTileWidth()
{
	return m_tileWidth;
}

int TileUtil::getTileHeight()
{
	return m_tileHeight;
}

int TileUtil::getOriginTileWidth()
{
	return m_originTileWidth;
}

int TileUtil::getOriginTileHeight()
{
	return m_originTileHeight;
}

int TileUtil::getOriginPicWidth()
{
	return m_originPicWidth;
}

int TileUtil::getOriginPicHeight()
{
	return m_originPicHeight;
}

TileUtil::~TileUtil()
{

}

void TileUtil::setPicWidth( int width )
{
	m_picWidth = width;
}

void TileUtil::setPicHeight( int height )
{
	m_picHeight = height;
}
