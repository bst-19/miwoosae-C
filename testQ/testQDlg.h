﻿
// testQDlg.h: 헤더 파일
//

#pragma once
#include "systems.h"
#include "StopWatch.h"

// CtestQDlg 대화 상자
class CtestQDlg : public CDialogEx
{

#define WINDOW_WIDTH		(350)
#define WINDOW_HEIGHT		(600)
#define WINDOW_MARGIN		(25)

#define LOG_ERR			(900)
#define LOG_NORM		(800)
#define LOG_SUCCESS		(700)

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
	int setLog(LPWSTR str_log);
	void setResources(void);
	void setIRBlaster(void);
	void bootTimeAval(void);

	// 동영상 출력을 위한 변수	// 동영상 출력을 위한 변수
	CStatic m_picture;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	VideoCapture *capture;
	Mat mat_frame;
	Mat mat_tmp_frame;
	Mat diff_frame;
	Mat dst, detected_edges;
	CImage cimage_mfc;
	CImage cimage_mfc_clone;
	int *pos;
	int cropYn = 0;
	int startYn = 0;
	STOPWATCH CWatch;
	char *dir = "img_res/";
	char *base = "img_res/0.jpg";
	int file_name = 0;

	int low_threshold = 50;
	int high_threshold = 150;

	int changeTag = 0;

	// 이미지 유사도를 위한 변수 선언
	int h_bins = 50, s_bins = 60;
	int histSize[2] = { h_bins, s_bins };
	float h_ranges[2] = { 0, 180 };
	float s_ranges[2] = { 0, 256 };
	const float * ranges[2] = { h_ranges, s_ranges };
	int channels[2] = { 0, 1 };

	Mat src_base, re_base, hist_base;
	Mat dst_target, re_target, hist_target;

	// 상태표시줄 (Status Bar) 표현을 위한 변수
	CStatusBarCtrl m_StatusBar;
	LPWSTR version_info = L"ver 0.1";
	LPWSTR team_info = L"team BST";
	LPWSTR time_info;
	LPWSTR vender_info = L"ID SW개발실";

	// 현재상태 갱신을 위한 변수
	enum ThreadWorking {
		RUN = 0
	};

	CCriticalSection g_cs_status;
	int test_status;

	bool m_bThreadStart;
	CWinThread *m_pThread;
	ThreadWorking m_ThreadWorkType;

	static UINT UpdateLog(LPVOID _mothod);
	static UINT ThreadFirst(LPVOID _mothod);


	afx_msg void OnStnClickedPicture();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_list;
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);


	// 이미지를 출력하기 위한 변수
	CStatic m_bird_pic;
	afx_msg void OnStnClickedBird();
	CButton m_btn_start;
	CComboBox m_repeat_combo;
	CStatic m_txt_repeat;
	CStatic m_txt_IR;
	CButton m_btn_off;
	CButton m_btn_on;
	CStatic m_box1;

	afx_msg void OnLvnItemchangedLog(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnOn();
	afx_msg void OnBnClickedBtnOff();
	void BtnOnFunc(int param);
	void BtnOffFunc(int param);
	void StartFunc(int param);
	void StopFunc(int param);

	void makeExcel(int num);

	wchar_t* intToWchar(int num);
	//	afx_msg void OnBnClickedStart();


	afx_msg void OnBnClickedStart2();
	//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCrop();
	CButton m_btn_crop;
	afx_msg void OnBnClickedStart();
	
	CButton m_btn_stop;
	afx_msg void OnBnClickedStop();
	
	CEdit m_edit_diff;
	CEdit m_edit_time;

	int repeatCnt = 0;
	int repeatNow = 0;

	wchar_t result[12][50];
	CButton m_btn_nocrop;
	afx_msg void OnBnClickedCrop2();
	CStatic m_txt_etc;
	CButton m_chbx_etc;
};
