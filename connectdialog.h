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

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

 public:
    QTcpSocket * m_tcpsocket = NULL;
    QDataStream  m_instream;
    QMainWindow * m_mainwindow = NULL;

 public:
    explicit ConnectDialog(QWidget    * parent = 0,
			   QMainWindow * mainwindow = NULL,
                           FortuneServer * fortuneserver = NULL);
    ~ConnectDialog();

 public slots:
   void accept ();
   void reject ();
   void onPushButtonLaunchServer ();
   void onPushButtonConnect2Server();
   void onPushButtonTorClientConnect();
   void displayError(QAbstractSocket::SocketError socketError);
   void sessionOpened();

 private:
   void showhostname();
   void showhostip();
   void readFortune();
   bool isonline (const QNetworkConfigurationManager & mgr);
   FortuneServer * m_fortuneserver = NULL;
   QNetworkSession * m_networksession = NULL;
   QString currentFortune = "";

 private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
