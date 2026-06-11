#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "userdata.h"
#include "pwdialog.h"
#include "eggecrypt.h"
#include "cryptodialog.h"
#include "connectdialog.h"
#include "version.h"
#include "contacts.h"
#include "websocketserver.h"
#include "websocketclient.h"
#include "displayablecontacts.h"

class ConnectDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   PwDialog*       m_pwdlg = nullptr;
   CryptoDialog*   m_cryptodlg = nullptr;
   EggeCrypt*      m_eggecrypt = nullptr;
   ConnectDialog*  m_connectdlg = nullptr;
   Contacts*       m_contacts = nullptr;
   UserData*       m_userdata = nullptr;
   DisplayableContacts* m_displayablecontacts = nullptr;
   // TabsDialog*     m_tabs = nullptr;

 public:
    explicit MainWindow ( QWidget* parent = 0 );
    void showInfo ( QString infoMessage );
    void showMessage ( QString message );
    // void showContactIcon()
    ~MainWindow();

 public slots:
    void OnClickedLoginRegister();
    void OnClickedConnect();
    void OnClickedSetKeys();
    void OnClickedLogout();
    void OnShowMessage ( const QString & msg );
    void OnClickedSend();
    void OnClickedTabs();
    void OnClickedConnectionList();
    void OnClickedInfo();

 private:
   unsigned m_ContactFileSize = 7;
   // QString m_ContactFile[
    void setStyleSheet ( QString & sheetName );
    Ui::MainWindow* ui;
    QString eggemesg_version = EGGEMESG_VERSION;
    QLabel* m_statusbarlabel = nullptr;
    egge::server::WebSocketServer * m_websocketserver = nullptr;

};

#endif // MAINWINDOW_H
