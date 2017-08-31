//
//  IosHelper.cpp
//  kkddz
//
//  Created by macbook110 on 13-6-4.
//
//

#include "IosHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <UIKit/UIDevice.h>
#include <sys/socket.h> // Per msqr
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#import "WXApi.h"
#import "WXApiObject.h"
#import "sdkCall.h"
#import "XMLDictionary.h"

#endif//

void IosHelper::sendAuthRequest()
{ 
    //构造SendAuthReq结构体 
    SendAuthReq* req =[[[SendAuthReq alloc ] init ] autorelease ];
    req.scope = @"snsapi_userinfo" ;
    req.state = @"123" ;
    //第三方向微信终端发送一个SendAuthReq消息结构
    [WXApi sendReq:req]; 
}

void IosHelper::shareWithWeixinCircleTxt(const char * pTxt,const char * pUrl, const char* desc){
    NSString *txt = [NSString stringWithCString:pTxt encoding:NSUTF8StringEncoding];
    WXMediaMessage *message = [WXMediaMessage message];
    message.title = txt;
    message.description = [NSString stringWithCString:desc encoding:NSUTF8StringEncoding];
    message.messageExt = txt;
    message.messageAction = txt;
    
    [message setThumbImage:[UIImage imageNamed:@"weixin_share_icon.png"]];
    
    WXWebpageObject *ext = [WXWebpageObject object];
    ext.webpageUrl = [NSString stringWithCString:pUrl encoding:NSUTF8StringEncoding];
    
    message.mediaObject = ext;
    
    
    SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
    req.bText = NO;
    req.message = message; 
    req.scene = WXSceneTimeline;
    
    [WXApi sendReq:req];
}
void IosHelper::shareWithWeixinFriendTxt(const char * pTxt,const char * pUrl, const char* desc){
    
    NSString *txt = [NSString stringWithCString:pTxt encoding:NSUTF8StringEncoding];
    WXMediaMessage *message = [WXMediaMessage message];
    message.title = txt;
    message.description = [NSString stringWithCString:desc encoding:NSUTF8StringEncoding];;
    message.messageExt = txt;
    message.messageAction = txt;
    
    WXWebpageObject *ext = [WXWebpageObject object];
    ext.webpageUrl = [NSString stringWithCString:pUrl encoding:NSUTF8StringEncoding];
    
    message.mediaObject = ext;
    
    
    SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
    req.bText = NO;
    req.message = message; 
    req.scene = WXSceneSession;
    
    [WXApi sendReq:req];

}

void IosHelper::shareWithWeixinFriendImg(const char * pTxt,const char *FileName)
{
    NSString *txt = [NSString stringWithCString:pTxt encoding:NSUTF8StringEncoding];
    NSString *filePath = [NSString stringWithCString:FileName encoding:NSUTF8StringEncoding];
    WXMediaMessage *message = [WXMediaMessage message];
    
    message.title = txt;
    message.description = txt;
    [message setThumbImage:[UIImage imageNamed:@"weixin_share_icon.png"]];
    
    WXImageObject *ext = [WXImageObject object];
    ext.imageData = [NSData dataWithContentsOfFile:filePath];
    
    
    
    message.mediaObject = ext;
    
    SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
    req.bText = NO;
    req.message = message;
    req.scene = WXSceneSession;
    
    [WXApi sendReq:req];
}
void IosHelper::shareWithWeixinCircleImg(const char * pTxt,const char *FileName)
{
    NSString *txt = [NSString stringWithCString:pTxt encoding:NSUTF8StringEncoding];
    NSString *filePath = [NSString stringWithCString:FileName encoding:NSUTF8StringEncoding];
    WXMediaMessage *message = [WXMediaMessage message];
    
    message.title = txt;
    message.description = txt;
    [message setThumbImage:[UIImage imageNamed:@"weixin_share_icon.png"]];
    
    WXImageObject *ext = [WXImageObject object];
    ext.imageData = [NSData dataWithContentsOfFile:filePath];
    
    
    
    message.mediaObject = ext;
    
    SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
    req.bText = NO;
    req.message = message;
    req.scene = WXSceneTimeline;
    
    [WXApi sendReq:req];
}

void IosHelper::wxPayByOrder(const char* order)
{
    NSString *string_order = [[NSString alloc] initWithCString:(const char*)order encoding:NSUTF8StringEncoding];
    NSLog(@" other ---- %@", string_order);
    
    NSDictionary *xmlDictionary = [NSDictionary dictionaryWithXMLString:string_order];
    // 打印 NSDictionary
    NSLog(@"%@", xmlDictionary);
	
    PayReq *request = [[[PayReq alloc] init] autorelease];
    request.partnerId   = xmlDictionary[@"partnerid"];
    request.prepayId    = xmlDictionary[@"prepayid"];
    request.package     = @"Sign=WXPay";
    request.nonceStr    = xmlDictionary[@"noncestr"];
    request.timeStamp   = [xmlDictionary[@"timestamp"] longLongValue];
    request.sign        = xmlDictionary[@"sign"];
    
    NSLog(@"package-:-     %@", request.package);
    NSLog(@"partnerId-:-   %@", request.partnerId);
    NSLog(@"prepayId-:-    %@", request.prepayId);
    NSLog(@"nonceStr-:-    %@", request.nonceStr);
    //NSLog(@"timeStamp-:-   %u", request.timeStamp);
    NSLog(@"sign-:-        %@", request.sign);
    
    [WXApi sendReq:request];
}

void IosHelper::startBrowserJni( const char * url)
{
    NSString *nsFineName = [NSString stringWithCString:url encoding:NSUTF8StringEncoding];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:nsFineName]];
}

void IosHelper::loginQQ()
{
    NSArray *permissions = [NSArray arrayWithObjects:kOPEN_PERMISSION_GET_INFO, kOPEN_PERMISSION_GET_USER_INFO, kOPEN_PERMISSION_GET_SIMPLE_USER_INFO, nil];
    
    [[[sdkCall getinstance] oauth] authorize:permissions inSafari:NO];
}

void IosHelper::logoutQQ()
{
    
}

 AVAudioRecorder *recorder = NULL;
void IosHelper::beginRecord(const char *_fileName)
{
    if (recorder == nil)
    {
        //设置文件名和录音路径
        NSString *recordFilePath = [NSString stringWithCString:_fileName encoding:NSUTF8StringEncoding];
        
        NSDictionary *recordSetting = [[NSDictionary alloc] initWithObjectsAndKeys:
                                       [NSNumber numberWithFloat: 8000.0],AVSampleRateKey, //采样率
                                       [NSNumber numberWithInt: kAudioFormatLinearPCM],AVFormatIDKey,
                                       [NSNumber numberWithInt:16],AVLinearPCMBitDepthKey,//采样位数 默认 16
                                       [NSNumber numberWithInt: 1], AVNumberOfChannelsKey,//通道的数目
                                       nil];
        
        //初始化录音
        NSError *error = nil;
        recorder = [[ AVAudioRecorder alloc] initWithURL:[NSURL URLWithString:recordFilePath] settings:recordSetting error:&error];
    }
    recorder.meteringEnabled = YES;
    [recorder prepareToRecord];
    //开始录音
    UInt32 sessionCategory = kAudioSessionCategory_PlayAndRecord;
    AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(sessionCategory), &sessionCategory);
    
    // 扬声器播放
    UInt32 audioRouteOverride = kAudioSessionOverrideAudioRoute_Speaker;
    AudioSessionSetProperty (kAudioSessionProperty_OverrideAudioRoute, sizeof(audioRouteOverride), &audioRouteOverride);
    [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayAndRecord error:nil];
    [[AVAudioSession sharedInstance] setActive:YES error:nil];
    [recorder record];
}
const char * IosHelper::endRecord()
{
    if (recorder == nil)
        return "";
    if (recorder.isRecording)
        [recorder stop];
    recorder = nil;
	return "";
}
