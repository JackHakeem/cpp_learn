//
//  Connect91Handler.m
//  HEBI
//
//  Created by 揭浩英 on 12-6-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Connect91Handler.h"
#include "cocos2d.h"
#include "LoginManage.h"
#include "utils/http/ghttp.h"

USING_NS_CC;

#define CONNECT91_AppId 101128//100336
#define CONNECT91_AppKey @"2428f3a3a8eb1923108aed6c33137a702bc7ff49cac9b96b"//@"31ac593cb8a332ca9e9345434eb57730cc33081fbf62e5f7"

@implementation Connect91Handler

static Connect91Handler *_sharedTo91 = nil;

+ (Connect91Handler *)sharedTo91
{
	if (!_sharedTo91) {
		_sharedTo91 = [[self alloc] kkInit];
	}
	
	return _sharedTo91;
}

-(id) kkInit
{
	if( (self = [super init]) )
	{
        [Connect91Handler setAppId:CONNECT91_AppId AppKey:CONNECT91_AppKey ];
        [self registerLoginNotification];
        
        //设定平台为横屏或者竖屏
        [[NdComPlatform defaultPlatform] NdSetScreenOrientation:UIInterfaceOrientationLandscapeLeft];
        //设置是否自动旋转
        [[NdComPlatform defaultPlatform] NdSetAutoRotation:YES];
        
	}
	return self;
}

//在初始化过程中注册监听登录消息
-(void) registerLoginNotification
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSLoginProcess:) name:(NSString*)kNdCPLoginNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSNewMessageCount:) name:kNdCPNewMessageNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSLeaveComplatformUI:) name:(NSString *)kNdCPLeavePlatformNotification object:nil];
}

/**
 @brief !!!:监听消息数更新
 */
- (void)SNSNewMessageCount:(NSNotification*)notify
{
    //	NSDictionary *dict = [notify userInfo];
    //	int nMsg = [[dict objectForKey:@"newMsgCount"] intValue];
    //	int nMsgSys = [[dict objectForKey:@"newSysMsgCount"] intValue];
	
    //[self updateNewMessageCountTip];
}

/**
 @brief !!!:离开平台界面
 */
- (void)SNSLeaveComplatformUI:(NSNotification*)notify
{
	NSLog(@"SNSLeaveComplatformUI %@",[notify description]);
}

//调用检查更新接口
-(void) versionUpdateCheck
{
    int nRes = [[NdComPlatform defaultPlatform] NdAppVersionUpdate:0 delegate:self];
    cocos2d::CCLog("versionUpdateCheck rnt=%d", nRes);
}

- (void)appVersionUpdateDidFinish:(ND_APP_UPDATE_RESULT)updateResult
{
    NSString *title = nil;
    NSLog(@"update result:%d", updateResult);
    switch (updateResult) 
    {
        case ND_APP_UPDATE_NO_NEW_VERSION:
            title = @"无可用更新"; 
            break;          
        case ND_APP_UPDATE_FORCE_UPDATE_CANCEL_BY_USER: 
            title = @"下载强制更新被取消";
            break;
        case ND_APP_UPDATE_NORMAL_UPDATE_CANCEL_BY_USER:
            title = @"下载普通更新被取消"; 
            break;
        case ND_APP_UPDATE_NEW_VERSION_DOWNLOAD_FAIL: 
            title = @"下载新版本失败";
            break;
        case ND_APP_UPDATE_CHECK_NEW_VERSION_FAIL:
            title = @"检测新版本信息失败";
            break;
        default:
            break; 
    }
    //无可用更新程序继续,其他情况demo暂不做特殊处理
    if (updateResult == ND_APP_UPDATE_NO_NEW_VERSION )
    {
        //开始登录以及应用相关的操作 
          [self login91];
    }
    else
    {
        exit(0);
    }
}
//登录 
-(void)login91
{
   //[[NdComPlatform defaultPlatform] NdSetDebugMode:0]; //debug
    [[NdComPlatform defaultPlatform] NdLogin:0];
    //[Connect91Handler switchAccount];
}

//实现响应方法
- (void) SNSLoginProcess:(NSNotification *)notify
{
    NSDictionary *dict = [notify userInfo];
    BOOL success = [[dict objectForKey:@"result"] boolValue];
    int error = [[dict objectForKey:@"error"] intValue];
    
    if (error == ND_COM_PLATFORM_ERROR_USER_CANCEL)
    {
        //用户取消登录和和相应处理
        [self login91];
        return;
    }
    if([[NdComPlatform defaultPlatform] isLogined] && success)
    {
        //用户登录成功后相应操作 
        NSString* pStrAccount = [[NdComPlatform defaultPlatform] loginUin];
        const char* strAccount;
        strAccount = [pStrAccount UTF8String];
      //  cocos2d::CCLog("%s", strAccount);
        char str[100];
        NSUInteger strsize = [pStrAccount length];
        memcpy(str, strAccount, strsize);
        str[strsize] = '\0';
        //cocos2d::CCLog("...............登陆成功.............token是:%s", str);
        CCLOG(".....the.fucking.....token..is.......%s",str);
      //  cocos2d::CCMessageBox(str,"fucking token");
        g_pLoginManage->LoginFor91Platform(str , 0);
        
        // Doyang 20120712
        [self removeLoginNotification];
    }
    else if (error == ND_COM_PLATFORM_ERROR_NETWORK_FAIL)
    {
        cocos2d::CCLog("网络连接错误");
    }
    else if (error != ND_COM_PLATFORM_ERROR_USER_CANCEL) 
    { 
        //用户登录失败提示和处理
        
    } 
}

//在必要的时候(例如析构)移除登录消息的监听
-(void)removeLoginNotification
{
    [[NSNotificationCenter defaultCenter] removeObserver:self
                         name:(NSString *)kNdCPLoginNotification object:nil];
}

+(void) switchAccount
{
    [[NdComPlatform defaultPlatform] NdSwitchAccount];
}

+(void) setDebug
{
    [[NdComPlatform defaultPlatform] NdSetDebugMode:0];
}

+(void) setAppId:(int)AppIdValue AppKey:(NSString*)AppKeyValue
{
    //...开发者这应该在程序启动的时候优先设置向开发者后台申请的 AppId 和 AppKey
    [[NdComPlatform defaultPlatform] setAppId:AppIdValue];
    [[NdComPlatform defaultPlatform] setAppKey:AppKeyValue];
    //...write you code here
    //优先检查软件自身版本更新,之后再开始应用相关操作处理
}

-(void) buyGold:(int)gold
{
    char uri[500];
    NSString* pStrAccount = [[NdComPlatform defaultPlatform] loginUin];
    sprintf(uri, "http://i.pay.4399sy.com/game/get_order_id.php?app_id=%d&item_count=%d&from=%d&uid=%s&serverid=%s", CONNECT91_AppId, gold, 91, [pStrAccount UTF8String], g_pLoginManage->getExchargeServerId().c_str());//http://i.pay.sy.my4399.com/game/get_order_id.php
    ghttp_request *request = NULL;
    ghttp_status status;
    char *buf;
    int bytes_read;
    
    request = ghttp_request_new();
    if(ghttp_set_uri(request, uri) == -1)
        exit(-1);
    if(ghttp_set_type(request, ghttp_type_get) == -1)
        exit(-1);
    ghttp_set_sync(request, ghttp_async);
    ghttp_prepare(request);
    
    while(1) 
    {
        status = ghttp_process(request);
        if(status == ghttp_error)
            break;
        buf = ghttp_get_body(request);
        bytes_read = ghttp_get_body_len(request);
        if(status == ghttp_done) 
        {
            printf("%s", buf);
            printf("\n");
            printf("number:%d", bytes_read);
            break;
        }
        else
        {
            printf("false\n");
        }
    }
    char* usefulBuff = new char[bytes_read+1];
    strncpy(usefulBuff, buf, bytes_read);
    usefulBuff[bytes_read] = '\0';
    
    NSString* orderNumStr = [NSString stringWithUTF8String:usefulBuff];
    delete [] usefulBuff;
    usefulBuff = 0;
    ghttp_request_destroy(request);
    [[NdComPlatform defaultPlatform] NdUniPayForCoin:orderNumStr needPayCoins:gold payDescription:@""];
}

+(void) enterPlatform
{
    if([[NdComPlatform defaultPlatform] isLogined])
        [[NdComPlatform defaultPlatform] NdEnterPlatform:0];
    else
        [[NdComPlatform defaultPlatform] NdLogin:0]; 
}


@end
