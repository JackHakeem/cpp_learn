#include "CardList.h"
#include "ArenaUI.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "model/arena/ArenaConst.h"
#include "socket/command/s36/SCMD36E.h"
#include "model/arena/ArenaConst.h"
#include "utils/ScaleUtil.h"

const float FontSize = 36.0f;
const float FontSize_0 = 36.0f;

CardList::CardList()
{
	_pContainer = 0;
}

CardList::~CardList()
{}

bool CardList::initWithParam(ArenaUI* pContainer)
{
	if (!LayerNode::init())
		return false;
	
	_pContainer = pContainer;


	//
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this, 
			menu_selector(CardList::takeAward) );
			_btn->setPosition(ccp(POSX(625), POSX(640-225)));

			_btn->setScaleX(3.0f);
			_btn->setScaleY(1.0f);

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::WindowLayer_Arena-1);
			this->addChild(buttonMenu, CardListZ_btn0, CardListTAG_btn0);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC042").c_str(), CCSizeMake(POSX(500), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setScaleX(0.3f);
			pLabel->setColor(ccc3(254, 189, 0));
		}
		
	}
	this->setIsVisible(false);
    
    return true;
}

		
void CardList::takeAward(CCObject* pSender)
{
	//
	this->setIsVisible(false);
	//
	_pContainer->dispatchEvent(ArenaConst::TAKE_AWARD, 0);
}

void CardList::update(SCMD36E* data)
{
	/*
	if(!_clickCard)return;
			
	_clickCard.setCard(data.b_id.value);
			
 	var choose:Array = [2,0,3,1];
	var pos:int = choose.indexOf(data.b_id.value);
	choose.splice(pos,1);
			
	var factor:int = int(Math.random() * choose.length);
	switch(factor){
		case 0:
			choose.sort(Array.DESCENDING);
			break;
		case 1:
			choose.sort(Array.NUMERIC);
			break;
		case 2:
			choose.sort(Array.NUMERIC);
			break;
		default:
					
			break;
	}
	for each(var card:CardItem in _cardDic){
		if(card == _clickCard)continue;
 		card.setCard(choose.shift());
	}
			
	_clickCard.play();
			
	setTimeout(function():void{
		for each(var card:CardItem in _cardDic){
			if(card == _clickCard)continue;
			card.play();
		}
	}, 700);
			
	setTimeout(function():void{
		_pContainer.dispatchEvent(new ParamEvent(ArenaConst.CARD_FINISH));
	}, 2500);
	*/
	_pContainer->dispatchEvent(ArenaConst::CARD_FINISH, 0);

}