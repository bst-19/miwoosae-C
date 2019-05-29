
// testQDlg.h: 헤더 파일
//

#pragma once
#include "systems.h"



// CtestQDlg 대화 상자
class CtestQDlg : public CDialogEx
{

	#define WINDOW_WIDTH		(1000)
	#define WINDOW_HEIGHT		(600)
	#define WINDOW_MARGIN		(25)

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
	VideoCapture *capture;
	Mat mat_frame;
	Mat dst, detected_edges;
	CImage cimage_mfc;

	int low_threshold = 50;
	int high_threshold = 150;

	// 상태표시줄 (Status Bar) 표현을 위한 변수
	CStatusBarCtrl m_StatusBar;
	LPWSTR version_info = L"ver 0.1";
	LPWSTR team_info = L"team BST";
	LPWSTR time_info;
	LPWSTR vender_info = L"LG전자 BS사업본부 ID SW개발실";

	// 현재상태 갱신을 위한 변수
	enum ThreadWorking {
		RUN = 0
	};

	bool m_bThreadStart;
	CWinThread *m_pThread;
	ThreadWorking m_ThreadWorkType;
	
	static UINT UpdateLog(LPVOID _mothod);

	afx_msg void OnStnClickedPicture();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_list;
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	CStatic m_box1;
	CStatic m_box2;
	CStatic m_box3;

	// 이미지를 출력하기 위한 변수
	CStatic m_bird_pic;
	afx_msg void OnStnClickedBird();
	CButton m_btn_start;
	CComboBox m_repeat_combo;
	CStatic m_txt_repeat;
	CStatic m_txt_IR;
	CButton m_btn_off;
	CButton m_btn_on;
};
