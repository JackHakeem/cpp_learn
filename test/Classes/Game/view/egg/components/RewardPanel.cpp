#include "RewardPanel.h"
#include "KKLabelTTF.h"
#include "manager/LangManager.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "model/egg/EggProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "GoodsItem.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LayerManager.h"
#include "control/AppFacade.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "view/egg/EggMediator.h"
#include "model/backpack/GoodsManager.h"
#include "utils/ColorUtil.h"
#include "events/GameDispatcher.h"
#include "utils/ColorUtil.h"
#include "model/backpack/GoodsManager.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "ChangeQuality.h"
#include "model/egg/EggManager.h"
#include "ChangeSmallType.h"
#include "model/config/ConfigManager.h"

const float FontSize = 20.0f;
const float w_frame_label = 300;

RewardPanel::RewardPanel()
{
	_paneContianer = 0;
}

RewardPanel::~RewardPanel()
{}

bool RewardPanel::init()
{
	if (!LayerNode::init())
		return false;

	_paneContianer = new LayerNode();
	_paneContianer->init();
	this->addChild(_paneContianer, 0);
	_paneContianer->release();


	return true;
}

/**
	* ������ʷ��Ը������
	* @param arr	��ʷ��Ը�Ľ�������
	* 
	*/		
void RewardPanel::updateContianer(std::vector<EggInfo> arr)
{
	_paneContianer->removeAllChildrenWithCleanup(true);

	float height = 0;
	int size = arr.size();
	//if (size > 3)
	//	size = 3;
	int ssize = size-3;
	if (ssize < 0)
		ssize = 0;

	for(int i = ssize; i < size; i++)
	{ 
		EggInfo egg = arr[i];

		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(FontSize, 26.0f, CCSizeMake(w_frame_label, 120));
		//std::string sd = "sdfasdfasdfdd X 1";
		//pLabel->add(sd, ccc3(240, 240, 232));
		txtContent(pLabel, egg.state, egg.goodsId, egg.type, egg.quality, egg.num, egg.name);
		pLabel->setPosition(ccp(0, - height));
		_paneContianer->addChild(pLabel);
		pLabel->release();
		height += (pLabel->m_iRow+1)*pLabel->m_fFontRealHeight;
	}
			
	//_scrollPane.update();
	//if(_paneContianer.height > _scrollPane.height){
	//	_scrollPane.verticalScrollBar.visible=true;
	//}else{
	//	_scrollPane.verticalScrollBar.visible=false;
	//}
	//		
	//if(_paneContianer.height > _scrollPane.height) {
	//	_scrollPane.verticalScrollBar.scrollPosition = _scrollPane .verticalScrollBar.maxScrollPosition;
	//}
}

/**
	* ��ʷ������ÿһ����¼ 
	* @param state 	����״̬
	* @param goodsId 	��������ID/��ƷID
	* @param type		��������
	* @param quality	����Ʒ��
	* @param goodsNum  ��Ʒ����
	* @param name		�������
	* @return 		
	* 
	*/			
void RewardPanel::txtContent(KKLabelTTF* pkk, int state, int goodsId, int type, int quality, int goodsNum, std::string name)
{
//	var content:String = "";
	if(name != "")
	{
		std::string content;
		char str[100];
		//
		sprintf(str, ValuesUtil::Instance()->getString("BCS004").c_str());
		content = str;
		pkk->add(content, ccc3(255, 0, 0));
		//
		pkk->add(name, ccc3(255, 211, 6));
		//
        std::string eggStr = ValuesUtil::Instance()->getString("EGG024");
		pkk->add(eggStr, ccc3(255, 255, 255));
		//
		ccColor3B color = ColorUtil::getGoodColor(g_pGoodsManager->getBasicGood(goodsId)->quality);
		sprintf(str, "%s x%d",g_pGoodsManager->getBasicGood(goodsId)->goodName.c_str(), goodsNum);
		content = str;
		pkk->add(content, color);
		//
		
	}
	else
	{
		if(type == 3)
		{//��Դ��
			std::string content;
			char str[100];
			//
			//sprintf(str, ValuesUtil::Instance()->getString("BCS004").c_str());
			//content = str;

			sprintf(str, "%d_%d", type, quality);
			ccColor3B color = ColorUtil::getGoodColor(ChangeQuality::getQuality(str));

			
			content = EggManager::Instance()->getEggTips(type,ChangeSmallType::smallType(goodsId), quality);

			vector<std::string> mapStr;
			ConfigManager::splitStringByCharacterEx( content, "|" , mapStr);
			if (mapStr.size() > 0)
				content = mapStr[0];

			sprintf(str, "%s x%d", content.c_str(), goodsNum);
			content = str;
			pkk->add(content, color);

		}
		else if(type == 2)
		{//Ӷ������Ӷ����

			// �����Ѵ򿪣���ʾ��ɫΪ�������ݵ���ɫ������δ�򿪣���ʾ����Ʒ������Ӧ����ɫ
			std::string content;
			char str[100];
			sprintf(str, "%d_%d", type, quality);
			ccColor3B color = (state == 1) ?
				ColorUtil::getGoodColor(g_pGoodsManager->getBasicGood(goodsId)->quality):
				ColorUtil::getGoodColor(ChangeQuality::getQuality(str));
				
			if (state == 1)
			{
				content = g_pGoodsManager->getBasicGood(goodsId)->goodName;
			}
			else
			{
				content = EggManager::Instance()->getEggTips(type, 0, quality);

				vector<std::string> mapStr;
				ConfigManager::splitStringByCharacterEx( content, "|" , mapStr);
				if (mapStr.size() > 0)
					content = mapStr[0];
			}
			// �����Ѵ򿪣���ʾ��ɫΪ�������ݵ����֣�����δ�򿪣���ʾ����Ʒ������Ӧ������
			sprintf(str, "%s x%d", content.c_str(), goodsNum);
			content = str;

			pkk->add(content, color);

		}
		else
		{
			std::string content;
			char str[100];
			ccColor3B color = ColorUtil::getGoodColor(quality);

			if (state == 1)
			{
				content = g_pGoodsManager->getBasicGood(goodsId)->goodName;
			}
			else
			{
				content = EggManager::Instance()->getEggTips(type, 0, quality);

				vector<std::string> mapStr;
				ConfigManager::splitStringByCharacterEx( content, "|" , mapStr);
				if (mapStr.size() > 0)
					content = mapStr[0];
			}

			// �����Ѵ򿪣���ʾ��ɫΪ�������ݵ����֣�����δ�򿪣���ʾ����Ʒ������Ӧ������
			sprintf(str, "%s x%d", content.c_str(), goodsNum);
			content = str;

			pkk->add(content, color);
		}
	}
	//return content;
}