#include "login_dialog.h"
#include "ui_login_dialog.h"
#include "QDebug"

login_dialog::login_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_dialog)
{
    ui->setupUi(this);

}

login_dialog::~login_dialog()
{
    delete ui;
}

void login_dialog::btn0_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + '0');
}

void login_dialog::closeEvent(QCloseEvent *e) // 창 닫기 버튼 누를 경우
{
    emit sendSensorValue(-1); // 로그인 실패하고 창 닫으면 -1 전송
    qDebug() << "login dialog close delete\n";
}

void login_dialog::btn1_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + '1');
}

void login_dialog::btn2_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + '2');
}

void login_dialog::btn3_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "3");
}

void login_dialog::btn4_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "4");
}

void login_dialog::btn5_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "5");
}

void login_dialog::btn6_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "6");
}

void login_dialog::btn7_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "7");
}

void login_dialog::btn8_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "8");
}

void login_dialog::btn9_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "9");
}

void login_dialog::btnDelete_clicked()
{
    if(ui->PW->toPlainText().length()!=0) ui->PW->setPlainText(ui->PW->toPlainText().chopped(1));
}

void login_dialog::btnEnter_clicked()
{
    QString pwd = ui->PW->toPlainText();
    ui->PW->setPlainText(ui->PW->toPlainText().chopped(ui->PW->toPlainText().length()));
    if(pwd == "123456"){
        QMessageBox msgBox;
        msgBox.setText("로그인 성공!");
        msgBox.exec();
        emit sendSensorValue(1); // 성공하면 1 전송
        qDebug() << "login dialog close ok\n";
        QWidget::close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("비밀번호가 틀렸습니다.");
        msgBox.exec();
    }
}

