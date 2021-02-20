
// ChessAppDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChessApp.h"
#include "ChessAppDlg.h"
#include "afxdialogex.h"
#include"LevelOne.h"
#include"LevelOneFactory.h"
#include"LevelTwoFactory.h"
#include"LevelThreeFactory.h"
#include"LevelFourFactory.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChessAppDlg �Ի���



CChessAppDlg::CChessAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChessAppDlg::IDD, pParent),ptr_Factory(new CLevelOneFactory)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChessAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, Combo);
}

BEGIN_MESSAGE_MAP(CChessAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_CBN_CLOSEUP(IDC_COMBO1, &CChessAppDlg::OnCbnCloseupCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CChessAppDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CChessAppDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CChessAppDlg ��Ϣ�������
DWORD CChessAppDlg::ThreadProc( LPVOID lpParameter)
{
	::mciSendString(_T("open ..\\res\\������.mp3 alias start"),NULL,0,NULL);

	::mciSendString(_T("play start repeat"),NULL,0,NULL);
	return 0;
}

BOOL CChessAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	srand((unsigned int)time(NULL));

	this->border.ChessBorderInit(theApp.m_hInstance);
	this->ptr_Foe = this->ptr_Factory->FactroyCreate();
	CreateThread(NULL,0,CChessAppDlg::ThreadProc,this,0,0);
	player.SelectInit(theApp.m_hInstance);

	this->Combo.AddString(_T("LevelOne"));
	this->Combo.AddString(_T("LevelTwo"));
	this->Combo.AddString(_T("LevelThree"));
	this->Combo.AddString(_T("LevelFour"));
	this->Combo.SelectString(-1,_T("LevelOne"));
	if(ReadInfo() == false)
	{
		initcolordlg.SetPlayerColor(&this->player,this->ptr_Foe);
		initcolordlg.DoModal();
	}
	
	this->CareTaker.SetMemento(this->CreateMemento());
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChessAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChessAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	CClientDC hdc(this);
	
	CDC CMemDC;
	CMemDC.CreateCompatibleDC(&hdc);
	CBitmap CBmp;
	CBmp.CreateCompatibleBitmap(&hdc,501,614);
	CMemDC.SelectObject(CBmp);

	//----------------------------
	this->border.ChessBorderShow(CMemDC);
	this->player.SelectShow(CMemDC);
	//----------------------------
	hdc.BitBlt(0,0,501,614,&CMemDC,0,0,SRCCOPY);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChessAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChessAppDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChessAppDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(point.x<501 && point.y <614)
			this->player.GetSelectPos(point);
	this->OnPaint();
	CDialogEx::OnMouseMove(nFlags, point);
}


void CChessAppDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	GetKeyPos(point);

	if(border.BorderArr[this->mPoint.y][this->mPoint.x] == 0)
	{
		this->SetPlayingBorder(&this->CareTaker,&this->border);
	}

	//ֻ�е���ҵ�����ȷ���İ��£����Բſ��Խ����ж�������
	bool bDownFlag = false;
	if( (bDownFlag = this->player.KeyDown(this->mPoint,&border) )== true)
		PlaySound(TEXT("..\\res\\������Ч.wav"),NULL,SND_FILENAME|SND_ASYNC);
	this->OnPaint();
	POINT Temp;
	Temp.x = this->mPoint.y;
	Temp.y = this->mPoint.x;
	if(this->Judger.IsWin(&border,player.nColorKey,Temp))
	{
		this->MessageBox(_T("you win,Next"),_T("��ʾ"),MB_OK);
		this->border.Clear();
		//��������
		if(player.nColorKey == WHITE)
		{
			int index = rand()%5;
			if(index == 0)
				this->border.BorderArr[7][7] = BLACK;
			if(index == 1)
				this->border.BorderArr[3][3] = BLACK;
			if(index == 2)
				this->border.BorderArr[11][3] = BLACK;
			if(index == 3)
				this->border.BorderArr[3][11] = BLACK;
			if(index == 4)
				this->border.BorderArr[11][11] = BLACK;
		}
	}
	else
	{
		if(bDownFlag == true)
		{
			this->mPoint = this->ptr_Foe->TimeToComputer(&this->border);
			this->OnPaint();
			if(this->Judger.IsWin(&this->border,ptr_Foe->nColor,mPoint))
			{
				this->MessageBox(_T("you lose,Again"),_T("��ʾ"),MB_OK);
				this->border.Clear();
				//��������
				if(player.nColorKey == WHITE)
				{
					int index = rand()%5;
					if(index == 0)
						this->border.BorderArr[7][7] = BLACK;
					if(index == 1)
						this->border.BorderArr[3][3] = BLACK;
					if(index == 2)
						this->border.BorderArr[11][3] = BLACK;
					if(index == 3)
						this->border.BorderArr[3][11] = BLACK;
					if(index == 4)
						this->border.BorderArr[11][11] = BLACK;
				}
			}
		}
	}
	
	this->OnPaint();

	CDialogEx::OnLButtonDown(nFlags, point);
}
void CChessAppDlg::GetKeyPos(POINT point)
{
	this->mPoint.x = ((point.x - 19)/16)/2;
	this->mPoint.y = ((point.y - 93)/16)/2;
}

void CChessAppDlg::OnCbnCloseupCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = this->Combo.GetCurSel();
	if(index != CB_ERR)
	{
		if(index == 0)
		{
			this->ptr_Factory.reset(new CLevelOneFactory);
			this->ptr_Foe = ptr_Factory->FactroyCreate();
			initcolordlg.SetPlayerColor(&this->player,this->ptr_Foe);
			this->initcolordlg.DoModal();
			this->border.Clear();
			//��������
			if(player.nColorKey == WHITE)
			{
				int index = rand()%5;
				if(index == 0)
					this->border.BorderArr[7][7] = BLACK;
				if(index == 1)
					this->border.BorderArr[3][3] = BLACK;
				if(index == 2)
					this->border.BorderArr[11][3] = BLACK;
				if(index == 3)
					this->border.BorderArr[3][11] = BLACK;
				if(index == 4)
					this->border.BorderArr[11][11] = BLACK;
			}
		}
		if(index == 1)
		{
			this->ptr_Factory.reset(new CLevelTwoFactory);
			this->ptr_Foe = ptr_Factory->FactroyCreate();
			initcolordlg.SetPlayerColor(&this->player,this->ptr_Foe);
			this->initcolordlg.DoModal();
			this->border.Clear();
			//��������
			if(player.nColorKey == WHITE)
			{
				int index = rand()%5;
				if(index == 0)
					this->border.BorderArr[7][7] = BLACK;
				if(index == 1)
					this->border.BorderArr[3][3] = BLACK;
				if(index == 2)
					this->border.BorderArr[11][3] = BLACK;
				if(index == 3)
					this->border.BorderArr[3][11] = BLACK;
				if(index == 4)
					this->border.BorderArr[11][11] = BLACK;
			}
		}
		if(index == 2)
		{
			this->ptr_Factory.reset(new CLevelThreeFactory);
			this->ptr_Foe = ptr_Factory->FactroyCreate();
			initcolordlg.SetPlayerColor(&this->player,this->ptr_Foe);
			this->initcolordlg.DoModal();
			this->border.Clear();
			//��������
			if(player.nColorKey == WHITE)
			{
				int index = rand()%5;
				if(index == 0)
					this->border.BorderArr[7][7] = BLACK;
				if(index == 1)
					this->border.BorderArr[3][3] = BLACK;
				if(index == 2)
					this->border.BorderArr[11][3] = BLACK;
				if(index == 3)
					this->border.BorderArr[3][11] = BLACK;
				if(index == 4)
					this->border.BorderArr[11][11] = BLACK;
			}
		}
		if(index == 3)
		{
			this->ptr_Factory.reset(new CLevelFourFactory);
			this->ptr_Foe = ptr_Factory->FactroyCreate();
			initcolordlg.SetPlayerColor(&this->player,this->ptr_Foe);
			this->initcolordlg.DoModal();
			this->border.Clear();
			//��������
			if(player.nColorKey == WHITE)
			{
				int index = rand()%5;
				if(index == 0)
					this->border.BorderArr[7][7] = BLACK;
				if(index == 1)
					this->border.BorderArr[3][3] = BLACK;
				if(index == 2)
					this->border.BorderArr[11][3] = BLACK;
				if(index == 3)
					this->border.BorderArr[3][11] = BLACK;
				if(index == 4)
					this->border.BorderArr[11][11] = BLACK;
			}
		}
	}

}

CStateMemento* CChessAppDlg::CreateMemento()
{
	return new CStateMemento;
}
void CChessAppDlg::RecoverLastBorder(CStateCareTaker* CareTaker,CChessBorder* border)
{
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			border->BorderArr[i][j] = CareTaker->GetMemento()->arr[i][j];
		}
	}
}
void CChessAppDlg::SetPlayingBorder(CStateCareTaker* CareTaker,CChessBorder* border)
{
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			CareTaker->GetMemento()->arr[i][j] = border->BorderArr[i][j];
		}
	}
}

void CChessAppDlg::OnBnClickedButton1()
{
	this->RecoverLastBorder(&this->CareTaker,&this->border);
	this->OnPaint();
}


void CChessAppDlg::OnBnClickedButton2()
{
	FILE* pF;
	fopen_s(&pF,"..\\res\\Border.txt","wb");

	char txt;
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			if(this->border.BorderArr[i][j] == 0)
			{
				fputc('0',pF);
			}
			if(this->border.BorderArr[i][j] == 1)
			{
				fputc('1',pF);
			}
			if(this->border.BorderArr[i][j] == 2)
			{
				fputc('2',pF);
			}
		}
		fputc('\r',pF);
		fputc('\n',pF);
	}

	fclose(pF);

	FILE* pf;
	fopen_s(&pf,"..\\res\\info.txt","wb");
	if(player.nColorKey == BLACK)
		fputc('2',pf);
	else if(player.nColorKey == WHITE)
		fputc('1',pf);

	if(this->ptr_Foe->nLevel == 1)
		fputc('1',pf);
	if(this->ptr_Foe->nLevel == 2)
		fputc('2',pf);
	if(this->ptr_Foe->nLevel == 3)
		fputc('3',pf);
	if(this->ptr_Foe->nLevel == 4)
		fputc('4',pf);
	fclose(pf);
}
bool CChessAppDlg::ReadInfo()
{
	FILE* pF;
	fopen_s(&pF,"..\\res\\info.txt","rb");
	char Color;
	char State;
	Color = fgetc(pF);
	State = fgetc(pF);
	if(Color != '0' && State != '0')
	{
		if(State - '0' == 1)
		{
			this->ptr_Factory.reset(new CLevelOneFactory);
			this->ptr_Foe = ptr_Factory->FactroyCreate();
			this->Combo.SelectString(-1,_T("LevelOne"));
		}
		else if(State - '0' == 2)
		{
			this->ptr_Factory.reset(new CLevelTwoFactory);
			this->ptr_Foe = ptr_Factory->FactroyCreate();
			this->Combo.SelectString(-1,_T("LevelTwo"));
		}
		else if(State - '0' == 3)
		{
			this->ptr_Factory.reset(new CLevelThreeFactory);
			this->ptr_Foe = ptr_Factory->FactroyCreate();
			this->Combo.SelectString(-1,_T("LevelThree"));
		}
		else if(State - '0' == 4)
		{
			this->ptr_Factory.reset(new CLevelFourFactory);
			this->ptr_Foe = ptr_Factory->FactroyCreate();
			this->Combo.SelectString(-1,_T("LevelFour"));
		}

		if(Color-'0' == WHITE)
		{
			this->player.SetColor(WHITE);
			this->ptr_Foe->nColor = BLACK;
		}
		else if(Color-'0' == BLACK)
		{
			this->player.SetColor(BLACK);
			this->ptr_Foe->nColor = WHITE;
		}

		fclose(pF);
		return true;
	}
	else
	{
		fclose(pF);
		return false;
	}
}