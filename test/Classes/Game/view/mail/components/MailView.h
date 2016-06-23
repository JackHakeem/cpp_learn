#pragma once
#include "cocos2d.h"
#include "PopContainer.h"
#include "model/mail/vo/MailContentVo.h"

USING_NS_CC;

class MailView : public PopContainer
{
public:
	MailView();
	~MailView();
	virtual bool init();

public:
	void initView();
	void loadBackGround();
	void loadTabButton();
	void loadMailListPanel();
	void loadWritePanel();
	void loadReadPanel();
	void loadButtons();

	void setMailListContent(int mailtype);

	void onAllMailTabClick(CCObject * pSender);
	void onSysMailTabClick(CCObject * pSender);
	void onPlayerMailTabClick(CCObject * pSender);
	void onWriteMail(CCObject * pSender);
	void onDeleteAllMails(CCObject * pSender);
	void onDeleteMail(CCObject * pSender);
	void onReplyMail(CCObject * pSender);
	void onSendMail(CCObject * pSender);
	void onReturn(CCObject * pSender);

	void onDeleteConfirm(CCObject * pSender);
	void onDeleteOK(CCObject * pSender);
	void onClickCancel(CCObject * pSender);

	void enableButton(int tag, bool var);
	void setTabBtnAndScrollState(bool a[]);
	void enableInput(bool var1,bool var2,bool var3);

	void resetWritePanel(MailContentVo contentVo);
	void resetReadPanel(MailContentVo contentVo);
	void resetScrollPage(int mailtype);

	void requestMailCount(int type);
	void requestMailList(int type);

	void setMailId(uint32 mailId);
	void setCurPage(uint32 page);
	void setPageText(int curPage,int totalPage);
	void showReadLayer();
	void showHightLight(bool var,CCPoint pos);

	std::string getTimeStringByMili(const time_t * time);
	
public:
	enum
	{
		TAG_MenuItemImage,
	};

	enum
	{
		TAG_Container = 0,

		TAG_Button_Menu_AllMail = 101,
		TAG_Button_Menu_SysMail,
		TAG_Button_Menu_PlayerMail,

		TAG_Button_Menu_DelAllMail,
		TAG_Button_Menu_Write,
		TAG_Button_Menu_Send,
		TAG_Button_Menu_Return,
		TAG_Button_Menu_DelMail,
		TAG_Button_Menu_Reply,
		TAG_Button_Menu_Attach,
		TAG_Page_LabelText,

		TAG_BtnImage_DelSingle = 151,
		TAG_BtnImage_DelAll,

		TAG_HightLight = 200,

		TAG_AllMail_ScrollView = 201,
		TAG_SysMail_ScrollView,
		TAG_PlayerMail_ScrollView,
		TAG_Write_ContentLayer,
		TAG_Read_ContentLayer,
	};

	enum
	{
		Z_Back,
		Z_Tab_Btn,
		Z_ContentLayer,
		Z_Scroll,
	};

	enum
	{
		TAG_Name_TextFeild = 51,
		TAG_Date_TextFeild,
		TAG_Title_TextFeild,
		TAG_Content_TextFeild,
	};

public:
	CCSize _winSize;
	CCPoint _listPos;
	CCPoint _writeReadPos;
	uint _curMailId;
	uint _curMailTab;
	uint _curPage;
	bool _isDeleteAll;
	bool _isTabClick;

protected:
private:

};