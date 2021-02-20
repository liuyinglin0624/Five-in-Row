#pragma once
#include"Player.h"
#include"Sys.h"
#include"Strategy.h"
// CInitColorDlg �Ի���

class CInitColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInitColorDlg)

public:
	CInitColorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInitColorDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CPlayer* player;
	shared_ptr<CStrategy> pPtr;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	void SetPlayerColor(CPlayer* player,shared_ptr<CStrategy> ptr);
};
