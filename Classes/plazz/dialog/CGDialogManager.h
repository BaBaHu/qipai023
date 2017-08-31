#ifndef _CGDialogManager_H_
#define _CGDialogManager_H_
#include "cocos2d.h"
#include <string>
#include <map>
#include "CGDialog.h"
using namespace std;
USING_NS_CC;

typedef std::map<int, CGDialog*> CGameDialogMap;
class CGDialogManager : public Ref
{
public:
	static CGDialogManager* shared();
	static void purge();

public:
	bool AddDialog(int diglgID, CGDialog* dialog);
	bool RemoveDialog(int diglgID);

	//执行确定按钮
	bool PerformOkAction(int diglgID);

	//执行取消按钮
	bool PerformCancelAction(int diglgID);

	int GetDialgID();
private:
	CGDialogManager();
	~CGDialogManager();

private:
	CGameDialogMap			m_mapDialog;
	int						m_dialgID;
};
#endif // _CGDialogManager_H_