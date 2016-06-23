#pragma once

#include "BaseType.h"
#include "model/egg/vo/EggInfo.h"
#include "utils/TipBase.h"


class GameDispatcher;
class TipHelps;

class GoodsItem:public LayerNode, public TipBase
{
public:
	GoodsItem();
	~GoodsItem();

	bool init();
	void addGoods(EggInfo egg);
	void setNum(int num);
	void setIcon(int state, int type, int smallType, int quality);
	void updateGoods(int goodsId, int goodsNum);
	void onTimer(CCObject* pSender);
	void setTips(int state, int type, int smallType, int quality);
public:
	GameDispatcher* _dispatcher;
	int _itemType;// ��Ʒ������ͣ������Ǳ�����Ļ��Ǵ����ģ�1���䣬2������

	int _eggId;		// ����Id
	std::string _eggName;	// ��������
	int _type;			// ��������
	int _smallType;		// ����С��
	int _state;		    // ����״̬
	int _quality;		// ����Ʒ��
	int _num;			// �����ѵ���
	int _goodsId;		// ���������ƷId
	int _goodsNum;		// ���������Ʒ����
	
	bool _isSelect;	// �Ƿ񱻵��ѡ��
	int _clickNum;	// ������Ĵ���

	CCLabelTTF* _txtNum;

	CCMenu* _pic;
	LayerNode* _icon;// ͼƬ����

	CCSize _frameContentSize;
	TipHelps* _tips;
};