#include "MineBg.h"
#include "MineView.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"

MineBg::CELLPOINT MineBg::p2r_x(int x, int y)//ͼƬ���������Ӧ�߼�����IDX
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

	//������ͼ
	char mappicName[100];
	int xIndex = 0;
	int yIndex = 0;
	for (int i = 0; i < MineBgCellMax; i++)
	{
		xIndex = i/MineBgCellCnt_x;
		yIndex = i%MineBgCellCnt_x;
		//�½�����
		sprintf(mappicName, "assets/ui/silvermine/map/%d_%d.jpg",yIndex, xIndex);
		SpriteNode* ps = new SpriteNode();
		if (!ps->initWithFile(mappicName))
		{}
		this->addChild(ps, 0);
		ps->release();
		ps->setAnchorPoint(ccp(0, 0));
		ps->setPosition(ccp(0, 0));
		//���鸳ֵ
		CELLPOINT posIdx = p2r_x(yIndex, xIndex);
		m_picArr[posIdx.x][posIdx.y] = ps;
		//��������
		CCPoint pos = posIdx.localCellPos();
		m_picArr[posIdx.x][posIdx.y]->setPosition(ccp(POSX(pos.x), POSX(pos.y)));
	}

	return true;
}