#ifndef _GOODS_VIEW_H_
#define _GOODS_VIEW_H_
#include "LayerNode.h"
#include "utils/TipBase.h"
#include "model/appoint/vo/GoodsVo.h"
#include "utils/TipHelps.h"

class GoodsView : public LayerNode, public TipBase 
{
public:
	GoodsView(GoodsVo *pGoodsVo, bool isAppointBlessView = false);
	~GoodsView();

	void initGrid();
	void dispose();
	void onGoodsItemClick(CCObject *pSender);
	void timerStep();
	void doubleClick();
	
	bool _isAppointBlessView;
	GoodsVo *goodsVo;				//��Ʒֵ����
private:
	//_grid:MovieClip;				//��Ʒ��������
	//_pic:PicLoadingContent = null;		//����ͷ��
	TipHelps *_popTip;				//��ͣ��ʾ��Ϣ
	//_timer:Timer = null;				//˫����ʱ��
	int _numClick;					//˫��������
};
#endif