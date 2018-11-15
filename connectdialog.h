#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include "fortuneserver.h"
#include "fortunethread.h"
#include "mainwindow.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QNetworkSession>
#include <QNetworkConfigurationManager>
#include "torprocess.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

 public:
    QTcpSocket * m_tcpsocket = nullptr;
    QDataStream  m_instream;
    QMainWindow * m_mainwindow = nullptr;

 public:
    explicit ConnectDialog(QWidget    * parent = 0,
			   QMainWindow * mainwindow = nullptr,
                           FortuneServer * fortuneserver = nullptr);
    ~ConnectDialog();

 public slots:
   void accept ();
   void reject ();
   void onPushButtonLaunchServer ();
   void onPushButtonConnect2Server();
   void onPushButtonTorClientConnect();
   void displayError(QAbstractSocket::SocketError socketError);
   void sessionOpened();
   void tabTorControlUpdateHandler();

 private:
   void showhostname();
   void showhostip();
   void readFortune();
   bool isonline (const QNetworkConfigurationManager & mgr);
   void tabTorControlUpdate();
   FortuneServer * m_fortuneserver = nullptr;
   QNetworkSession * m_networksession = nullptr;
   QString currentFortune = "";
   TorProcessThread * m_torprocess = nullptr;

 private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
