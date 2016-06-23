#ifndef __FIGUREITEM_H_
#define __FIGUREITEM_H_

#include "cocos2d.h"
using namespace cocos2d;

class PlayerInfoVo;

class FigureItem : public CCLayer
{
public:
	FigureItem( const CCRect& rect);
	~FigureItem();

public:
	static FigureItem* FigureItemlWithRect( const CCRect& rect );
	void initPlayerVo( PlayerInfoVo* playerInfoVo, int id );

	int id();
	CCRect m_rect;
	int m_ItemIndex;

	CCLabelTTF* _txtLevel;
	CCLabelTTF* _txtName;

	PlayerInfoVo* _playerInfoVo;
};

#endif