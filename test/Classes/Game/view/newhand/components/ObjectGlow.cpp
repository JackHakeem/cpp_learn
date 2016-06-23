#include "ObjectGlow.h"
#include "manager/LayerManager.h"
#include "model/newhand/vo/NewhandConst.h"
#include "view/task/TaskFollowMediator.h"
#include "utils/ScaleUtil.h"
#include "utils/ConvertUtil.h"
#include "mvc/Facade.h"
#include "view/mainUI/MainUIMediator.h"
#include "control/AppFacade.h"
#include "view/mainUI/components/MainNavigate.h"

const int LEAD_AROW_TAG = 101;
ObjectGlow::ObjectGlow( CCNode *pObject, int loc_type, CCNode *pObjectParent /*= NULL*/, 
	int arrow_dir, string info, bool isFlyEff /*= false*/, CCPoint arrowPos)
{
	_pLead = 0;
	_pRect = 0;
	_pObject = 0;
	//_pObjectParent = 0;

	_pObject = pObject;
	//_pObjectParent = pObjectParent;
	_loc_type = loc_type;
	_arraw_dir = arrow_dir;
	_info = info;
	_isFlyEff = isFlyEff;
	//_type = type;
	_arrowPos = arrowPos;

	/*if(!_pObjectParent)
	{
		_pObjectParent = LayerManager::newhandLayer;
	}*/

	/*if(pObject == NULL)
	{
		return;
	}*/

	//switch(_type)
	//{
	//case TYPE_1:
	//	//if(_ob.parent is MainNavigate || _ob is WorldExit
	//	initFilter(2);
	//	//GlobalEnterFrame.getInstance().addFrameHandle(onStep);
	//	break;

	//case TYPE_2:
	//	//if(_ob is SimpleButton || _ob is ChildExit  || _ob is FormationClip)
	//	initFilter(0);
	//	//GlobalEnterFrame.getInstance().addFrameHandle(onStep);
	//	break;

	//case TYPE_3:
	//	//if(root is CrystalView)
	//	initFilter(1);
	//	_pRect = CCSprite::spriteWithFile("Icon.png");
	//	/*_rect.graphics.lineStyle(2, _lineColor);
	//	_rect.graphics.drawRoundRect(0, 0, _ob.height, _ob.height + 12, 20, 20);
	//	_rect.graphics.endFill();
	//	_rect.mouseEnabled = false;*/
	//	paintToRoot(pObjectParent);
	//	break;

	//case TYPE_4:
	//	//if((_ob is TextField || _ob is DisplayObject) && _ob.parent)
	//	initFilter(1);
	//	/*if(_ob is TaskItem || _ob is ShopItem || _ob is TaskOperationItem){
	//		_rectW = Math.min(_ob.width-31, _ob.textWidth) + 30;
	//		_rectH = _ob.height + 6;
	//	}
	//	else{
	//		_rectW = _ob.width;
	//		_rectH = _ob.height + 2;
	//	}*/
	//	_pRect = CCSprite::spriteWithFile("Icon.png");
	//	/*_rect.graphics.lineStyle(2, _lineColor);
	//	_rect.graphics.drawRoundRect(0, 0, _rectW, _rectH, 5,5);
	//	_rect.graphics.endFill();
	//	_rect.mouseEnabled = false;*/
	//	/*if(_ob is TextField){
	//	_rect.graphics.beginFill(0x000000, 0);
	//	_rect.graphics.drawRoundRect(0, 0, _rectW, _rectH, 5,5);
	//	_rect.graphics.endFill();
	//	_rect.mouseEnabled = true;
	//	_rect.mouseChildren = false;
	//	_rect.buttonMode = true;
	//	_rect.addEventListener(MouseEvent.MOUSE_DOWN, onRectMouseDown);
	//	}
	//	if(!root){
	//	root = LayerManager.newhandLayer;
	//	}*/
	//	paintToRoot(pObjectParent);

	//	if(isFlyEff){
	//		/*_flyEff = Reflection.createInstance("lead_task");
	//		_flyEff.x = _rect.x + _rectW/2;
	//		_flyEff.y = _rect.y + _rectH/2;
	//		_flyEff.mouseEnabled = false;
	//		_flyEff.mouseChildren = false;
	//		root.addChild(_flyEff);*/
	//	}
	//	break;

	//default:
	//	break;
	//}

	if(loc_type != 0){
		drawLeadArrow(loc_type, LayerManager::newhandLayer, arrow_dir, info);
	}
	/*if(root ==null || root == LayerManager.newhandLayer){
	StageProxy.addListener(onResizeHandle);
	}*/
}

void ObjectGlow::initFilter( int type /*= 0*/ )
{

}

void ObjectGlow::paintToRoot( CCNode *pParentNode )
{
	if(_pRect)
	{
		if(_pRect->getParent())
		{
			_pRect->removeFromParentAndCleanup(false);
		}

		_pRect->setAnchorPoint(CCPointZero);
		_pRect->setPosition(_pObject->getPosition());
		pParentNode->addChild(_pRect);
	}
}

void ObjectGlow::drawLeadArrow( int loc_type, CCNode *pObjectParent, int arrow_dir, string info )
{
	/*
	 * Fix here
	 * By Doyang. At 20120528
	 * Don't use coordinate.
	 */

	int *coordinate = getCoordinate(loc_type, pObjectParent, arrow_dir);
	if(loc_type == NewhandConst::LOC_TASK){
		/*if(_ob is SimpleButton){
			info = LangManager.getText("NHD001");
		}
		else if(_ob is CustomTabBar){
			if(_ob.getIndex()==0){
				info = LangManager.getText("NHD002");
			}
			else{
				info = LangManager.getText("NHD003");
			}
		}*/
		// disabled by LH 20120912
		//info = " ";
	}

	_pLead = new LeadArrow(coordinate[0], coordinate[1], coordinate[2], info);
    
    CC_SAFE_DELETE(coordinate);
    
	//_pLead = new LeadArrow(coordinate[0], _arrowPos.x, _arrowPos.y, info);
	_pLead->setTag(LEAD_AROW_TAG);
	if(pObjectParent)
	{
		//var des_p:Point = root.globalToLocal(new Point(_lead.x, _lead.y));
		//_lead.x = des_p.x;
		//_lead.y = des_p.y;
		pObjectParent->addChild(_pLead);
	}
	else
	{
		LayerManager::newhandLayer->addChild(_pLead);
	}
	_pLead->release();
}

int *ObjectGlow::getCoordinate( int loc_type, CCNode *pObjectParent, int arrow_dir )
{
	int *coordinate = new int[3];
	int dir = arrow_dir;//dx, dy, 
	CCPoint tempPos = ConvertUtil::convertToScreenPos(_pObject);
	/*CCPoint tempPos2 = CCPointZero;
	CCPoint tempPos = CCPointZero;
	CCRect rect = _pObject->boundingBox();
	if(_pObject && _pObject->getParent())
	{
		tempPos = _pObject->getParent()->convertToWorldSpace(_pObject->getPosition());
		tempPos2 = _pObject->getParent()->convertToNodeSpace(_pObject->getPosition());
	}*/
	switch(loc_type){
	case NewhandConst::LOC_TASK:
		{
			if(arrow_dir == 15)
			{
				//// Equals _ob is CustomTabBar
				//// Show taskFollowView list.
				//GameDispatcher::getInstance()->dispatchEvent(TaskFollowMediator::SHOW_TASK_FOLLOW_LIST, NULL);

				tempPos = POS(ccp(750, 550), ScaleUtil::TOP_RIGHT);
				dir = 11;
			}
			else 
			{
				
			}
		}
		
		/*if(_ob is SimpleButton){
			dx = StageProxy.width - 254;
			dy = 175;
			dir = 11;
		}
		else if(_ob is CustomTabBar){
			dx = StageProxy.width - 390;
			dy = 175;
			dir = 11;
			if(_ob.getIndex()==0){
				dx += 60;
			}
		}
		else{
			dx = StageProxy.width - 235;
			dy = 275 + _ob.y;
			dir = 15;
		}*/
		break;
	case NewhandConst::LOC_MAIN:
		{
			//tempPos = POS(ccp(780, 192), ScaleUtil::BOTTOM_RIGHT);
			float x = 0;
			float y = 0;
			CCPoint endPoint = POS(ccp(850, 120), ScaleUtil::BOTTOM_RIGHT);
			MainUIMediator *pMediator = (MainUIMediator *) g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
			if(pMediator 
				&& pMediator->_buttomView 
				&& pMediator->_buttomView->_mainNavigateX)
			{
				x = endPoint.x - (pMediator->_buttomView->_mainNavigateX->m_btnCount * POSX(90.0f)) + POSX(20) + _pObject->boundingBox().origin.x;
				y = tempPos.y + _pObject->boundingBox().size.height + POSX(100);
			}
			else
			{
				x = tempPos.x;
				y = tempPos.y;
			}
			tempPos.x = x;
			tempPos.y = y;
			dir = 12;	
		}
		/*dx = StageProxy.width + _ob.x - 162;
		dy = StageProxy.height - 185;
		dir = 12;*/

		break;
	case NewhandConst::LOC_CD:
		{
			dir = 13;
		}
		/*dx = _ob.width;
		dy = _ob.y + 165;
		dir = 13*/
			break;
	case NewhandConst::LOC_SEC:
		{
			dir = 15;
		}
		/*dx = StageProxy.width - 180 + _ob.x - 138 - 90;
		dy = 130;
		dir = 15;*/
		break;
	case NewhandConst::LOC_MAP:
		{
			

			/*dx = StageProxy.width - 220 - _ob.width;
			dy = _ob.y + _ob.height/2 -13;*/
			dir = 11;
		}
		break;
	case NewhandConst::LOC_WORLD:
		{
			//tempPos = POS(ccp(860, 140), ScaleUtil::CENTER_BOTTOM);
		}
		break;
	case NewhandConst::LOC_CHILD:
		{
			//tempPos = POS(ccp(860, 140), ScaleUtil::CENTER_BOTTOM);
		}
		break;
	case NewhandConst::LOC_POP:
		{

			switch(dir){
			case 11://49
				
				/*if(_ob is WorldExit){
					dx = p.x - 260;
					dy = p.y -13;
				}
				else if(_ob is ChildExit){
					dx = p.x - 245;
					dy = p.y -88;
				}else{
					dx = p.x - 220;
					dy = p.y + _ob.height/2 -13;
					}*/
				tempPos.x -= POSX(110);
				tempPos.y -= POSX(10);
				//tempPos = POS(ccp(860, 140), ScaleUtil::CENTER_BOTTOM);
				break;
			case 12:
				/*dx = p.x - 162 + w;
				dy = p.y - 106;*/
				break;
			case 13:
				tempPos.x += POSX(100);
				/*dx = p.x + w + 45;
				dy = p.y + _ob.height + 20;*/
				break;
			case 14:
				tempPos.x += POSX(50);
				tempPos.y -= POSX(70);
				/*dx = p.x + w - 13;
				dy = p.y + _ob.height + 50;*/
				break;
			case 15:
				/*dx = p.x - 165 + w;
				dy = p.y + _ob.height + 50;*/
				break;
			case 32://布阵--从上到下拖动人物的指引箭头
				tempPos.y += _pObject->boundingBox().size.height / 2;
				/*dx = p.x;
				dy = p.y + _ob.height/2;*/
				break;
			}
			dir = arrow_dir;
		}
		break;

	case NewhandConst::LOC_VSCROLL:
		{
			tempPos.x += POSX(240 - 50);
			tempPos.y += POSX(50);
			dir = 16;
		}
		break;
	default:
		{
			//tempPos = _arrowPos;
			tempPos.x -= POSX(110);
			tempPos.y -= POSX(20);
			dir = 11;
		}
		break;
	}
	coordinate[0] = dir;
	coordinate[1] = tempPos.x;
	coordinate[2] = tempPos.y;
	return coordinate;
}

void ObjectGlow::stopAndClear()
{
	/*GlobalEnterFrame.getInstance().removeFrameHandle(onStepRect);
	GlobalEnterFrame.getInstance().removeFrameHandle(onStep);
	StageProxy.removeListener(onResizeHandle);
	if(_rect && _rect.parent){
		if(_rect.hasEventListener(MouseEvent.MOUSE_DOWN)){
			_rect.removeEventListener(MouseEvent.MOUSE_DOWN, onRectMouseDown);
		}
		_rect.parent.removeChild(_rect);
		_rect = null;
	}
	else{
		_ob.filters = [];
		_ob = null;
	}
	if(_lead && _lead.parent){
		_lead.parent.removeChild(_lead);
		_lead.dispose();
		_lead = null;
	}
	if(_flyEff){
		_flyEff.parent.removeChild(_flyEff);
		_flyEff = null;
	}*/

	if (LayerManager::newhandLayer->getChildByTag(LEAD_AROW_TAG))
	{
		LayerManager::newhandLayer->removeChildByTag(LEAD_AROW_TAG, true);
	}
	/*if(_pLead && _pObjectParent)
	{
		_pObjectParent->removeChildByTag(LEAD_AROW_TAG, true);
		_pLead = 0;
	}*/
}

