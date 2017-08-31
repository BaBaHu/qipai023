#include "GlobalUnits.h"

#define GAME_GLOBAL "GameFrame"
//////////////////////////////////////////////////////////////////////////////////
CGlobalUnits gGlobalUnits;
//////////////////////////////////////////////////////////////////////////////////

//构造函数
CGlobalUnits::CGlobalUnits()
{
	//默认参数
	DefaultParameter();
	return;
}

//析构函数
CGlobalUnits::~CGlobalUnits()
{
	return;
}

//创建组件
bool CGlobalUnits::InitGlobalUnits()
{
	//加载参数
	LoadParameter();
	return true;
}

//注销组件
bool CGlobalUnits::UnInitGlobalUnits()
{
	//保存参数
	SaveParameter();
	return true;
}

//加载参数
void CGlobalUnits::LoadParameter()
{
	return;
	////界面配置
	//m_bMuteStatuts=UserDefault::getInstance()->getBoolForKey(GAME_GLOBAL, ("MuteStatuts"), m_bMuteStatuts);
	//m_bAllowSound=UserDefault::getInstance()->getBoolForKey(GAME_GLOBAL, ("AllowSound"),m_bAllowSound);
	//m_bAllowBackGroundSound=UserDefault::getInstance()->getBoolForKey(GAME_GLOBAL, ("AllowBackGroundSound"),m_bAllowBackGroundSound);
	//m_bNotifyUserInOut=UserDefault::getInstance()->getBoolForKey(GAME_GLOBAL, ("NotifyUserInOut"),m_bNotifyUserInOut);
	//m_bDebarDetestChat=UserDefault::getInstance()->getBoolForKey(GAME_GLOBAL, ("DebarDetestChat"),m_bDebarDetestChat);

	////旁观选项
	//m_bAllowLookon=UserDefault::getInstance()->getBoolForKey(GAME_GLOBAL, ("AllowLookon"),m_bAllowLookon);
	//m_bAllowFriendLookon=UserDefault::getInstance()->getBoolForKey(GAME_GLOBAL, ("AllowFriendLookon"),m_bAllowFriendLookon);

	////消息模式
	//m_cbMessageMode=(byte)UserDefault::getInstance()->getIntegerForKey(GAME_GLOBAL, ("MessageMode"),m_cbMessageMode);
	//switch (m_cbMessageMode)
	//{
	//case MESSAGE_MODE_ALL:
	//case MESSAGE_MODE_FRIEND: { break; }
	//default: { m_cbMessageMode=MESSAGE_MODE_DETEST; }
	//}
}

//保存参数
void CGlobalUnits::SaveParameter()
{
	return;
	////界面配置
	//UserDefault::getInstance()->setBoolForKey(GAME_GLOBAL, ("MuteStatuts"), m_bMuteStatuts);
	//UserDefault::getInstance()->setBoolForKey(GAME_GLOBAL, ("AllowSound"),m_bAllowSound);
	//UserDefault::getInstance()->setBoolForKey(GAME_GLOBAL, ("AllowBackGroundSound"),m_bAllowBackGroundSound);
	//UserDefault::getInstance()->setBoolForKey(GAME_GLOBAL, ("NotifyUserInOut"),m_bNotifyUserInOut);
	//UserDefault::getInstance()->setBoolForKey(GAME_GLOBAL, ("DebarDetestChat"),m_bDebarDetestChat);

	////旁观选项
	//UserDefault::getInstance()->setBoolForKey(GAME_GLOBAL, ("AllowLookon"),m_bAllowLookon);
	//UserDefault::getInstance()->setBoolForKey(GAME_GLOBAL, ("AllowFriendLookon"),m_bAllowFriendLookon);

	////消息模式
	//UserDefault::getInstance()->setIntegerForKey(GAME_GLOBAL, ("MessageMode"),m_cbMessageMode);

	//return;
}

//默认参数
void CGlobalUnits::DefaultParameter()
{
	//其他选项
	m_bMuteStatuts=false;
	m_bAllowSound=true;
	m_bAllowBackGroundSound=true;
	m_bNotifyUserInOut=true;
	m_bDebarDetestChat=false;

	//旁观选项
	m_bAllowLookon=false;
	m_bAllowFriendLookon=true;

	//模式变量
	m_cbMessageMode=MESSAGE_MODE_DETEST;

	return;
}
