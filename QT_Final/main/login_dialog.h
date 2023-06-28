#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
#include <QMessageBox>

extern std::string PWD;

namespace Ui
{
    class login_dialog;
}

class login_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit login_dialog(QWidget *parent = nullptr);
    ~login_dialog();

private:
    Ui::login_dialog *ui;

signals:
    void sendLogInResult(int flag); // 로그인 성공 혹은 실패에 따라 다른 값 전송

private slots:
    void closeEvent(QCloseEvent *e);
    void btn0_clicked();
    void btn1_clicked();
    void btn2_clicked();
    void btn3_clicked();
    void btn4_clicked();
    void btn5_clicked();
    void btn6_clicked();
    void btn7_clicked();
    void btn8_clicked();
    void btn9_clicked();
    void btnDelete_clicked();
    void btnEnter_clicked();
};

#endif // LOGIN_DIALOG_H
