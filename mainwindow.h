#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userdata.h"
#include "pwdialog.h"
#include "eggecrypt.h"
#include "cryptodialog.h"
#include "connectdialog.h"
#include "fortuneserver.h"
#include "fortunethread.h"

class ConnectDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

 public:
    PwDialog *      m_pwdlg = NULL;
    CryptoDialog *  m_cryptodlg = NULL;
    EggeCrypt *     m_eggecrypt = NULL;
    ConnectDialog * m_connectdlg = NULL;
    FortuneServer * m_fortuneserver = NULL;

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

 public slots:
    void OnClickedLoginRegister();
    void OnClickedConnect();
    void OnClickedSetKeys();
    void OnClickedLogout();
    void OnShowMessage(const QString & msg);

 private:
    void setStyleSheet(QString & sheetName);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
