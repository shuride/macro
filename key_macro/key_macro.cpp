#include "stdafx.h"
#include "key_macro.h"
#include "key_macroDlg.h"
#include "MmTimer.h"
#include "AppIni.h"
#include "common.h"
#include "GdiObjects.h"


BEGIN_MESSAGE_MAP(Ckey_macroApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

Ckey_macroApp::Ckey_macroApp()
{
}

// 유일한 Ckey_macroApp 개체입니다.
Ckey_macroApp theApp;

static CMmTimer _mmtm;

// Ckey_macroApp 초기화
BOOL Ckey_macroApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// !!! 응용프로그램이 이미 실행중인지 검사하여, 
	// 실행중일 때는 현재 실행중인 응용프로그램에 초기화 메시지 전송
	if (ApplicationAlreadyExist ("#32770", "macro-windows"))	{
		return FALSE;
	}

	AfxEnableControlContainer();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("macro-windows"));

	g_ini.LoadData ();
	_mmtm.Start(1);

	InitGdiObjects ();

	Ckey_macroDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	
	if (nResponse == IDOK) {
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	DeinitGdiObjects ();

	_mmtm.Stop ();
	g_ini.SaveData ();

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}
