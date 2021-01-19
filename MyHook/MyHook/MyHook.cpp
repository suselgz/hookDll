#include "MyHook.h"
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QLibrary> 
#include <Windows.h>

#pragma execution_character_set("utf-8")

#define WM_My_mouseAll WM_USER + 1001    //�Զ�����깳����Ϣ�����ں�������ͨ��
#define WM_My_keyboardAll WM_USER + 1002    //�Զ�����깳����Ϣ�����ں�������ͨ��

typedef void(*Mouse)(HWND); //���庯��ָ�룬�Ա�����
typedef void(*UnMouse)(); //���庯��ָ�룬�Ա�����
typedef void(*Keyboard)(HWND); //���庯��ָ�룬�Ա�����
typedef void(*UnKeyboard)(); //���庯��ָ�룬�Ա�����

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
	QLibrary mylib("hookDll_d.dll"); //�������õ���dll�ļ�  
#else
	QLibrary mylib("hookDll_r.dll"); //�������õ���dll�ļ�  
#endif
	if (mylib.load())              //�ж��Ƿ���ȷ����  
	{
		Mouse hook = (Mouse)mylib.resolve("SetMouseHookAll"); //ȡ�� SetMouseHookAll() ������ַ
		if (hook)                                             //�ж��Ƿ�ɹ������� SetMouseHookAll() ����  
		{
			ui.label2->setText("MouseHook�ɹ�");
			hook((HWND)this->winId()); //���ﺯ��ָ�����dll�е� SetMouseHookAll() ����  
		}
		else ui.label2->setText("δ�ҵ������������Ƿ�����");
	}
	else ui.label2->setText("DLL�ļ�����ʧ��");
}

void MyHook::MouseUnHookButton()
{
#ifdef _DEBUG    
	QLibrary mylib("hookDll_d.dll"); //�������õ���dll�ļ�  
#else
	QLibrary mylib("hookDll_r.dll"); //�������õ���dll�ļ�  
#endif
	if (mylib.load())              //�ж��Ƿ���ȷ����  
	{
		UnMouse unhook = (UnMouse)mylib.resolve("UnMouseHookAll");
		if (unhook)                                         
		{
			ui.label2->setText("ж��MouseHook�ɹ�");
			unhook(); //���ﺯ��ָ�����dll�е� UnMouseHookAll() ����  
		}
		else ui.label2->setText("δ�ҵ������������Ƿ�����");
	}
	else ui.label2->setText("DLL�ļ�����ʧ��");
}

void MyHook::KeyboardHookButton()
{
#ifdef _DEBUG    
	QLibrary mylib("hookDll_d.dll"); //�������õ���dll�ļ�  
#else
	QLibrary mylib("hookDll_r.dll"); //�������õ���dll�ļ�  
#endif
	if (mylib.load())              //�ж��Ƿ���ȷ����  
	{
		Mouse hook = (Mouse)mylib.resolve("SetKeyBoarHookAll"); //ȡ�� SetKeyBoarHookAll() ������ַ
		if (hook)                                               //�ж��Ƿ�ɹ������� SetKeyBoarHookAll() ����  
		{
			ui.label2->setText("KeyboardHook�ɹ�");
			hook((HWND)this->winId()); //���ﺯ��ָ�����dll�е� SetKeyBoarHookAll() ����  
		}
		else ui.label2->setText("δ�ҵ������������Ƿ�����");
	}
	else ui.label2->setText("DLL�ļ�����ʧ��");
}

void MyHook::KeyboardUnHookButton()
{
#ifdef _DEBUG    
	QLibrary mylib("hookDll_d.dll"); //�������õ���dll�ļ�  
#else
	QLibrary mylib("hookDll_r.dll"); //�������õ���dll�ļ�  
#endif
	if (mylib.load())             //�ж��Ƿ���ȷ����  
	{
		UnMouse unhook = (UnMouse)mylib.resolve("UnKeyBoarHook");
		if (unhook)
		{
			ui.label2->setText("ж��KeyboardHook�ɹ�");
			unhook(); //���ﺯ��ָ�����dll�е� UnMouseHookAll() ����  
		}
		else ui.label2->setText("δ�ҵ������������Ƿ�����");
	}
	else ui.label2->setText("DLL�ļ�����ʧ��");
}

bool MyHook::nativeEvent(const QByteArray &eventType, void *message, long *result) //�¼�����
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
		ui.lineEdit->setText(QString("����ƶ���%1��%2)").arg(pm->pt.x).arg(pm->pt.y));
		break;
	case 513:
		ui.lineEdit2->setText("�������");
		break;
	case 514:
		ui.lineEdit2->setText("�������");
		break;
	case 516:
		ui.lineEdit2->setText("�����Ҽ�");
		break;
	case 517:
		ui.lineEdit2->setText("�����Ҽ�");
		break;
	case 519:
		ui.lineEdit2->setText("���¹���");
		break;
	case 520:
		ui.lineEdit2->setText("�������");
		break;
	case 522:
		if (pm->mouseData == 7864320)
		{
			ui.lineEdit2->setText("�����Ϲ�");
		}
		if (pm->mouseData == -7864320)
		{
			ui.lineEdit2->setText("�����¹�");
		}
		break;
	case 523:
		if (pm->mouseData == 131072)
		{
			ui.lineEdit2->setText("�����ϲ��");
		}
		if (pm->mouseData == 65536)
		{
			ui.lineEdit2->setText("�����²��");
		}
		break;
	case 524:
		ui.lineEdit2->setText("������");
		break;
	default:
		ui.lineEdit2->setText("����������");
		break;
	}
	return true;
}

bool MyHook::callbackKeyboard(MSG *msg)
{
	PKBDLLHOOKSTRUCT pk = (PKBDLLHOOKSTRUCT)msg->lParam; 

	//if (msg->wParam == WM_KEYDOWN && pk->vkCode == VK_HOME)
	//{
	//	QMessageBox::information(NULL, "������Ϣ", "����Home��");
	//}
	//if (msg->wParam == WM_KEYUP && pk->vkCode == VK_END)
	//{
	//	QMessageBox::information(NULL, "������Ϣ", "����End��");

	if (msg->wParam == WM_KEYUP) ui.lineEdit3->setText(QString::number(pk->vkCode));

	return true;
}