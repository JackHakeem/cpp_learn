#ifndef _APPOINT_BLESS_VO_H_
#define _APPOINT_BLESS_VO_H_
/** 
 * @author shenzhiqiang
 * @version 1.1.4.0
 * @description  淘宝祝福值Vo
 * @data 2012-3-8 下午02:35:45 
 * 
 */ 
class AppointBlessVo
{
public:
	int goodsId;		// 物品原型ID
	int goodsType;		// 物品类型
	int blessValue;		// 兑换时需要的祝福值
	int crystalLev;		// 兑换时需要的命之水晶等级
};
#endif