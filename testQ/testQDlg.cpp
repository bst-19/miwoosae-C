﻿
// testQDlg.cpp: 구현 파일
//

#include <Windows.h>
#include "stdafx.h"
#include "testQ.h"
#include "testQDlg.h"
#include "afxdialogex.h"
#include "uuirtdrv.h"
#include "conio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestQDlg 대화 상자

CtestQDlg::CtestQDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTQ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Control(pDX, IDC_LOG, m_list);
	DDX_Control(pDX, IDC_BOX1, m_box1);
	DDX_Control(pDX, IDC_BIRD, m_bird_pic);
	DDX_Control(pDX, IDC_START, m_btn_start);
	DDX_Control(pDX, IDC_COMBO1, m_repeat_combo);
	DDX_Control(pDX, IDC_STATIC_REPEAT, m_txt_repeat);
	DDX_Control(pDX, IDC_STATIC_IR, m_txt_IR);
	DDX_Control(pDX, IDC_BTN_OFF, m_btn_off);
	DDX_Control(pDX, IDC_BTN_ON, m_btn_on);
}

BEGIN_MESSAGE_MAP(CtestQDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_PICTURE, &CtestQDlg::OnStnClickedPicture)
	ON_BN_CLICKED(IDOK, &CtestQDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CtestQDlg::OnLvnItemchangedList1)
	ON_WM_GETMINMAXINFO()
	ON_STN_CLICKED(IDC_BIRD, &CtestQDlg::OnStnClickedBird)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LOG, &CtestQDlg::OnLvnItemchangedLog)
	ON_BN_CLICKED(IDC_BTN_ON, &CtestQDlg::OnBnClickedBtnOn)
	ON_BN_CLICKED(IDC_BTN_OFF, &CtestQDlg::OnBnClickedBtnOff)
	ON_BN_CLICKED(IDC_START, &CtestQDlg::OnBnClickedStart)
END_MESSAGE_MAP()




// CtestQDlg 메시지 처리기
BOOL CtestQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		//ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	//
	// 리소스들을 초기화하고 배치하는 함수
	setResources();

	//
	// IR Blaster를 초기화하는 함수
	setIRBlaster();

	capture = new VideoCapture(1);
	if (!capture->isOpened()) {
		setLog(L"캠을 열 수 없습니다.");
	}

	// 웹캠 크기를 320 x 240 으로 지정
	capture->set(CAP_PROP_FRAME_WIDTH, 500);
	capture->set(CAP_PROP_FRAME_HEIGHT, 500);

	SetTimer(1000, 30, NULL);



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CtestQDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.



void CtestQDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CtestQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestQDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CtestQDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 캡쳐한 내용을 읽어서 mat_frame에 배열형태로 담음
	capture->read(mat_frame);


	//	 open CV 함수 적용
	// 그레이 스케일 이미지로 변환
	cvtColor(mat_frame, mat_frame, COLOR_BGR2GRAY);

	// 화면에 보여주기 위한 처리
	// elemSize : 채널의 갯수 에 8bit을 곱한다
	int bpp = 8 * mat_frame.elemSize();

	// bpp : bits per pixel
	assert((bpp == 8 || bpp == 24 || bpp == 32));

	// bit 에 따라 padding을 결정함
	int padding = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
		padding = 4 - (mat_frame.cols % 4);

	if (padding == 4)
		padding = 0;

	int border = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
	{
		border = 4 - (mat_frame.cols % 4);
	}


	Mat mat_temp;
	if (border > 0 || mat_frame.isContinuous() == false)
	{
		// Adding needed columns on the right (max 3 px)
		// 테두리 처리 여부 결정 (각 테두리를 0으로 채움)
		cv::copyMakeBorder(mat_frame, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
	}
	else
	{
		mat_temp = mat_frame;
	}

	// r : 크기를 다루는 클래스 객체
	RECT r;

	// Picture Control의 크기를 r에 저장
	m_picture.GetClientRect(&r);
	cv::Size winSize(r.right, r.bottom);

	if (cimage_mfc) {
		cimage_mfc.ReleaseDC();
		delete cimage_mfc;
	}


	cimage_mfc.Create(winSize.width, winSize.height, 24);

	BITMAPINFO *bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	bitInfo->bmiHeader.biBitCount = bpp;
	bitInfo->bmiHeader.biWidth = mat_temp.cols;
	bitInfo->bmiHeader.biHeight = -mat_temp.rows;
	bitInfo->bmiHeader.biPlanes = 1;
	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo->bmiHeader.biCompression = BI_RGB;
	bitInfo->bmiHeader.biClrImportant = 0;
	bitInfo->bmiHeader.biClrUsed = 0;
	bitInfo->bmiHeader.biSizeImage = 0;
	bitInfo->bmiHeader.biXPelsPerMeter = 0;
	bitInfo->bmiHeader.biYPelsPerMeter = 0;


	//그레이스케일 인경우 팔레트가 필요
	if (bpp == 8)
	{
		RGBQUAD* palette = bitInfo->bmiColors;
		for (int i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}


	// Image is bigger or smaller than into destination rectangle
	// we use stretch in full rect

	if (mat_temp.cols == winSize.width  && mat_temp.rows == winSize.height)
	{
		// source and destination have same size
		// transfer memory block
		// NOTE: the padding border will be shown here. Anyway it will be max 3px width

		SetDIBitsToDevice(cimage_mfc.GetDC(),
			//destination rectangle
			0, 0, winSize.width, winSize.height,
			0, 0, 0, mat_temp.rows,
			mat_temp.data, bitInfo, DIB_RGB_COLORS);
	}
	else
	{
		// destination rectangle
		int destx = 0, desty = 0;
		int destw = winSize.width;
		int desth = winSize.height;

		// rectangle defined on source bitmap
		// using imgWidth instead of mat_temp.cols will ignore the padding border
		int imgx = 0, imgy = 0;
		int imgWidth = mat_temp.cols - border;
		int imgHeight = mat_temp.rows;

		StretchDIBits(cimage_mfc.GetDC(),
			destx, desty, destw, desth,
			imgx, imgy, imgWidth, imgHeight,
			mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
	}


	HDC dc = ::GetDC(m_picture.m_hWnd);
	cimage_mfc.BitBlt(dc, 0, 0);


	::ReleaseDC(m_picture.m_hWnd, dc);

	cimage_mfc.ReleaseDC();
	cimage_mfc.Destroy();

	CDialogEx::OnTimer(nIDEvent);


}


void CtestQDlg::OnStnClickedPicture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CtestQDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();


}


void CtestQDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CtestQDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	lpMMI->ptMinTrackSize.x = WINDOW_WIDTH;
	lpMMI->ptMinTrackSize.y = WINDOW_HEIGHT;

	lpMMI->ptMaxTrackSize.x = WINDOW_WIDTH;
	lpMMI->ptMaxTrackSize.y = WINDOW_HEIGHT;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

UINT CtestQDlg::UpdateLog(LPVOID _mothod) {
	CtestQDlg *pDlg = (CtestQDlg *)AfxGetApp()->GetMainWnd();


	//
	// 테스트가 진행중이지 않을 경우
	// 상태변수를 1로 바꾸고 테스트를 시작한다.

	pDlg->g_cs_status.Lock();
	pDlg->test_status = 1;
	pDlg->g_cs_status.Unlock();

	pDlg->setLog(L"테스트를 시작합니다.");


	//
	// Some Test func...
	//
	Sleep(5000);

	pDlg->setLog(L"테스트를 종료합니다.");


	pDlg->g_cs_status.Lock();
	pDlg->test_status = 0;
	pDlg->g_cs_status.Unlock();

	/*pDlg->m_list.InsertItem(0, L"MFC Thread Test");
	pDlg->m_list.SetItemText(0, 1, get_time().c_str());
	pDlg->m_StatusBar.SetText(get_date().c_str(), 2, 0);*/
	Sleep(1000);

	return 0;
}

void CtestQDlg::OnStnClickedBird()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CtestQDlg::OnBnClickedBtnOff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CtestQDlg *pDlg = (CtestQDlg *)AfxGetApp()->GetMainWnd();

<<<<<<< HEAD
	setLog(L"[IR] Off Button Clicked");

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IRReceiveCallbackRegYn == 0) {
		// 원할한 테스트를 위해 DLL API를 활용한 callback은 태그로 확인하여 등록
		fn_UUIRTSetReceiveCallback(hDrvHandle, &IRReceiveCallback, (void *)0xA5A5A5A5);
	}
	char	gIRCode[2048] =
		"0000 006C 0022 0002 0155 00A9 0015 0016 0015 0016 0015 0041 0015 0016 0015 0016 0015 0016 0015 0016 0015 0016 0015 0041 0015 0041 0015 0016 0015 0041 0015 0041 0015 0041 0015 0041 0015 0041 0015 0016 0015 0016 0015 0016 0015 0041 0015 0016 0015 0016 0015 0016 0015 0016 0015 0041 0015 0041 0015 0041 0015 0016 0015 0041 0015 0041 0015 0041 0015 0041 0015 0602 0155 0056 0015 0E4A";
	m_list.SetItemText(0, 1, L"IR Blaster로 Power Off Code를 송신합니다.");
	IRSend(gIRCode);

=======
	pDlg->m_list.InsertItem(0, L"[IR] OFF button Clicked");
	pDlg->m_list.SetItemText(0, 1, get_time().c_str());
	pDlg->m_StatusBar.SetText(get_date().c_str(), 2, 0);
>>>>>>> parent of 6bd8f60... Resolve a merge conflict
}


void CtestQDlg::OnBnClickedBtnOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CtestQDlg *pDlg = (CtestQDlg *)AfxGetApp()->GetMainWnd();

<<<<<<< HEAD
	setLog(L"[IR] On Button Clicked");
=======
	pDlg->m_list.InsertItem(0, L"[IR] On button Clicked");
	pDlg->m_list.SetItemText(0, 1, get_time().c_str());
	pDlg->m_StatusBar.SetText(get_date().c_str(), 2, 0);
}
>>>>>>> parent of 6bd8f60... Resolve a merge conflict


void CtestQDlg::OnBnClickedStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CtestQDlg::OnLvnItemchangedLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


<<<<<<< HEAD
	}
	else {
		setLog(L"이미 진행중입니다");
=======
void CtestQDlg::OnBnClickedBtnOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IRReceiveCallbackRegYn == 0) {
		// 원할한 테스트를 위해 DLL API를 활용한 callback은 태그로 확인하여 등록
		fn_UUIRTSetReceiveCallback(hDrvHandle, &IRReceiveCallback, (void *)0xA5A5A5A5);
>>>>>>> parent of 6bd8f60... Resolve a merge conflict
	}


	char	gIRCode[2048] =
		"0000 006C 0022 0002 0155 00A9 0015 0016 0015 0016 0015 0041 0015 0016 0015 0016 0015 0016 0015 0016 0015 0016 0015 0041 0015 0041 0015 0016 0015 0041 0015 0041 0015 0041 0015 0041 0015 0041 0015 0016 0015 0016 0015 0016 0015 0041 0015 0016 0015 0016 0015 0016 0015 0016 0015 0041 0015 0041 0015 0041 0015 0016 0015 0041 0015 0041 0015 0041 0015 0041 0015 0602 0155 0056 0015 0E4A";
	m_list.SetItemText(0, 1, L"IR Blaster로 Power On Code를 송신합니다.");
	IRSend(gIRCode);
}


void CtestQDlg::OnBnClickedBtnOff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IRReceiveCallbackRegYn == 0) {
		// 원할한 테스트를 위해 DLL API를 활용한 callback은 태그로 확인하여 등록
		fn_UUIRTSetReceiveCallback(hDrvHandle, &IRReceiveCallback, (void *)0xA5A5A5A5);
	}
	char	gIRCode[2048] =
		"0000 006C 0022 0002 0155 00A9 0015 0016 0015 0016 0015 0041 0015 0016 0015 0016 0015 0016 0015 0016 0015 0016 0015 0041 0015 0041 0015 0016 0015 0041 0015 0041 0015 0041 0015 0041 0015 0041 0015 0016 0015 0016 0015 0016 0015 0041 0015 0016 0015 0016 0015 0016 0015 0016 0015 0041 0015 0041 0015 0041 0015 0016 0015 0041 0015 0041 0015 0041 0015 0041 0015 0602 0155 0056 0015 0E4A";
	m_list.SetItemText(0, 1, L"IR Blaster로 Power Off Code를 송신합니다.");
	IRSend(gIRCode);
}


/// @brief wstring을 입력받아 list control에 출력한다.
/// 로그를 출력하기 위한 함수
/// 
int CtestQDlg::setLog(LPWSTR str_log) {
	CtestQDlg *pDlg = (CtestQDlg *)AfxGetApp()->GetMainWnd();
	
	pDlg->m_list.InsertItem(0, str_log);
	pDlg->m_list.SetItemText(0, 1, get_time().c_str());
	return 1;
}


/// @brief 리소스들을 초기화하고 배치한다.
/// 
/// 
void CtestQDlg::setResources(void)
{
	CtestQDlg *pDlg = (CtestQDlg *)AfxGetApp()->GetMainWnd();
	// SetWindowPos(NULL, x좌표, y좌표, 넓이, 높이, );
// 윈도우 크기 설정

	pDlg->SetWindowPos(NULL, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SWP_NOREPOSITION);
	pDlg->MoveWindow(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//
	// Status Bar 설정을 위한 초기화 진행
	m_StatusBar.Create(WS_CHILD | WS_VISIBLE | SBT_OWNERDRAW, CRect(0, 0, 0, 0), this, 0);


	int strPartDim[4] = { 40 , 100, 200, WINDOW_WIDTH - 1 };
	m_StatusBar.SetParts(4, strPartDim);

	m_StatusBar.SetText(version_info, 0, 0);
	m_StatusBar.SetText(team_info, 1, 0);
	m_StatusBar.SetText(get_date().c_str(), 2, 0);
	m_StatusBar.SetText(vender_info, 3, 0);

	//
	// List Control 설정을 위한 초기화 진행
	int m_list_width = WINDOW_WIDTH - (2 * WINDOW_MARGIN);
	int m_list_height = 100;
	m_list.MoveWindow(WINDOW_MARGIN - 10, 600 - m_list_height - WINDOW_MARGIN * 3, m_list_width, m_list_height);
	m_list.ModifyStyle(0, LVS_NOCOLUMNHEADER);

	// List Control의 크기를 얻어옴
	LV_COLUMN add_column;
	add_column.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	wchar_t *p_item_table[2] = { L"time", L"status" };
	int item_size_table[2] = { m_list_width - WINDOW_MARGIN - 80, 80 };

	for (int i = 0; i < 2; i++) {
		add_column.pszText = p_item_table[i];
		add_column.cx = item_size_table[i];
		add_column.fmt = LVCFMT_CENTER;
		m_list.InsertColumn(i + 1, &add_column);
	}

	g_cs_status.Lock();
	test_status = 0;
	g_cs_status.Unlock();

	setLog(L"프로그램을 시작합니다.");

	//
	//	그룹 묶기

	//
	// 1번박스
	// 반복 콤보박스
	m_box1.SetWindowPos(NULL, WINDOW_MARGIN - 10, WINDOW_MARGIN, 300, WINDOW_HEIGHT - m_list_height - WINDOW_MARGIN * 5, NULL);
	m_txt_repeat.MoveWindow(WINDOW_MARGIN + 10, WINDOW_MARGIN * 2, 50, 20);
	m_repeat_combo.MoveWindow(WINDOW_MARGIN + 100, WINDOW_MARGIN * 2, 100, 20);

	for (int i = 0; i < 12; i++) {
		wstringstream temp_num;
		temp_num << i + 1;
		m_repeat_combo.InsertString(i, temp_num.str().c_str());
	}
	m_repeat_combo.SetCurSel(11);
	m_btn_start.MoveWindow(WINDOW_MARGIN + 10, WINDOW_MARGIN + 300 + 10, 270, 50);

	m_txt_IR.MoveWindow(WINDOW_MARGIN + 10, WINDOW_MARGIN * 4 - 20, 100, 20);
	m_btn_on.MoveWindow(WINDOW_MARGIN + 10, WINDOW_MARGIN * 4, 120, 20);
	m_btn_off.MoveWindow(WINDOW_MARGIN + 150, WINDOW_MARGIN * 4, 120, 20);

	int m_picture_width = 256;
	int m_picture_height = 192;
	m_picture.MoveWindow(WINDOW_MARGIN + 10,
		WINDOW_MARGIN * 5,
		m_picture_width,
		m_picture_height);

}

void CtestQDlg::setIRBlaster(void) {
	//
	//
	// IR BLASTER 컨트롤 설정 초기화

	//If the handle is valid, try to get the function address.
	if (!loadDLL())
	{
		setLog(_T("uuirtdrv.dll을 로드할 수 없습니다. \n"));
		return;
	}

	if (!fn_UUIRTGetDrvInfo(&drvVersion))
	{
		setLog(_T("uirtdrv.dll의 버전을 검색할 수 없습니다. \n"));
		unLoadDLL();
		return;
	}

	if (drvVersion != 0x0100)
	{
		setLog(_T("uirtdrv.dll 버전이 맞지 않습니다. \n"));
		Sleep(1000);
		unLoadDLL();
		return;
	}

	hDrvHandle = fnUUIRTOpen();
	if (hDrvHandle == INVALID_HANDLE_VALUE)
	{
		DWORD err;

		err = GetLastError();

		if (err == UUIRTDRV_ERR_NO_DLL)
		{
			setLog(_T("USB-UIRT 드라이버를 찾을 수 없습니다. 드라이버를 설치하세요. \n"));
		}
		else if (err == UUIRTDRV_ERR_NO_DEVICE)
		{
			setLog(_T("USB-UIRT 디바이스를 연결할 수 없습니다. PC에 장비 연결을 확인하세요. \n"));
		}
		else if (err == UUIRTDRV_ERR_NO_RESP)
		{
			setLog(_T("USB-UIRT 장비에 연결되지 않았습니다. 연결을 다시 한번 확인하세요. \n"));
		}
		else if (err == UUIRTDRV_ERR_VERSION)
		{
			setLog(_T("USB-UIRT의 펌웨어가 API DLL과 호환되지 않습니다. 최신 버전의 API DLL을 확인하세요. \n"));
		}
		else
		{
			setLog(_T("USB-UIRT 초기화가 불가합니다.(알려지지 않은 에러) \n"));
		}

		unLoadDLL();
		return;
	}

	// Register a callback function for IR receive...
	fn_UUIRTSetReceiveCallback(hDrvHandle, &IRReceiveCallback, (void *)0xA5A5A5A5);
}