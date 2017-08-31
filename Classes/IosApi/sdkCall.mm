//
//  sdkCall.m
//  sdkDemo
//
//  Created by xiaolongzhang on 13-3-29.
//  Copyright (c) 2013年 xiaolongzhang. All rights reserved.
//

#import "sdkCall.h"
#import "sdkDef.h"
#import <TencentOpenAPI/TencentMessageObject.h>
#include "MEWeiXinHelper.h"
static sdkCall *g_instance = nil;
@interface sdkCall()
@property (nonatomic, retain)NSArray* permissons;
@end

@implementation sdkCall

@synthesize oauth = _oauth;
@synthesize permissons = _permissons;

+ (sdkCall *)getinstance
{
    @synchronized(self)
    {
        if (nil == g_instance)
        {
            g_instance = [[super allocWithZone:nil] init];
        }
    }

    return g_instance;
}

- (id)init
{
    //注意： 初始化授权 开发者需要在这里填入自己申请到的 AppID
    _oauth = [[TencentOAuth alloc] initWithAppId:@"101358059" andDelegate:self];
	
    return self;
}


+ (id)allocWithZone:(NSZone *)zone
{
    return [[self getinstance] retain];
}


- (id)copyWithZone:(NSZone *)zone
{
    return self;
}

+ (void)resetSDK
{
    g_instance = nil;
}

- (void)tencentDidLogin
{
    if (_oauth.accessToken.length > 0) {
        // 获取用户信息
        [_oauth getUserInfo];

    } else {
		NSString *astring = @"登录不成功 没有获取accesstoken";
		NSLog(@"astring:%@",astring);
        MEWeiXinHelper::getInstance()->onWxLoginFail([astring cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}

- (void)tencentDidNotLogin:(BOOL)cancelled
{
    if (cancelled) {
		NSString *astring = @"用户取消登录";
		NSLog(@"astring:%@",astring);
        MEWeiXinHelper::getInstance()->onWxLoginFail([astring cStringUsingEncoding:NSUTF8StringEncoding]);
    } else {
		NSString *astring = @"登录失败";
		NSLog(@"astring:%@",astring);
        MEWeiXinHelper::getInstance()->onWxLoginFail([astring cStringUsingEncoding:NSUTF8StringEncoding]);
    }
	
}

- (void)tencentDidNotNetWork
{
	NSString *astring = @"登录失败,请检查网络";
	NSLog(@"astring:%@",astring);
    MEWeiXinHelper::getInstance()->onWxLoginFail([astring cStringUsingEncoding:NSUTF8StringEncoding]);
}

- (NSArray *)getAuthorizedPermissions:(NSArray *)permissions withExtraParams:(NSDictionary *)extraParams
{
    return nil;
}

- (void)tencentDidLogout
{

}


- (BOOL)tencentNeedPerformIncrAuth:(TencentOAuth *)tencentOAuth withPermissions:(NSArray *)permissions
{
    return YES;
}


- (BOOL)tencentNeedPerformReAuth:(TencentOAuth *)tencentOAuth
{
    return YES;
}

- (void)tencentDidUpdate:(TencentOAuth *)tencentOAuth
{
}


- (void)tencentFailedUpdate:(UpdateFailType)reason
{
}


- (void)getUserInfoResponse:(APIResponse*) response
{
    if (response && response.retCode == URLREQUEST_SUCCEED) {
        
        NSDictionary *userInfo = [response jsonResponse];
        NSString *nickName = userInfo[@"nickname"];
        NSString *figureurl = userInfo[@"figureurl_qq_2"];
        NSString *gender = userInfo[@"gender"];

		NSString* strMsg = [NSString stringWithFormat:@"%@+%@+%@+%@+%@+%@",[_oauth openId], [_oauth accessToken], [_oauth expirationDate], nickName,figureurl,gender];
        MEWeiXinHelper::getInstance()->onQQLoginSuccess([strMsg cStringUsingEncoding:NSUTF8StringEncoding]);
    } else {
        NSLog(@"QQ auth fail ,getUserInfoResponse:%d", response.detailRetCode);
    }
}

@end
