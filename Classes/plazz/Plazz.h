#ifndef _Plazz_H_
#define _Plazz_H_

#include "df/DF.h"

#include "data/GlobalUserInfo.h"
#include "data/ServerListData.h"

#include "data/OptionParameter.h"
#include "data/GlobalUnits.h"

#include "network/CSocketEngine.h"
#include "network/CSocketMission.h"

//广场任务
#include "plazz/GPMission.h"

//房间服务
#include "kernel/server/IServerItem.h"
#include "kernel/server/TableFrame.h"

//游戏接口
#include "kernel/game/IClientKernel.h"
//游戏接口
#include "kernel/IStringMessageSink.h"

//辅助
#include "dialog/CGDialog.h"
#include "utils/StringData.h"
#include "../libs/libs.h"
#include "cocos2d.h"

#define PLAZZ_PRINTF cocos2d::log

//static const char* DEFAULT_IP_ADDRESS = "125.88.146.105";
static const char* DEFAULT_IP_ADDRESS = "127.0.0.1";
//static const int DEFAULT_PORT = 12100;
static const int DEFAULT_PORT = 8300;

USING_NS_CC;
#endif // _Plazz_H_