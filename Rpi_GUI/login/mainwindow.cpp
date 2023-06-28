
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn0_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + '0');
}


void MainWindow::on_btn1_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + '1');
}

void MainWindow::on_btn2_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + '2');
}

void MainWindow::on_btn3_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "3");
}

void MainWindow::on_btn4_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "4");
}

void MainWindow::on_btn5_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "5");
}

void MainWindow::on_btn6_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "6");
}

void MainWindow::on_btn7_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "7");
}

void MainWindow::on_btn8_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "8");
}

void MainWindow::on_btn9_clicked()
{
    ui->PW->setPlainText(ui->PW->toPlainText() + "9");
}

void MainWindow::on_btnDelete_clicked()
{
    if(ui->PW->toPlainText().length()!=0) ui->PW->setPlainText(ui->PW->toPlainText().chopped(1));
}

void MainWindow::on_btnEnter_clicked()
{
    QString x = ui->PW->toPlainText();
    ui->PW->setPlainText(ui->PW->toPlainText().chopped(ui->PW->toPlainText().length()));
    if(x == "123456"){
        ui->PW->setPlainText(ui->PW->toPlainText() + "정답입니다");
    }
    else ui->PW->setPlainText(ui->PW->toPlainText() + "틀렸습니다");
}

