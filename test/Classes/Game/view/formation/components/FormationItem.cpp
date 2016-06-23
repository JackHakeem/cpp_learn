#include "FormationItem.h"
#include "manager/ViewManager.h"



        /**
		* Decorate to formation of the character
		* @ param sitGrid formation position
		* @ param info PlayerInfoVo characters
		 * 
		 */		
 FormationItem::FormationItem( int sitGrid , PlayerInfoVo* info ):_mark(0),sitGrid(0),_figureId(0),_clickNum(0),isHasCopy(false),isMove(false)   //Initialize member list
{
	if (!info)
	{
		CCLog("error  FormationItem::FormationItem( int sitGrid , PlayerInfoVo* info )");
	}
	else
	{
		this->sitGrid=sitGrid;
		this->_figureId=info->playerBaseInfo.id;
		//this->_mark->initWithFile("assets/ui/formation/9.png");
		//this->_mark->setPosition(ccp(1024/2,768/2));   //Should use sitGird to get coordinates die a coordinate array write FormationPoint [9]
		//ViewManager::getInstance()->formationView->_panel->addChild(_mark );  //Added to the formation of the panel

		 initHeadInfo(info->playerBaseInfo, info->figureBaseInfo );
	}



	 ///////add listen


}

  

      /**
		 Head, head of the increase under the name, message that the IPAD version see specific needs
		 * @param playerBase
		 * @param figureBase
		 * 
		 */	

void FormationItem::initHeadInfo( PlayerBaseVo playerBase, FigureBaseVo figureBase )
{	
	// int cloth = playerBase.cloth;

}

