#ifndef _CGDialog_H_
#define _CGDialog_H_
#include <string>
#include <map>
#include <functional>
using namespace std;

// 对话框按钮
#define CGDLG_MB_OK			0x1
#define CGDLG_MB_CANCEL		0x2

typedef std::function<void (void)> CGDIALOG_CALLBACK;
typedef std::function<void (const std::string&, const std::string&, int, CGDIALOG_CALLBACK, CGDIALOG_CALLBACK)> CGDIALOG_CREATOR;

class CGDialog
{
public:
	CGDialog(const std::string& title, const std::string& content,
		int buttonMask, CGDIALOG_CALLBACK confirmCallback = nullptr, CGDIALOG_CALLBACK cancelCallback = nullptr);

	CGDialog(const std::string& title, const int contentID,
		int buttonMask, CGDIALOG_CALLBACK confirmCallback = nullptr, CGDIALOG_CALLBACK cancelCallback = nullptr);
public:
	static CGDIALOG_CREATOR sCreator;
	std::string				m_title;
	std::string				m_content;
	int						m_contentID;
	int						m_buttonMask;
	int						m_nDialogID;
	CGDIALOG_CALLBACK		m_okCallBack;
	CGDIALOG_CALLBACK		m_cancelCallBack;
};

#endif // _CGDialog_H_