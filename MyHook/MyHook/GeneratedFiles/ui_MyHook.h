/********************************************************************************
** Form generated from reading UI file 'MyHook.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYHOOK_H
#define UI_MYHOOK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyHookClass
{
public:
    QWidget *centralWidget;
    QPushButton *MouseHookButton;
    QPushButton *MouseUnHookButton;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit2;
    QPushButton *KeyboardHookButton;
    QPushButton *KeyboardUnHookButton;
    QLabel *label;
    QLineEdit *lineEdit3;
    QLabel *label2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyHookClass)
    {
        if (MyHookClass->objectName().isEmpty())
            MyHookClass->setObjectName(QStringLiteral("MyHookClass"));
        MyHookClass->resize(237, 192);
        centralWidget = new QWidget(MyHookClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MouseHookButton = new QPushButton(centralWidget);
        MouseHookButton->setObjectName(QStringLiteral("MouseHookButton"));
        MouseHookButton->setGeometry(QRect(10, 70, 91, 23));
        MouseUnHookButton = new QPushButton(centralWidget);
        MouseUnHookButton->setObjectName(QStringLiteral("MouseUnHookButton"));
        MouseUnHookButton->setGeometry(QRect(10, 100, 91, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 211, 20));
        lineEdit2 = new QLineEdit(centralWidget);
        lineEdit2->setObjectName(QStringLiteral("lineEdit2"));
        lineEdit2->setGeometry(QRect(10, 40, 91, 20));
        KeyboardHookButton = new QPushButton(centralWidget);
        KeyboardHookButton->setObjectName(QStringLiteral("KeyboardHookButton"));
        KeyboardHookButton->setGeometry(QRect(130, 70, 91, 23));
        KeyboardUnHookButton = new QPushButton(centralWidget);
        KeyboardUnHookButton->setObjectName(QStringLiteral("KeyboardUnHookButton"));
        KeyboardUnHookButton->setGeometry(QRect(130, 100, 91, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 40, 41, 21));
        lineEdit3 = new QLineEdit(centralWidget);
        lineEdit3->setObjectName(QStringLiteral("lineEdit3"));
        lineEdit3->setGeometry(QRect(170, 40, 51, 20));
        label2 = new QLabel(centralWidget);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setGeometry(QRect(10, 130, 211, 21));
        MyHookClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyHookClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 237, 23));
        MyHookClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyHookClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyHookClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyHookClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyHookClass->setStatusBar(statusBar);

        retranslateUi(MyHookClass);

        QMetaObject::connectSlotsByName(MyHookClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyHookClass)
    {
        MyHookClass->setWindowTitle(QApplication::translate("MyHookClass", "MyHook", 0));
        MouseHookButton->setText(QApplication::translate("MyHookClass", "\345\220\257\345\212\250\351\274\240\346\240\207Hook", 0));
        MouseUnHookButton->setText(QApplication::translate("MyHookClass", "\345\215\270\350\275\275\351\274\240\346\240\207Hook", 0));
        KeyboardHookButton->setText(QApplication::translate("MyHookClass", "\345\220\257\345\212\250\351\224\256\347\233\230Hook", 0));
        KeyboardUnHookButton->setText(QApplication::translate("MyHookClass", "\345\215\270\350\275\275\351\224\256\347\233\230Hook", 0));
        label->setText(QApplication::translate("MyHookClass", "\346\214\211\351\224\256\347\240\201", 0));
        label2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MyHookClass: public Ui_MyHookClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYHOOK_H
