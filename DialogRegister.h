#pragma once


// DialogRegister 对话框

class DialogRegister : public CDialogEx
{
	DECLARE_DYNAMIC(DialogRegister)

public:
	DialogRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogRegister();
	static bool IsRegister;
// 对话框数据
	enum { IDD = IDD_DIALOG_REGISTER };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void AppInit();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
