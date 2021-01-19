#include "MyHook.h"
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QLibrary> 
#include <Windows.h>

#pragma execution_character_set("utf-8")

#define WM_My_mouseAll WM_USER + 1001    //自定义鼠标钩子消息，用于和主程序通信
#define WM_My_keyboardAll WM_USER + 1002    //自定义鼠标钩子消息，用于和主程序通信

typedef void(*Mouse)(HWND); //定义函数指针，以备调用
typedef void(*UnMouse)(); //定义函数指针，以备调用
typedef void(*Keyboard)(HWND); //定义函数指针，以备调用
typedef void(*UnKeyboard)(); //定义函数指针，以备调用

MyHook::MyHook(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.MouseHookButton, SIGNAL(clicked()), this, SLOT(MouseHookButton()));
	connect(ui.MouseUnHookButton, SIGNAL(clicked()), this, SLOT(MouseUnHookButton()));
	connect(ui.KeyboardHookButton, SIGNAL(clicked()), this, SLOT(KeyboardHookButton()));
	connect(ui.KeyboardUnHookButton, SIGNAL(clicked()), this, SLOT(KeyboardUnHookButton()));
}

void MyHook::MouseHookButton()
{
#ifdef _DEBUG    
	QLibrary mylib("hookDll_d.dll"); //声明所用到的dll文件  
#else
	QLibrary mylib("hookDll_r.dll"); //声明所用到的dll文件  
#endif
	if (mylib.load())              //判断是否正确加载  
	{
		Mouse hook = (Mouse)mylib.resolve("SetMouseHookAll"); //取得 SetMouseHookAll() 函数地址
		if (hook)                                             //判断是否成功连接上 SetMouseHookAll() 函数  
		{
			ui.label2->setText("MouseHook成功");
			hook((HWND)this->winId()); //这里函数指针调用dll中的 SetMouseHookAll() 函数  
		}
		else ui.label2->setText("未找到函数，请检查是否有误");
	}
	else ui.label2->setText("DLL文件加载失败");
}

void MyHook::MouseUnHookButton()
{
#ifdef _DEBUG    
	QLibrary mylib("hookDll_d.dll"); //声明所用到的dll文件  
#else
	QLibrary mylib("hookDll_r.dll"); //声明所用到的dll文件  
#endif
	if (mylib.load())              //判断是否正确加载  
	{
		UnMouse unhook = (UnMouse)mylib.resolve("UnMouseHookAll");
		if (unhook)                                         
		{
			ui.label2->setText("卸载MouseHook成功");
			unhook(); //这里函数指针调用dll中的 UnMouseHookAll() 函数  
		}
		else ui.label2->setText("未找到函数，请检查是否有误");
	}
	else ui.label2->setText("DLL文件加载失败");
}

void MyHook::KeyboardHookButton()
{
#ifdef _DEBUG    
	QLibrary mylib("hookDll_d.dll"); //声明所用到的dll文件  
#else
	QLibrary mylib("hookDll_r.dll"); //声明所用到的dll文件  
#endif
	if (mylib.load())              //判断是否正确加载  
	{
		Mouse hook = (Mouse)mylib.resolve("SetKeyBoarHookAll"); //取得 SetKeyBoarHookAll() 函数地址
		if (hook)                                               //判断是否成功连接上 SetKeyBoarHookAll() 函数  
		{
			ui.label2->setText("KeyboardHook成功");
			hook((HWND)this->winId()); //这里函数指针调用dll中的 SetKeyBoarHookAll() 函数  
		}
		else ui.label2->setText("未找到函数，请检查是否有误");
	}
	else ui.label2->setText("DLL文件加载失败");
}

void MyHook::KeyboardUnHookButton()
{
#ifdef _DEBUG    
	QLibrary mylib("hookDll_d.dll"); //声明所用到的dll文件  
#else
	QLibrary mylib("hookDll_r.dll"); //声明所用到的dll文件  
#endif
	if (mylib.load())             //判断是否正确加载  
	{
		UnMouse unhook = (UnMouse)mylib.resolve("UnKeyBoarHook");
		if (unhook)
		{
			ui.label2->setText("卸载KeyboardHook成功");
			unhook(); //这里函数指针调用dll中的 UnMouseHookAll() 函数  
		}
		else ui.label2->setText("未找到函数，请检查是否有误");
	}
	else ui.label2->setText("DLL文件加载失败");
}

bool MyHook::nativeEvent(const QByteArray &eventType, void *message, long *result) //事件过滤
{
	MSG* pMsg = reinterpret_cast<MSG*>(message);
	
	if (pMsg->message == WM_My_mouseAll)
	{
		bool okMouse = callbackMouse(pMsg);
		return okMouse;
	}

	if (pMsg->message == WM_My_keyboardAll)
	{
		bool okKeyboard = callbackKeyboard(pMsg);
		return okKeyboard;
	}

	return false;
}

bool MyHook::callbackMouse(MSG *pmsg)
{
	PMSLLHOOKSTRUCT pm = (PMSLLHOOKSTRUCT)pmsg->lParam;
	int code = (UINT)pmsg->wParam;
	switch (code)
	{
	case 512:
		ui.lineEdit->setText(QString("鼠标移动（%1，%2)").arg(pm->pt.x).arg(pm->pt.y));
		break;
	case 513:
		ui.lineEdit2->setText("按下左键");
		break;
	case 514:
		ui.lineEdit2->setText("弹起左键");
		break;
	case 516:
		ui.lineEdit2->setText("按下右键");
		break;
	case 517:
		ui.lineEdit2->setText("弹起右键");
		break;
	case 519:
		ui.lineEdit2->setText("按下滚轮");
		break;
	case 520:
		ui.lineEdit2->setText("弹起滚轮");
		break;
	case 522:
		if (pm->mouseData == 7864320)
		{
			ui.lineEdit2->setText("滚轮上滚");
		}
		if (pm->mouseData == -7864320)
		{
			ui.lineEdit2->setText("滚轮下滚");
		}
		break;
	case 523:
		if (pm->mouseData == 131072)
		{
			ui.lineEdit2->setText("按下上侧键");
		}
		if (pm->mouseData == 65536)
		{
			ui.lineEdit2->setText("按下下侧键");
		}
		break;
	case 524:
		ui.lineEdit2->setText("弹起侧键");
		break;
	default:
		ui.lineEdit2->setText("按下其他键");
		break;
	}
	return true;
}

bool MyHook::callbackKeyboard(MSG *msg)
{
	PKBDLLHOOKSTRUCT pk = (PKBDLLHOOKSTRUCT)msg->lParam; 

	//if (msg->wParam == WM_KEYDOWN && pk->vkCode == VK_HOME)
	//{
	//	QMessageBox::information(NULL, "键盘消息", "按下Home键");
	//}
	//if (msg->wParam == WM_KEYUP && pk->vkCode == VK_END)
	//{
	//	QMessageBox::information(NULL, "键盘消息", "弹起End键");

	if (msg->wParam == WM_KEYUP) ui.lineEdit3->setText(QString::number(pk->vkCode));

	return true;
}