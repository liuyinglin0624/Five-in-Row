// InitColorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChessApp.h"
#include "InitColorDlg.h"
#include "afxdialogex.h"


// CInitColorDlg 对话框

IMPLEMENT_DYNAMIC(CInitColorDlg, CDialogEx)

CInitColorDlg::CInitColorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInitColorDlg::IDD, pParent)
{
	this->player = NULL;
}

CInitColorDlg::~CInitColorDlg()
{
}

void CInitColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInitColorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CInitColorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CInitColorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CInitColorDlg 消息处理程序
void CInitColorDlg::SetPlayerColor(CPlayer* player,shared_ptr<CStrategy> ptr)
{
	this->player = player;
	this->pPtr = ptr;
}

void CInitColorDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->player->SetColor(BLACK);
	this->pPtr->SetColor(WHITE);
	this->SendMessage(WM_CLOSE);
}


void CInitColorDlg::OnBnClickedButton1()
{
	this->player->SetColor(WHITE);
	this->pPtr->SetColor(BLACK);
	this->SendMessage(WM_CLOSE);
}
