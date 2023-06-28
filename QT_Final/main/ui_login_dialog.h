/********************************************************************************
** Form generated from reading UI file 'login_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_DIALOG_H
#define UI_LOGIN_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login_dialog
{
public:
    QWidget *centralwidget;
    QLabel *label_RightPage;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *btn6;
    QPushButton *btn3;
    QPushButton *btn5;
    QPushButton *btn7;
    QPushButton *btn9;
    QPushButton *btnEnter;
    QPushButton *btn2;
    QPushButton *btnDelete;
    QPushButton *btn1;
    QPushButton *btn8;
    QPushButton *btn4;
    QPushButton *btn0;
    QLabel *label_LeftPage;
    QTextBrowser *PW;
    QLabel *label_LogoImage;
    QLabel *label_LogoText;

    void setupUi(QDialog *login_dialog)
    {
        if (login_dialog->objectName().isEmpty())
            login_dialog->setObjectName(QString::fromUtf8("login_dialog"));
        login_dialog->resize(800, 480);
        centralwidget = new QWidget(login_dialog);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setGeometry(QRect(0, 0, 800, 480));
        label_RightPage = new QLabel(centralwidget);
        label_RightPage->setObjectName(QString::fromUtf8("label_RightPage"));
        label_RightPage->setGeometry(QRect(331, 0, 469, 480));
        label_RightPage->setStyleSheet(QString::fromUtf8("background-color: rgb(45, 51, 51);"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(350, 130, 445, 283));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btn6 = new QPushButton(gridLayoutWidget);
        btn6->setObjectName(QString::fromUtf8("btn6"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn6->sizePolicy().hasHeightForWidth());
        btn6->setSizePolicy(sizePolicy);
        btn6->setMinimumSize(QSize(120, 65));
        btn6->setMaximumSize(QSize(130, 65));
        QFont font;
        font.setFamily(QString::fromUtf8("\355\234\264\353\250\274\353\252\250\354\235\214T"));
        font.setPointSize(12);
        btn6->setFont(font);
        btn6->setAutoFillBackground(false);
        btn6->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btn6->setCheckable(false);
        btn6->setAutoRepeat(false);
        btn6->setAutoExclusive(false);
        btn6->setAutoDefault(true);
        btn6->setFlat(false);

        gridLayout->addWidget(btn6, 1, 2, 1, 1);

        btn3 = new QPushButton(gridLayoutWidget);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        sizePolicy.setHeightForWidth(btn3->sizePolicy().hasHeightForWidth());
        btn3->setSizePolicy(sizePolicy);
        btn3->setMinimumSize(QSize(120, 65));
        btn3->setMaximumSize(QSize(130, 65));
        btn3->setFont(font);
        btn3->setAutoFillBackground(false);
        btn3->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btn3->setCheckable(false);
        btn3->setAutoRepeat(false);
        btn3->setAutoExclusive(false);
        btn3->setAutoDefault(true);
        btn3->setFlat(false);

        gridLayout->addWidget(btn3, 0, 2, 1, 1);

        btn5 = new QPushButton(gridLayoutWidget);
        btn5->setObjectName(QString::fromUtf8("btn5"));
        sizePolicy.setHeightForWidth(btn5->sizePolicy().hasHeightForWidth());
        btn5->setSizePolicy(sizePolicy);
        btn5->setMinimumSize(QSize(120, 65));
        btn5->setMaximumSize(QSize(130, 65));
        btn5->setFont(font);
        btn5->setAutoFillBackground(false);
        btn5->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btn5->setCheckable(false);
        btn5->setAutoRepeat(false);
        btn5->setAutoExclusive(false);
        btn5->setAutoDefault(true);
        btn5->setFlat(false);

        gridLayout->addWidget(btn5, 1, 1, 1, 1);

        btn7 = new QPushButton(gridLayoutWidget);
        btn7->setObjectName(QString::fromUtf8("btn7"));
        btn7->setEnabled(true);
        sizePolicy.setHeightForWidth(btn7->sizePolicy().hasHeightForWidth());
        btn7->setSizePolicy(sizePolicy);
        btn7->setMinimumSize(QSize(120, 65));
        btn7->setMaximumSize(QSize(130, 65));
        btn7->setFont(font);
        btn7->setAcceptDrops(false);
        btn7->setAutoFillBackground(false);
        btn7->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btn7->setCheckable(false);
        btn7->setAutoRepeat(false);
        btn7->setAutoExclusive(false);
        btn7->setAutoDefault(true);
        btn7->setFlat(false);

        gridLayout->addWidget(btn7, 2, 0, 1, 1);

        btn9 = new QPushButton(gridLayoutWidget);
        btn9->setObjectName(QString::fromUtf8("btn9"));
        sizePolicy.setHeightForWidth(btn9->sizePolicy().hasHeightForWidth());
        btn9->setSizePolicy(sizePolicy);
        btn9->setMinimumSize(QSize(120, 65));
        btn9->setMaximumSize(QSize(130, 65));
        btn9->setFont(font);
        btn9->setAutoFillBackground(false);
        btn9->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btn9->setCheckable(false);
        btn9->setAutoRepeat(false);
        btn9->setAutoExclusive(false);
        btn9->setAutoDefault(true);
        btn9->setFlat(false);

        gridLayout->addWidget(btn9, 2, 2, 1, 1);

        btnEnter = new QPushButton(gridLayoutWidget);
        btnEnter->setObjectName(QString::fromUtf8("btnEnter"));
        sizePolicy.setHeightForWidth(btnEnter->sizePolicy().hasHeightForWidth());
        btnEnter->setSizePolicy(sizePolicy);
        btnEnter->setMinimumSize(QSize(120, 65));
        btnEnter->setMaximumSize(QSize(130, 65));
        btnEnter->setFont(font);
        btnEnter->setAutoFillBackground(false);
        btnEnter->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btnEnter->setCheckable(false);
        btnEnter->setAutoRepeat(false);
        btnEnter->setAutoExclusive(false);
        btnEnter->setAutoDefault(true);
        btnEnter->setFlat(false);

        gridLayout->addWidget(btnEnter, 3, 2, 1, 1);

        btn2 = new QPushButton(gridLayoutWidget);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        sizePolicy.setHeightForWidth(btn2->sizePolicy().hasHeightForWidth());
        btn2->setSizePolicy(sizePolicy);
        btn2->setMinimumSize(QSize(120, 65));
        btn2->setMaximumSize(QSize(130, 65));
        btn2->setFont(font);
        btn2->setAutoFillBackground(false);
        btn2->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btn2->setCheckable(false);
        btn2->setAutoRepeat(false);
        btn2->setAutoExclusive(false);
        btn2->setAutoDefault(true);
        btn2->setFlat(false);

        gridLayout->addWidget(btn2, 0, 1, 1, 1);

        btnDelete = new QPushButton(gridLayoutWidget);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));
        sizePolicy.setHeightForWidth(btnDelete->sizePolicy().hasHeightForWidth());
        btnDelete->setSizePolicy(sizePolicy);
        btnDelete->setMinimumSize(QSize(120, 65));
        btnDelete->setMaximumSize(QSize(130, 65));
        btnDelete->setFont(font);
        btnDelete->setAutoFillBackground(false);
        btnDelete->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btnDelete->setCheckable(false);
        btnDelete->setAutoRepeat(false);
        btnDelete->setAutoExclusive(false);
        btnDelete->setAutoDefault(true);
        btnDelete->setFlat(false);

        gridLayout->addWidget(btnDelete, 3, 0, 1, 1);

        btn1 = new QPushButton(gridLayoutWidget);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        sizePolicy.setHeightForWidth(btn1->sizePolicy().hasHeightForWidth());
        btn1->setSizePolicy(sizePolicy);
        btn1->setMinimumSize(QSize(120, 65));
        btn1->setMaximumSize(QSize(130, 65));
        btn1->setFont(font);
        btn1->setAutoFillBackground(false);
        btn1->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btn1->setCheckable(false);
        btn1->setAutoRepeat(false);
        btn1->setAutoExclusive(false);
        btn1->setAutoDefault(true);
        btn1->setFlat(false);

        gridLayout->addWidget(btn1, 0, 0, 1, 1);

        btn8 = new QPushButton(gridLayoutWidget);
        btn8->setObjectName(QString::fromUtf8("btn8"));
        sizePolicy.setHeightForWidth(btn8->sizePolicy().hasHeightForWidth());
        btn8->setSizePolicy(sizePolicy);
        btn8->setMinimumSize(QSize(120, 65));
        btn8->setMaximumSize(QSize(130, 65));
        btn8->setFont(font);
        btn8->setAutoFillBackground(false);
        btn8->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btn8->setCheckable(false);
        btn8->setAutoRepeat(false);
        btn8->setAutoExclusive(false);
        btn8->setAutoDefault(true);
        btn8->setFlat(false);

        gridLayout->addWidget(btn8, 2, 1, 1, 1);

        btn4 = new QPushButton(gridLayoutWidget);
        btn4->setObjectName(QString::fromUtf8("btn4"));
        sizePolicy.setHeightForWidth(btn4->sizePolicy().hasHeightForWidth());
        btn4->setSizePolicy(sizePolicy);
        btn4->setMinimumSize(QSize(120, 65));
        btn4->setMaximumSize(QSize(130, 65));
        btn4->setFont(font);
        btn4->setAutoFillBackground(false);
        btn4->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btn4->setCheckable(false);
        btn4->setAutoRepeat(false);
        btn4->setAutoExclusive(false);
        btn4->setAutoDefault(true);
        btn4->setFlat(false);

        gridLayout->addWidget(btn4, 1, 0, 1, 1);

        btn0 = new QPushButton(gridLayoutWidget);
        btn0->setObjectName(QString::fromUtf8("btn0"));
        sizePolicy.setHeightForWidth(btn0->sizePolicy().hasHeightForWidth());
        btn0->setSizePolicy(sizePolicy);
        btn0->setMinimumSize(QSize(120, 65));
        btn0->setMaximumSize(QSize(130, 65));
        btn0->setFont(font);
        btn0->setAutoFillBackground(false);
        btn0->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        btn0->setCheckable(false);
        btn0->setAutoRepeat(false);
        btn0->setAutoExclusive(false);
        btn0->setAutoDefault(true);
        btn0->setFlat(false);

        gridLayout->addWidget(btn0, 3, 1, 1, 1);

        label_LeftPage = new QLabel(centralwidget);
        label_LeftPage->setObjectName(QString::fromUtf8("label_LeftPage"));
        label_LeftPage->setGeometry(QRect(0, 0, 331, 480));
        label_LeftPage->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 246, 242);"));
        PW = new QTextBrowser(centralwidget);
        PW->setObjectName(QString::fromUtf8("PW"));
        PW->setGeometry(QRect(450, 30, 241, 81));
        PW->setStyleSheet(QString::fromUtf8("font: bold 36px black;"));
        label_LogoImage = new QLabel(centralwidget);
        label_LogoImage->setObjectName(QString::fromUtf8("label_LogoImage"));
        label_LogoImage->setGeometry(QRect(100, 90, 135, 211));
        label_LogoImage->setAutoFillBackground(false);
        label_LogoImage->setStyleSheet(QString::fromUtf8("image: url(:/images/can logo.png);"));
        label_LogoText = new QLabel(centralwidget);
        label_LogoText->setObjectName(QString::fromUtf8("label_LogoText"));
        label_LogoText->setGeometry(QRect(80, 300, 180, 30));
        label_LogoText->setStyleSheet(QString::fromUtf8("image: url(:/images/logo icanfarm.png);"));

        retranslateUi(login_dialog);
        QObject::connect(btn1, SIGNAL(clicked()), login_dialog, SLOT(btn1_clicked()));
        QObject::connect(btn0, SIGNAL(clicked()), login_dialog, SLOT(btn0_clicked()));
        QObject::connect(btn3, SIGNAL(clicked()), login_dialog, SLOT(btn3_clicked()));
        QObject::connect(btn2, SIGNAL(clicked()), login_dialog, SLOT(btn2_clicked()));
        QObject::connect(btn4, SIGNAL(clicked()), login_dialog, SLOT(btn4_clicked()));
        QObject::connect(btn5, SIGNAL(clicked()), login_dialog, SLOT(btn5_clicked()));
        QObject::connect(btn6, SIGNAL(clicked()), login_dialog, SLOT(btn6_clicked()));
        QObject::connect(btn7, SIGNAL(clicked()), login_dialog, SLOT(btn7_clicked()));
        QObject::connect(btn8, SIGNAL(clicked()), login_dialog, SLOT(btn8_clicked()));
        QObject::connect(btn9, SIGNAL(clicked()), login_dialog, SLOT(btn9_clicked()));
        QObject::connect(btnDelete, SIGNAL(clicked()), login_dialog, SLOT(btnDelete_clicked()));
        QObject::connect(btnEnter, SIGNAL(clicked()), login_dialog, SLOT(btnEnter_clicked()));

        btn6->setDefault(false);
        btn3->setDefault(false);
        btn5->setDefault(false);
        btn7->setDefault(false);
        btn9->setDefault(false);
        btnEnter->setDefault(false);
        btn2->setDefault(false);
        btnDelete->setDefault(false);
        btn1->setDefault(false);
        btn8->setDefault(false);
        btn4->setDefault(false);
        btn0->setDefault(false);


        QMetaObject::connectSlotsByName(login_dialog);
    } // setupUi

    void retranslateUi(QDialog *login_dialog)
    {
        login_dialog->setWindowTitle(QCoreApplication::translate("login_dialog", "Dialog", nullptr));
        label_RightPage->setText(QString());
        btn6->setText(QCoreApplication::translate("login_dialog", "6", nullptr));
        btn3->setText(QCoreApplication::translate("login_dialog", "3", nullptr));
        btn5->setText(QCoreApplication::translate("login_dialog", "5", nullptr));
        btn7->setText(QCoreApplication::translate("login_dialog", "7", nullptr));
        btn9->setText(QCoreApplication::translate("login_dialog", "9", nullptr));
        btnEnter->setText(QCoreApplication::translate("login_dialog", "Enter", nullptr));
        btn2->setText(QCoreApplication::translate("login_dialog", "2", nullptr));
        btnDelete->setText(QCoreApplication::translate("login_dialog", "Delete", nullptr));
        btn1->setText(QCoreApplication::translate("login_dialog", "1", nullptr));
        btn8->setText(QCoreApplication::translate("login_dialog", "8", nullptr));
        btn4->setText(QCoreApplication::translate("login_dialog", "4", nullptr));
        btn0->setText(QCoreApplication::translate("login_dialog", "0", nullptr));
        label_LeftPage->setText(QString());
        PW->setHtml(QCoreApplication::translate("login_dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'black'; font-size:36px; font-weight:700; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'\353\247\221\354\235\200 \352\263\240\353\224\225'; font-size:28pt; font-weight:400;\"><br /></p></body></html>", nullptr));
        label_LogoImage->setText(QString());
        label_LogoText->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class login_dialog: public Ui_login_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_DIALOG_H
