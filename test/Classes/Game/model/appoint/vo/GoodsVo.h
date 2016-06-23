#ifndef _GOODS_VO_H_
#define _GOODS_VO_H_

class GoodsVo
{
public:
	int id;					//物品id
	std::string	icon;			//物品图片
	std::string info;			//物品提示信息
	int quality;			//物品品质
	int sellPrice;			//出售价格
};
#endif