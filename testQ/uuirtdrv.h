
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the UUIRTDRV_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// UUIRTDRV_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef UUIRTDRV_EXPORTS
#define UUIRTDRV_API __declspec(dllexport)
#else
#define UUIRTDRV_API __declspec(dllimport)
#endif

// This class is exported from the uuirtdrv.dll
//class UUIRTDRV_API CUuirtdrv {
//public:
//	CUuirtdrv(void);
//	// TODO: add your methods here.
//};

typedef struct
{
	unsigned int fwVersion;
	unsigned int protVersion;
	unsigned char fwDateDay;
	unsigned char fwDateMonth;
	unsigned char fwDateYear;
} UUINFO, *PUUINFO;

typedef void *HUUHANDLE;

typedef void (WINAPI *PUUCALLBACKPROC) (char *IREventStr, void *userData);
typedef void (WINAPI *PLEARNCALLBACKPROC) (unsigned int progress, unsigned int sigQuality, unsigned long carrierFreq, void *userData);

extern UUIRTDRV_API int nUuirtdrv;

UUIRTDRV_API HUUHANDLE PASCAL UUIRTOpen(void);

UUIRTDRV_API BOOL PASCAL UUIRTClose(HUUHANDLE hHandle);

UUIRTDRV_API BOOL PASCAL UUIRTGetDrvInfo(unsigned int *puDrvVersion);

UUIRTDRV_API BOOL PASCAL UUIRTGetUUIRTInfo(HUUHANDLE hHandle, PUUINFO puuInfo);

UUIRTDRV_API BOOL PASCAL UUIRTGetUUIRTConfig(HUUHANDLE hHandle, PUINT32 puConfig);

UUIRTDRV_API BOOL PASCAL UUIRTSetUUIRTConfig(HUUHANDLE hHandle, UINT32 uConfig);

UUIRTDRV_API BOOL PASCAL UUIRTTransmitIR(HUUHANDLE hHandle, char *IRCode, int codeFormat, int repeatCount, int inactivityWaitTime, HANDLE hEvent, void *reserved0, void *reserved1);

UUIRTDRV_API BOOL PASCAL UUIRTLearnIR(HUUHANDLE hHandle, int codeFormat, char *IRCode, PLEARNCALLBACKPROC progressProc, void *userData, BOOL *pAbort, unsigned int param1, void *reserved0, void *reserved1);

UUIRTDRV_API BOOL PASCAL UUIRTSetReceiveCallback(HUUHANDLE hHandle, PUUCALLBACKPROC receiveProc, void *userData);

#define UUIRTDRV_ERR_NO_DEVICE 0x20000001
#define UUIRTDRV_ERR_NO_RESP   0x20000002
#define UUIRTDRV_ERR_NO_DLL    0x20000003
#define UUIRTDRV_ERR_VERSION   0x20000004

typedef HUUHANDLE(WINAPI *pfn_UUIRTOpen)		(void);
typedef BOOL(WINAPI *pfn_UUIRTClose)	(HUUHANDLE hHandle);
typedef BOOL(WINAPI *pfn_UUIRTGetDrvInfo)(unsigned int *puDrvVersion);
typedef BOOL(WINAPI *pfn_UUIRTGetUUIRTInfo)(HUUHANDLE hHandle, PUUINFO puuInfo);
typedef BOOL(WINAPI *pfn_UUIRTGetUUIRTConfig)(HUUHANDLE hHandle, PUINT32 puConfig);
typedef BOOL(WINAPI *pfn_UUIRTSetUUIRTConfig)(HUUHANDLE hHandle, UINT32 uConfig);
typedef BOOL(WINAPI *pfn_UUIRTSetReceiveCallback)(HUUHANDLE hHandle, PUUCALLBACKPROC receiveProc, void *userData);
typedef	BOOL(WINAPI *pfn_UUIRTTransmitIR)(HUUHANDLE hHandle, char *IRCode, int codeFormat, int repeatCount, int inactivityWaitTime, HANDLE hEvent, void *reserved0, void *reserved1);
typedef	BOOL(WINAPI *pfn_UUIRTLearnIR)(HUUHANDLE hHandle, int codeFormat, char *IRCode, PLEARNCALLBACKPROC progressProc, void *userData, BOOL *pAbort, unsigned int param1, void *reserved0, void *reserved1);

#define UUIRTDRV_CFG_LEDRX		0x00013
#define UUIRTDRV_CFG_LEDTX		0x0002
#define UUIRTDRV_CFG_LEGACYRX	0x0004

#define UUIRTDRV_IRFMT_UUIRT	0x0000
#define UUIRTDRV_IRFMT_PRONTO	0x0010

#define UUIRTDRV_IRFMT_LEARN_FORCERAW	0x0100
#define UUIRTDRV_IRFMT_LEARN_FORCESTRUC	0x0200
#define UUIRTDRV_IRFMT_LEARN_FORCEFREQ	0x0400
#define UUIRTDRV_IRFMT_LEARN_FREQDETECT	0x0800

// --------------------------------------------------------------------------
// IR CONTROL AREA 아래 영역은 IR CONtrol 에 필요한 전역 변수

HINSTANCE		hinstLib = NULL;
HUUHANDLE		hDrvHandle;
unsigned int	drvVersion;

char	gIRCode[2048] = "0000 0071 0000 0032 0080 0040 0010 0010 0010 0030 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0030 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0030 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0030 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0030 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0010 0030 0010 0aad";
int		gIRCodeFormat = UUIRTDRV_IRFMT_PRONTO;
char	gLearnBuffer[2048];
int		gLearnFormat;
int		IRReceiveCallbackRegYn = 0;

pfn_UUIRTOpen				fnUUIRTOpen;
pfn_UUIRTClose				fnUUIRTClose;
pfn_UUIRTGetDrvInfo			fn_UUIRTGetDrvInfo;
pfn_UUIRTGetUUIRTInfo		fn_UUIRTGetUUIRTInfo;
pfn_UUIRTGetUUIRTConfig		fn_UUIRTGetUUIRTConfig;
pfn_UUIRTSetUUIRTConfig		fn_UUIRTSetUUIRTConfig;
pfn_UUIRTSetReceiveCallback	fn_UUIRTSetReceiveCallback;
pfn_UUIRTTransmitIR			fn_UUIRTTransmitIR;
pfn_UUIRTLearnIR			fn_UUIRTLearnIR;

UUINFO UsbUirtInfo;
UINT32 uConfig;
char ch;

// --------------------------------------------------------------------------

/*****************************************************************************/
/* unLoadDLL: Disconnects from .DLL and unloads it from memory				 */
/*																			 */
/* returns: none															 */
/*																			 */
/*****************************************************************************/
void unLoadDLL(void)
{
	if (hinstLib)
		FreeLibrary(hinstLib);
	hinstLib = NULL;
}

/*****************************************************************************/
/* loadDLL: Establish contact with the UUIRTDRV dll and assign function      */
/*			entry points													 */
/*																			 */
/* returns: TRUE on success, FALSE on failure								 */
/*																			 */
/*****************************************************************************/
BOOL loadDLL(void)
{
	// Get a handle to the DLL module.

	hinstLib = LoadLibrary(L"uuirtdrv");

	// If the handle is valid, try to get the function address.

	if (hinstLib != NULL)
	{
		fnUUIRTOpen = (pfn_UUIRTOpen)GetProcAddress(hinstLib, "UUIRTOpen");
		fnUUIRTClose = (pfn_UUIRTClose)GetProcAddress(hinstLib, "UUIRTClose");
		fn_UUIRTGetDrvInfo = (pfn_UUIRTGetDrvInfo)GetProcAddress(hinstLib, "UUIRTGetDrvInfo");
		fn_UUIRTGetUUIRTInfo = (pfn_UUIRTGetUUIRTInfo)GetProcAddress(hinstLib, "UUIRTGetUUIRTInfo");
		fn_UUIRTGetUUIRTConfig = (pfn_UUIRTGetUUIRTConfig)GetProcAddress(hinstLib, "UUIRTGetUUIRTConfig");
		fn_UUIRTSetUUIRTConfig = (pfn_UUIRTSetUUIRTConfig)GetProcAddress(hinstLib, "UUIRTSetUUIRTConfig");
		fn_UUIRTSetReceiveCallback = (pfn_UUIRTSetReceiveCallback)GetProcAddress(hinstLib, "UUIRTSetReceiveCallback");
		fn_UUIRTTransmitIR = (pfn_UUIRTTransmitIR)GetProcAddress(hinstLib, "UUIRTTransmitIR");
		fn_UUIRTLearnIR = (pfn_UUIRTLearnIR)GetProcAddress(hinstLib, "UUIRTLearnIR");

		if (!fnUUIRTOpen ||
			!fnUUIRTClose ||
			!fn_UUIRTGetDrvInfo ||
			!fn_UUIRTGetUUIRTInfo ||
			!fn_UUIRTGetUUIRTConfig ||
			!fn_UUIRTSetUUIRTConfig ||
			!fn_UUIRTSetReceiveCallback ||
			!fn_UUIRTTransmitIR ||
			!fn_UUIRTLearnIR)
		{
			unLoadDLL();
			return FALSE;
		}

		return TRUE;
	}
	return FALSE;
}

/*****************************************************************************/
/* IRReceiveCallback: Receive IR Callback Procedure						     */
/*																			 */
/* This procedure is called by the UUIRT .dll whenever an IRcode is received */
/* The IRcode is passed to the callback in UIR format.						 */
/*																			 */
/*****************************************************************************/
void WINAPI IRReceiveCallback(char *IREventStr, void *userData)
{
	COORD coord;
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO conInfo;

	// Move the cursor to the bottom of the screen
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdOut, &conInfo);
	coord.X = conInfo.srWindow.Left;
	coord.Y = conInfo.srWindow.Bottom - 1;
	SetConsoleCursorPosition(hStdOut, coord);

	//printf("<IR Receive: Code = %s, UserData = %08x!!!\n", IREventStr, (UINT32)userData);

	// Move the cursor back to its original position
	SetConsoleCursorPosition(hStdOut, conInfo.dwCursorPosition);
}

/*****************************************************************************/
/* IRLearnCallback: Learn IR Callback Procedure						         */
/*																			 */
/* This procedure is called by the UUIRT .dll during the LEARN process		 */
/* to allow user feedback on Learn progress, signal quality and (if needed)  */
/* carrier frequency.														 */
/*																			 */
/*****************************************************************************/
void WINAPI IRLearnCallback(unsigned int progress, unsigned int sigQuality, unsigned long carrierFreq, void *userData)
{
	COORD coord;
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO conInfo;

	// Move the cursor to the bottom of the screen
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdOut, &conInfo);
	coord.X = conInfo.srWindow.Left;
	coord.Y = conInfo.srWindow.Bottom - 2;
	SetConsoleCursorPosition(hStdOut, coord);

	//printf("<Learn Progress: %d%%, Signal = %d%%, Freq = %ld, UserData = %08x!!!\n", progress, sigQuality & 0xff, carrierFreq, (UINT32)userData);

	// Move the cursor back to its original position
	SetConsoleCursorPosition(hStdOut, conInfo.dwCursorPosition);
}


/*****************************************************************************/
/* LearnThread: Learn IR Thread function									 */
/*																			 */
/* This function executes as a separate thread which calls the UUIRTLearnIR  */
/* function.  In this example, the UUIRTLearnIR function is called from this */
/* separate thread to allow the main console thread to continue monitoring   */
/* the keyboard so that the user may abort the learn process. Depending on   */
/* the application, the UUIRTLearnIR may be called from the main thread if   */
/* an asynchronous method (such as a timer) is available to monitor user     */
/* input.																	 */
/*																			 */
/*****************************************************************************/
DWORD WINAPI LearnThread(LPVOID lpParameter)
{
	BOOL *pbAbortLearn = (BOOL *)lpParameter;

	//printf("\nCalling LearnIR...");
	if (!fn_UUIRTLearnIR(hDrvHandle, gLearnFormat, gLearnBuffer, IRLearnCallback, (void *)0x5a5a5a5a, pbAbortLearn, 0, NULL, NULL))
	{
		//printf("\n\t*** ERROR calling UUIRTLearnIR! ***\n");
	}
	else
	{
		if (!*pbAbortLearn)
		{
			//printf("...Done...IRCode = %s\n", gLearnBuffer);
			strcpy_s(gIRCode, gLearnBuffer);
			gIRCodeFormat = gLearnFormat & 0xff;
		}
		else
		{
			//printf("...*** LEARN ABORTED ***\n");
		}
	}
	return 0;
}

/*****************************************************************************/
/* IRSend: 인자값으로 전달된 IR Cocdd를 IR Blaster로 출력                    */
/*																			 */
/*																			 */
/*****************************************************************************/

void IRSend(char* lpParameter) {
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	COORD coord;
	DWORD cWritten;

	// Move cursor to top-left of screen
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdOut, &conInfo);
	coord.X = conInfo.srWindow.Left;
	coord.Y = conInfo.srWindow.Top;
	SetConsoleCursorPosition(hStdOut, coord);

	// Clear screen
	FillConsoleOutputCharacter(
		hStdOut,          // screen buffer handle 
		' ',       // fill with spaces 
		(conInfo.srWindow.Right - conInfo.srWindow.Left + 1)*(conInfo.srWindow.Bottom - conInfo.srWindow.Top + 1),            // number of cells to fill 
		coord,            // first cell to write to 
		&cWritten);       // actual number written 


	// Retrieve information about the USB-UIRT device...
	if (!fn_UUIRTGetUUIRTInfo(hDrvHandle, &UsbUirtInfo))
	{
		//printf("\t*** ERROR Retrieving USB-UIRT Information! ***\n");
	}
	else
	{
		/*
		printf("\tUSB-UIRT Info: FirmwareVer=%d.%d ProtVer=%d.%d FirmwareDate=%d/%d/%d\n",
			UsbUirtInfo.fwVersion >> 8,
			UsbUirtInfo.fwVersion & 0xff,
			UsbUirtInfo.protVersion >> 8,
			UsbUirtInfo.protVersion & 0xff,
			UsbUirtInfo.fwDateMonth,
			UsbUirtInfo.fwDateDay,
			UsbUirtInfo.fwDateYear + 2000);
			*/
	}

	if (!fn_UUIRTGetUUIRTConfig(hDrvHandle, &uConfig))
	{
		//printf("\t*** ERROR Retrieving USB-UIRT Configuration Info! ***\n");
	}

	//printf("\nTransmitting IR Code (blocking)...");
	if (!fn_UUIRTTransmitIR(hDrvHandle,
		lpParameter /* IRCode */,
		gIRCodeFormat /* codeFormat */,
		10 /* repeatCount */,
		0 /* inactivityWaitTime */,
		NULL /* hEvent */,
		NULL /* reserved1 */,
		NULL /* reserved2 */
	))
	{
		//printf("\n\t*** ERROR calling UUIRTTransmitIR! ***\n");
	}
	else
	{
		//printf("...Returned from call (Done)!\n");
	}
	//printf("Press any key to continue...");
	//_getch();
	//break;
}
