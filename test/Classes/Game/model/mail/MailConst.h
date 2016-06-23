#pragma once

class MailConst
{
public:
	MailConst()
	{
	}
	/*定义邮件类型*/
	static const unsigned int MAIL_TYPE_ALL		=	0;	//全部
	static const unsigned int MAIL_TYPE_PLAYER	=	1;	//玩家
	static const unsigned int MAIL_TYPE_SYSTEM	=	2;	//系统

	/*定义邮件状态*/	
	static const unsigned int MAIL_STATUS_UNREAD	=	1;	//未读
	static const unsigned int MAIL_STATUS_READED	=	2;	//已读

	//附件id类型
	static const unsigned int GOLD_ITEM_ID		=	1;	// 金币礼包物品Id
	static const unsigned int SILVER_ITEM_ID		=	2;	// 银币礼包物品Id
	static const unsigned int PRACTICE_ITEM_ID	=	3;	// 历练
	static const unsigned int POPULARITY_ITEM_ID	=	4;	// 名声
	static const unsigned int EXP_ITEM_ID		=	5;	// 经验
	static const unsigned int VIGOUR_ITEM_ID		=	6;	// 精力
	static const unsigned int ENCHANT_ITEM_ID		=	7;	// 魔晶石
	static const unsigned int OTHER_ITEM_ID		=	99;	// 其它可在包裹中显示的物品ID都大于该值

	//附件状态	
	static const unsigned int ATTACH_STATUS_NULL		=	0;	// 0无附件
	static const unsigned int ATTACH_STATUS_UNLOAD	=	1;	// 1未领取
	static const unsigned int ATTACH_STATUS_LOADED	=	2;	// 2已领取
	static const unsigned int ATTACH_STATUS_LOADING	=	3;	// 3申请领取中

	//邮件错误
	static const unsigned int ERR_MAIL_SEND_FAILED	= 101;		// 邮件发送失败
	static const unsigned int ERR_MAIL_DEL_FAILED		= 102;		// 邮件删除失败
	static const unsigned int ERR_MAIL_GET_DETAIL_FAILED	= 103;	// 获取邮件详情失败
	static const unsigned int ERR_MAIL_RECVER_NOEXIST	= 104;		// 收件人不存在

protected:
private:
};