
// ChessAppDlg.h : ͷ�ļ�
//
#pragma once
#include"Sys.h"
#include"ChessBorder.h"
#include"Player.h"
#include"InitColorDlg.h"
#include"Judgement.h"
#include"Strategy.h"
#include"Factory.h"
#include "afxwin.h"
#include"StateCareTaker.h"
// CChessAppDlg �Ի���
class CChessAppDlg : public CDialogEx
{
// ����
public:
	CChessAppDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHESSAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CInitColorDlg initcolordlg;
	POINT mPoint;
	CChessBorder border;
	CPlayer player;
	CJudgement Judger;
	shared_ptr<CStrategy> ptr_Foe;
	shared_ptr<CFactory> ptr_Factory;
	CComboBox Combo;
	CStateCareTaker CareTaker;
public:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void GetKeyPos(POINT point);
	afx_msg void OnCbnCloseupCombo1();
	CStateMemento* CreateMemento();
	void RecoverLastBorder(CStateCareTaker* CareTaker,CChessBorder* border);
	void SetPlayingBorder(CStateCareTaker* CareTaker,CChessBorder* border);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	bool ReadInfo();
};
