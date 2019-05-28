
// testQDlg.h: 헤더 파일
//

#pragma once


// CtestQDlg 대화 상자
class CtestQDlg : public CDialogEx
{
// 생성입니다.
public:
	CtestQDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTQ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 동영상 출력을 위한 변수
	CStatic m_picture;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// 상태표시줄 (Status Bar) 표현을 위한 변수
	CStatusBarCtrl m_StatusBar;

	VideoCapture *capture;
	Mat mat_frame;
	Mat dst, detected_edges;
	CImage cimage_mfc;

	int low_threshold = 50;
	int high_threshold = 150;

	afx_msg void OnStnClickedPicture();
	afx_msg void OnBnClickedOk();
};
