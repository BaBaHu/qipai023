#include "CGDialogManager.h"
#include "MELog.h"

static CGDialogManager* _sharedDialogManager = nullptr;

CGDialogManager* CGDialogManager::shared()
{
	if (_sharedDialogManager == nullptr){
		_sharedDialogManager = new CGDialogManager();
	}
	return _sharedDialogManager;
}

void CGDialogManager::purge()
{
	CC_SAFE_RELEASE_NULL(_sharedDialogManager);
}


CGDialogManager::CGDialogManager()
{
	m_dialgID = 0;
	m_mapDialog.clear();
}

CGDialogManager::~CGDialogManager()
{
	log("CGDialogManager delete ...................................\n");
}

//初始化 
int CGDialogManager::GetDialgID()
{
	return ++m_dialgID;
}

bool CGDialogManager::AddDialog(int diglgID, CGDialog* dialog)
{
	CGameDialogMap::iterator it = m_mapDialog.find(diglgID);
	if (it != m_mapDialog.end())
	{
		m_mapDialog.erase(diglgID);
	}
	m_mapDialog[diglgID] = dialog;
	return true;
}

bool CGDialogManager::RemoveDialog(int diglgID)
{
	CGameDialogMap::iterator it = m_mapDialog.find(diglgID);
	if (it != m_mapDialog.end())
	{
		m_mapDialog.erase(diglgID);
	}
	return false;
}

//执行确定按钮
bool CGDialogManager::PerformOkAction(int diglgID)
{
	MELOG(MELOG_INFO, "CGDialogManager::PerformOkAction: %d", diglgID);
	CGameDialogMap::iterator it = m_mapDialog.find(diglgID);
	if (it != m_mapDialog.end() && it->second->m_okCallBack)
	{
		it->second->m_okCallBack();
	}
	RemoveDialog(diglgID);
	MELOG(MELOG_INFO, "CGDialogManager::PerformOkAction Finish: %d", diglgID);
	return true;
}

//执行取消按钮
bool CGDialogManager::PerformCancelAction(int diglgID)
{
	MELOG(MELOG_INFO, "CGDialogManager::PerformOkAction: %d", diglgID);
	CGameDialogMap::iterator it = m_mapDialog.find(diglgID);
	if (it != m_mapDialog.end() && it->second->m_cancelCallBack)
	{
		it->second->m_cancelCallBack();
	}
	RemoveDialog(diglgID);
	MELOG(MELOG_INFO, "CGDialogManager::PerformOkAction Finish: %d", diglgID);
	return true;
}