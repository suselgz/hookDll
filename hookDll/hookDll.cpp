// hookDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "hookDll.h"


// ���ǵ���������һ��ʾ��
HOOKDLL_API int nhookDll=0;

// ���ǵ���������һ��ʾ����
HOOKDLL_API int fnhookDll(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� hookDll.h
ChookDll::ChookDll()
{
    return;
}


#define WM_My_mouseAll WM_USER + 1001    //�Զ�����깳����Ϣ�����ں�������ͨ��
#define WM_My_keyboardAll WM_USER + 1002 //�Զ�����̹�����Ϣ�����ں�������ͨ��
///////////////////////////////////////////////////////////////////////////////////
#pragma  data_seg("MySec")  //����һ���½ڣ���ȫ�ֱ�������������У����ڹ���  
HWND g_hWnd = NULL;
#pragma  data_seg()  
#pragma  comment(linker,"/section:MySec,RWS") //����Ϊ����Ľ� 
//////////////////////////////////////////////////////////////////////////////////////////
HHOOK g_hMouseDll = NULL;
HHOOK g_hKeyBoarDll = NULL;

/*************************************************************�ص�����*******************************************************************************/
LRESULT CALLBACK LowLevelKeyboardProc(_In_ int code, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	PKBDLLHOOKSTRUCT pk = (PKBDLLHOOKSTRUCT)lParam;
	  
	if (g_hWnd != NULL && code == HC_ACTION)
	{
		::SendMessage(g_hWnd, WM_My_keyboardAll, wParam, lParam); //�м�����Ϣʱ�����䷢��������,����������	

	}
	return CallNextHookEx(g_hKeyBoarDll, code, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	PMSLLHOOKSTRUCT pm = (PMSLLHOOKSTRUCT)lParam;

	if (g_hWnd != NULL && nCode == HC_ACTION)
	{
		::SendMessage(g_hWnd, WM_My_mouseAll, wParam, lParam); //�������Ϣʱ�����䷢��������,����������
	}
	return CallNextHookEx(g_hMouseDll, nCode, wParam, lParam);
}

/****************************************************************����Hook**********************************************************************************/
extern "C" HOOKDLL_API void SetMouseHookAll(HWND hwnd)
{
	g_hWnd = hwnd;
	g_hMouseDll = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, GetModuleHandle(L"hookDll.dll"), 0);
}

extern "C" HOOKDLL_API void SetKeyBoarHookAll(HWND hwnd)
{
	g_hWnd = hwnd;
	g_hKeyBoarDll = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(L"hookDll.dll"), 0);
}
/****************************************************************ж��Hook**********************************************************************************/
extern "C" HOOKDLL_API void UnMouseHookAll()
{
	if (g_hMouseDll != 0) UnhookWindowsHookEx(g_hMouseDll);
}
extern "C" HOOKDLL_API void UnKeyBoarHook()
{
	if (g_hKeyBoarDll != 0) UnhookWindowsHookEx(g_hKeyBoarDll);
}