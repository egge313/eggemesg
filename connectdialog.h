#pragma once

#include <QDialog>
#include "mainwindow.h"
#include <QTcpSocket>
#include <QDataStream>
#include "torprocess.h"
#include "websocketserver.h"
#include "websocketclient.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

 public:

    QMainWindow * m_mainwindow;

 public:
    explicit ConnectDialog( QWidget    * parent = 0,
                            QMainWindow * mainwindow = nullptr );
    ~ConnectDialog();
    egge::server::WebSocketServer * getServer ();
    egge::client::WebSocketClient * getClient ();

 public slots:
   void accept ();
   void reject ();
   void onPushButtonTorClientConnect();
   void onPushButtonTorClientDisconnect();
   void onPushButtonLaunchService ();

 private:
   void showhostname();
   void showhostip();
   void readFortune();
   bool isonline ();
   void tabTorControlUpdate();
   void tabTorControlGeneratePassword (QString & password);

   TorProcessThread * m_torprocess = nullptr;

 private:
     Ui::ConnectDialog * ui;
     egge::server::WebSocketServer * m_EggemesgServer = nullptr;
     egge::client::WebSocketClient * m_EggemesgClient = nullptr;

};
