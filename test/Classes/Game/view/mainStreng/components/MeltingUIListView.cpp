#include "MeltingUIListView.h"
#include <cmath>
static int State_Touch = 1;
static int State_Move = 2;
static int State_End = 3;

MeltingUIListView* MeltingUIListView::listViewWithCCRect( const CCRect& mRect, bool isHorizontal )
{
	MeltingUIListView *pListView = new MeltingUIListView();
	if(pListView)
	{
		pListView->setIsLockHorizontal(isHorizontal);
		pListView->setRect(mRect);
		pListView->init();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}


MeltingUIListView::MeltingUIListView()
{
	m_fStep = 0.0f;
	m_bDraded = false;
	m_pClickGood = 0;
	m_fYMove = 0.0f;
}

bool MeltingUIListView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	m_fStep = 0.0f;
	m_bDraded = false;
	m_pClickGood = 0;
	m_state = State_Touch;
	this->unschedule(schedule_selector(MeltingUIListView::update));

	CCMutableArray<LayerNode *>* pArray = getChilds();
	for ( int i = 0; i < pArray->count(); i++ )
	{
		LayerNode * item = (LayerNode *) pArray->getObjectAtIndex( i );
		if (item)
		{
			for ( int j = 0; j < 3; j++ )
			{
				MeltingBagGoods* pGood = (MeltingBagGoods*)item->getChildByTag(j);

				if ( pGood )
				{
					CCPoint itemPoint = getScreenPos(pGood);
					CCSize itemSize = pGood->getContentSize();
					CCPoint locationInView = pTouch->locationInView(pTouch->view());
					CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
					if ( CCRect::CCRectContainsPoint(CCRectMake(itemPoint.x,itemPoint.y, itemSize.width,itemSize.height), currentTouchPoint) )
					{
						m_pTouch = pTouch;
						m_pEvent = pEvent;

						m_pClickGood = pGood;
						this->schedule(schedule_selector(MeltingUIListView::update), 0);
						break;
					}
				}				
			}
			
		}
	}	

	return CCUIListView::ccTouchBegan(pTouch, pEvent);
}

void MeltingUIListView::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

    if (abs(touchPoint.y - preTouchPoint.y) < 5)
    {
        return;                
    }
	m_state = State_Move;

	this->unschedule(schedule_selector(MeltingUIListView::update));
	m_fStep = 0.0f;

	if (m_bDraded)
	{
		//int id = getTouchItemId();
		//LayerNode * item = (LayerNode *) getChilds()->getObjectAtIndex( id );
		if(!m_pClickGood)
			return;
		m_pClickGood->ccTouchMoved(pTouch, pEvent);
	} 
	else
	{
		//CCPoint locationInView = pTouch->locationInView(pTouch->view());
		//CCPoint currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
		//locationInView = pTouch->previousLocationInView(pTouch->view());
		//CCPoint preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
		//m_fYMove = ccpSub( currentTouchPoint, preTouchPoint ).y;

		CCUIListView::ccTouchMoved(pTouch, pEvent);
	}
}

void MeltingUIListView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	m_state = State_End;
	if (m_bDraded)
	{
		if( m_pClickGood )
		{
			return m_pClickGood->ccTouchEnded(pTouch, pEvent);
		}
	}
	else
		CCUIListView::ccTouchEnded(pTouch, pEvent);
}

void MeltingUIListView::onItemClick( int position )
{


	CCUIListView::onItemClick(position);
}

void MeltingUIListView::update( ccTime dt )
{
	if ( m_state == State_Touch )
	{
		m_fStep += dt;
		if ( m_fStep > 0.1f )
		{
			m_pClickGood->ccTouchBegan(m_pTouch, m_pEvent);

			this->unschedule(schedule_selector(MeltingUIListView::update));
			m_fStep = 0.0f;
			m_bDraded = true;
		}
	}
	
}
