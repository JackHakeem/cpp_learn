#include "ceView.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"

ceView::ceView()
{
	for (int i = 0; i < CETEXMEMSIZE; i++)
		m_pTexMem[i] = 0;
	
	pbg = 0;
	progress = 0;
}

ceView::~ceView()
{}

bool ceView::init()
{
	if (!LayerNode::init())
		return false;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	pbg = cocos2d::CCLayerColor::layerWithColorWidthHeight(ccc4(0, 255, 0, 100), winSize.width, winSize.height); 
	this->addChild(pbg, 0, 1);
	pbg->setPosition(ccp(0, 0));

	for (int i = 0; i < CETEXMEMSIZE; i++)
	{
		//name
		//char str[CETEXMEMSIZE];
		//sprintf(str, "tex: %ld textures,for %lu KB (%.2f MB)", (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f*1024.0f));
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(" ", CCSizeMake(POSX(960/2), POSX(50)), CCTextAlignmentLeft, "Arial", POSX(15));
		pLabel->setPosition(ccp((i>=(CETEXMEMSIZE/2))?POSX(960/2):0, (i>=(CETEXMEMSIZE/2))?(POSX(50)*(i-(CETEXMEMSIZE/2))+ POSX(140)):(POSX(50)*i+ POSX(140))));
		pLabel->setAnchorPoint(ccp(0, 0));
		pbg->addChild(pLabel, 1, i);
		if (i%2==0)
			pLabel->setColor(ccc3(0, 0, 200));
		else
			pLabel->setColor(ccc3(200, 0, 0));

		m_pTexMem[i] = pLabel;
		
	}

	progress = 0;




	//X
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(ceView::clickShow) );
		_btnX->setPosition(ccp(winSize.width-_btnX->getContentSize().width/2, 
			winSize.height/2-_btnX->getContentSize().height/2));


		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->addChild(_btnX, 0, 0);
		buttonMenu->setPosition(ccp(0, 0));
		buttonMenu->setTouchLayer(TLE::IntervalLayer_zx-1);
		this->addChild(buttonMenu, 5);
		buttonMenu->release();
	}

//	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(ceView::update),this,2.0f,false);
	return true;
}

void ceView::cleanStrs()
{
	progress = 0;
	for (int i = 0; i < CETEXMEMSIZE; i++)
	{
		m_pTexMem[i]->setString(" ");
	}
}

void ceView::clickShow(CCObject* pSender)
{
	if (pbg)
		pbg->setIsVisible(!pbg->getIsVisible());
}

void ceView::insertNode(char* str)
{
	m_pTexMem[progress]->setString(str);

	progress++;
	if (progress >= CETEXMEMSIZE)
		progress = 0;
}

void ceView::update(float dt)
{
	//CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	//if (m_pTexMem)
	{
		CCMutableDictionary<std::string, CCTexture2D*> * pTextures = CCTextureCache::sharedTextureCache()->m_pTextures;
	
		unsigned int count = 0;
		unsigned int totalBytes = 0;

		vector<string> keys = pTextures->allKeys();
		vector<string>::iterator iter;
		int countTag = 1;
		char str[400];
		for (int i = 0 ; i < CETEXMEMSIZE; i++)
			m_pTexMem[i]->setString("c");

		for (iter = keys.begin(); iter != keys.end(); iter++, countTag++)
		{
			CCTexture2D *tex = pTextures->objectForKey(*iter);
			unsigned int bpp = tex->bitsPerPixelForFormat();
			// Each texture takes up width * height * bytesPerPixel bytes.
			unsigned int bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
			totalBytes += bytes;
			count++;

			
			if (countTag <  CETEXMEMSIZE)
			{
				sprintf(str, "\"%s\" rc=%lu  => %lu KB",//id=%lu %lu x %lu @ %ld bpp
						(*iter).c_str(),
						(long)tex->retainCount(),
						//(long)tex->getName(),
						//(long)tex->getPixelsWide(),
						//(long)tex->getPixelsHigh(),
						//(long)bpp,
						(long)bytes / 1024
						);

				/*CCLog("cocos2d: \"%s\" ", (*iter).c_str());*/
			
				m_pTexMem[countTag]->setString(str);			
			}

		}

		//char str[CETEXMEMSIZE];
		sprintf(str, "tex: %ld textures, %lu KB", (long)count, (long)totalBytes / 1024);
		m_pTexMem[0]->setString(str);
	}
}