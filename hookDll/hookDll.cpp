// hookDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "hookDll.h"


// 这是导出变量的一个示例
HOOKDLL_API int nhookDll=0;

// 这是导出函数的一个示例。
HOOKDLL_API int fnhookDll(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 hookDll.h
ChookDll::ChookDll()
{
    return;
}


#define WM_My_mouseAll WM_USER + 1001    //自定义鼠标钩子消息，用于和主程序通信
#define WM_My_keyboardAll WM_USER + 1002 //自定义键盘钩子消息，用于和主程序通信
///////////////////////////////////////////////////////////////////////////////////
#pragma  data_seg("MySec")  //定义一个新节，将全局变量放入这个节中，用于共享  
HWND g_hWnd = NULL;
#pragma  data_seg()  
#pragma  comment(linker,"/section:MySec,RWS") //设置为共享的节 
//////////////////////////////////////////////////////////////////////////////////////////
HHOOK g_hMouseDll = NULL;
HHOOK g_hKeyBoarDll = NULL;

/*************************************************************回调函数*******************************************************************************/
LRESULT CALLBACK LowLevelKeyboardProc(_In_ int code, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	PKBDLLHOOKSTRUCT pk = (PKBDLLHOOKSTRUCT)lParam;
	  
	if (g_hWnd != NULL && code == HC_ACTION)
	{
		::SendMessage(g_hWnd, WM_My_keyboardAll, wParam, lParam); //有键盘消息时，将其发给主程序,让主程序处理	

	}
	return CallNextHookEx(g_hKeyBoarDll, code, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	PMSLLHOOKSTRUCT pm = (PMSLLHOOKSTRUCT)lParam;

	if (g_hWnd != NULL && nCode == HC_ACTION)
	{
		::SendMessage(g_hWnd, WM_My_mouseAll, wParam, lParam); //有鼠标消息时，将其发给主程序,让主程序处理
	}
	return CallNextHookEx(g_hMouseDll, nCode, wParam, lParam);
}

/****************************************************************设置Hook**********************************************************************************/
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
/****************************************************************卸载Hook**********************************************************************************/
extern "C" HOOKDLL_API void UnMouseHookAll()
{
	if (g_hMouseDll != 0) UnhookWindowsHookEx(g_hMouseDll);
}
extern "C" HOOKDLL_API void UnKeyBoarHook()
{
	if (g_hKeyBoarDll != 0) UnhookWindowsHookEx(g_hKeyBoarDll);
}