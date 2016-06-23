#include "FigureItem.h"
#include "BaseType.h"
#include "manager/ViewManager.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "StrengFigureCreate.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"

FigureItem::FigureItem( const CCRect& rect)
{
	m_rect = rect;
	m_ItemIndex = 0;

	_txtLevel = 0;
	_txtName = 0;
	
	_playerInfoVo = 0;

	//CCLayerColor* pLayer = new CCLayerColor();
	//pLayer->initWithColorWidthHeight(  ccc4( 120, 255, 120, 100 ), (GLfloat)rect.size.width, (GLfloat)rect.size.height  );
	//this->addChild(pLayer);
}

FigureItem::~FigureItem()
{

}

FigureItem* FigureItem::FigureItemlWithRect(  const CCRect& rect )
{
	FigureItem* pItem = new FigureItem(rect);
	if (!pItem->init())
	{
		return NULL;
	}
	pItem->setContentSize( rect.size );
	pItem->setAnchorPoint( CCPointZero );
	//pItem->setPosition( rect.origin );
	//pItem->autorelease();
	
	return pItem;
}

void FigureItem::initPlayerVo( PlayerInfoVo* playerInfoVo, int id )
{
	_playerInfoVo = playerInfoVo;
	m_ItemIndex = id;
	if ( !_txtName )
	{
		// figure name
		string str = playerInfoVo->playerBaseInfo.name;
		char txt[54];
		sprintf( txt, ValuesUtil::Instance()->getString("trJi").c_str(), playerInfoVo->playerBaseInfo.lev() );
		str = str + "(" + txt + ")";
		_txtName = CCLabelTTF::labelWithString( str.c_str(), g_sSimHeiFont, POSX(36) );
		_txtName->setColor( cocos2d::ccWHITE );
		_txtName->setPosition( ccp( m_rect.size.width/2.0f, m_rect.size.height/2.0f ) );
		addChild( _txtName );
	}
}

int FigureItem::id()
{
	//return (*(RoleManage::Instance()))._currentId;  // temp data！！

	if(!_playerInfoVo)return -1;
	return _playerInfoVo->playerBaseInfo.id;
}