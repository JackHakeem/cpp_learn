//
//  Connect91Handler.h
//  HEBI
//
//  Created by 揭浩英 on 12-6-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NdComPlatform/NDComPlatform.h>
#import <NdComPlatform/NdComPlatformAPIResponse.h>
#import <NdComPlatform/NdCPNotifications.h>


@interface Connect91Handler : NSObject
{
    
}

+ (Connect91Handler *)sharedTo91;//获取
+(void) switchAccount;//改变帐户
+(void) setDebug;//设置成DEBUG
+(void) setAppId:(int)AppIdValue AppKey:(NSString*)AppKeyValue;//设置应用ID和产品密钥
+(void) enterPlatform;//进入平台中心的首页界面

-(id) kkInit;//初始化
-(void) appVersionUpdateDidFinish:(ND_APP_UPDATE_RESULT)updateResult;//检测版本更新回调
-(void) versionUpdateCheck;//启动版本更新检测
-(void) registerLoginNotification;//注册登陆所用的回调函数
-(void) login91;//登陆91
-(void) SNSLoginProcess:(NSNotification *)notify;//登陆所用的回调函数
-(void) removeLoginNotification;//移除登陆所用的回调函数监听
-(void) buyGold:(int)gold;

@end
