#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyHook.h"

class MyHook : public QMainWindow
{
	Q_OBJECT

public:
	MyHook(QWidget *parent = Q_NULLPTR);

private:
	Ui::MyHookClass ui;
private slots:
void MouseHookButton();
void MouseUnHookButton();
void KeyboardHookButton();
void KeyboardUnHookButton();
protected:
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
public:
	bool callbackMouse(MSG *msg);
	bool callbackKeyboard(MSG *msg);
};
