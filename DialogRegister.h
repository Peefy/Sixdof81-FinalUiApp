#pragma once


// DialogRegister �Ի���

class DialogRegister : public CDialogEx
{
	DECLARE_DYNAMIC(DialogRegister)

public:
	DialogRegister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogRegister();
	static bool IsRegister;
// �Ի�������
	enum { IDD = IDD_DIALOG_REGISTER };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void AppInit();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
