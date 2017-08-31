#include "CGDialog.h"
#include "CGDialogManager.h"
#include "MECallBackListenerHelper.h"

CGDIALOG_CREATOR CGDialog::sCreator = nullptr;

CGDialog::CGDialog(const std::string& title, const std::string& content, int buttonMask, CGDIALOG_CALLBACK confirmCallback, CGDIALOG_CALLBACK cancelCallback)
{
	/*if (sCreator != nullptr)
		sCreator(title, content, buttonMask, confirmCallback, cancelCallback);*/
	m_title = title;
	m_content = content;
	m_contentID = 0;
	m_buttonMask = buttonMask;
	m_okCallBack = confirmCallback;
	m_cancelCallBack = cancelCallback;

	int nDialogID = CGDialogManager::shared()->GetDialgID();
	m_nDialogID = nDialogID;

	CGDialogManager::shared()->AddDialog(nDialogID, this);
	
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onDialogMessageBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(nDialogID);
		pStack->pushInt(buttonMask);
		pStack->pushInt(0);
		pStack->pushString(content.c_str());
		ret = pStack->executeFunctionByHandler(nLuaHandler, 4);
	} while (0);
}

CGDialog::CGDialog(const std::string& title, const int contentID, int buttonMask, CGDIALOG_CALLBACK confirmCallback, CGDIALOG_CALLBACK cancelCallback)
{
	/*if (sCreator != nullptr)
	sCreator(title, content, buttonMask, confirmCallback, cancelCallback);*/
	m_title = title;
	m_contentID = contentID;
	m_content = "";
	m_buttonMask = buttonMask;
	m_okCallBack = confirmCallback;
	m_cancelCallBack = cancelCallback;

	int nDialogID = CGDialogManager::shared()->GetDialgID();
	m_nDialogID = nDialogID;

	CGDialogManager::shared()->AddDialog(nDialogID, this);
	
	int ret = 0;
	do
	{
		LUA_FUNCTION nLuaHandler = MECallBackListenerHelper::getInstance()->getHandler("onDialogMessageBack");
		CC_BREAK_IF(0 == nLuaHandler);
		LuaEngine* pEngine = LuaEngine::getInstance();
		LuaStack* pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		lua_settop(tolua_s, 0);
		pStack->pushInt(nDialogID);
		pStack->pushInt(buttonMask);
		pStack->pushInt(contentID);
		pStack->pushString("");
		ret = pStack->executeFunctionByHandler(nLuaHandler, 4);
	} while (0);
}