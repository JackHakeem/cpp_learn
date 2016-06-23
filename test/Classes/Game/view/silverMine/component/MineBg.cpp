#include "MineBg.h"
#include "MineView.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"

MineBg::CELLPOINT MineBg::p2r_x(int x, int y)//图片名字坐标对应逻辑坐标IDX
{
	return CELLPOINT(x, MineBgCellCnt_y-y-1);
}

MineBg::MineBg()
{
	for (int i = 0; i < MineBgCellCnt_x; i++)
	{
		for (int j = 0; j < MineBgCellCnt_y; j++)
			m_picArr[i][j] = 0;
	}
}

MineBg::~MineBg()
{}


bool MineBg::init()
{
	if (!LayerNode::init())
		return false;

	//背景地图
	char mappicName[100];
	int xIndex = 0;
	int yIndex = 0;
	for (int i = 0; i < MineBgCellMax; i++)
	{
		xIndex = i/MineBgCellCnt_x;
		yIndex = i%MineBgCellCnt_x;
		//新建精灵
		sprintf(mappicName, "assets/ui/silvermine/map/%d_%d.jpg",yIndex, xIndex);
		SpriteNode* ps = new SpriteNode();
		if (!ps->initWithFile(mappicName))
		{}
		this->addChild(ps, 0);
		ps->release();
		ps->setAnchorPoint(ccp(0, 0));
		ps->setPosition(ccp(0, 0));
		//数组赋值
		CELLPOINT posIdx = p2r_x(yIndex, xIndex);
		m_picArr[posIdx.x][posIdx.y] = ps;
		//本地坐标
		CCPoint pos = posIdx.localCellPos();
		m_picArr[posIdx.x][posIdx.y]->setPosition(ccp(POSX(pos.x), POSX(pos.y)));
	}

	return true;
}