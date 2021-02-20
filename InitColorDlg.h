#pragma once
#include"Player.h"
#include"Sys.h"
#include"Strategy.h"
// CInitColorDlg 对话框

class CInitColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInitColorDlg)

public:
	CInitColorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInitColorDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CPlayer* player;
	shared_ptr<CStrategy> pPtr;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	void SetPlayerColor(CPlayer* player,shared_ptr<CStrategy> ptr);
};
