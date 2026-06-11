#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pwdialog.h"
#include "connectdialog.h"
#include <QTextStream>
#include <QString>
#include "debugprint.h"
#include "contacts.h"
#include <QFile>
#include <QThread>
#include "tabdialog.h"
#include "connectionlistdialog.h"
#include "version.h"
#include "overlaytext.h"
#include <QMovie>
#include "displayablecontacts.h"
#include <QMessageBox>
#include "credits.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_statusbarlabel = new QLabel("Starting");
    m_contacts = new Contacts;

    ui->statusbar->addPermanentWidget(m_statusbarlabel);
    ui->statusbar->showMessage(
			   "Welcome, your holiness! ",
                7000);

    connect(ui->pushButtonLogin, SIGNAL(clicked()), this,
	    SLOT(OnClickedLoginRegister()));
    connect(ui->pushButtonConnect, SIGNAL(clicked()), this,
	    SLOT(OnClickedConnect()));
    ui->pushButtonSetKeys->setDisabled(true);
    connect(ui->pushButtonSetKeys, SIGNAL(clicked()), this,
	    SLOT(OnClickedSetKeys()));
    connect(ui->pushButtonLogout, SIGNAL(clicked()), this,
	    SLOT(OnClickedLogout()));
    connect(ui->pushButtonSend, SIGNAL(clicked()), this,
            SLOT(OnClickedSend()));
    connect(ui->pushButtonTabs, SIGNAL(clicked()), this,
            SLOT(OnClickedTabs()));
    connect(ui->pushButtonConnectionList, SIGNAL(clicked()), this,
            SLOT(OnClickedConnectionList()));
    connect(ui->pushButtonInfo, SIGNAL(clicked()), this,
            SLOT(OnClickedInfo()));


    ui->pushButtonConnect->setDisabled(true);

    // This pushbutton is a placeholder.
    ui->pushButtonInvisible->hide();

    // This pushbutton is for testing.
    ui->pushButtonTabs->hide();

    // set style sheet
    QString coffee_stylesheet ("coffee");
    setStyleSheet(coffee_stylesheet);

    // set application icon
    QIcon windowicon(":/images/icon.png");
    setWindowIcon(windowicon);

    // Set info button icon.
    /* QIcon* infobuttonicon = new QIcon();
    QPixmap pix (":/images/icons-info-40.png"
    infobuttonicon->addPixmap ( QPixmap ( ));
    ui->pushButtonInfo->setIcon ( *infobuttonicon );
     */

    /* QToolButton *b = new QToolButton(this);
    QIcon *ico = new QIcon();
    ico->addPixmap(QPixmap("on.jpg"),QIcon::Normal,QIcon::On);
    ico->addPixmap(QPixmap("off.jpg"),QIcon::Normal,QIcon::Off);
    b->setIcon(*ico);
    b->setCheckable(true); */

    // Contacts and their names.
    m_displayablecontacts = new DisplayableContacts();
    m_displayablecontacts->addContact ( ":/images/icons8-administrator-male-100.png", "Egge" );
    m_displayablecontacts->addContact ( ":/images/icons8-avatar-100.png", "Mogge" );
    m_displayablecontacts->addContact ( ":/images/icons8-businesswoman-100.png", "Imelda" );
    m_displayablecontacts->addContact ( ":/images/icons8-long-brunette-hair-lady-100.png", "Irmeli" );
    m_displayablecontacts->addContact ( ":/images/icons8-manager-100.png", "Tippe" );
    m_displayablecontacts->addContact ( ":/images/icons8-user-female-100.png", "Justiina" );    

    // Try and display a connection icon. Icon 1.
    {
        ui->labelIcon1->setAlignment( Qt::AlignCenter );
        QPixmap pix;
        DisplayableContacts::MyContact contact;

        if ( !m_displayablecontacts->find ( "Egge", contact ))
        {
             ui->statusbar->showMessage( "Can't find contact", 3000);
        }
        else if( pix.load ( contact.fileName ))
        {
            // overlayTextOnBitmap ( pix, "Kalervo" );

            // Scale pixmap to fit in label'size and keep ratio of pixmap.
            pix = pix.scaled( ui->labelIcon1->size(), Qt::KeepAspectRatio );
            ui->labelIcon1->setPixmap ( pix );
            ui->labelIconTxt1->setText ( contact.name );
        }
        else
        {
           ui->statusbar->showMessage( "Can't load pixmap", 3000);
        }
    }

    // Try and display a connection icon. Icon 2.
    {
        ui->labelIcon2->setAlignment( Qt::AlignCenter );
        QPixmap pix;
        DisplayableContacts::MyContact contact;

        if ( !m_displayablecontacts->find ( "Mogge", contact ))
        {
            ui->statusbar->showMessage( "Can't find contact", 3000);
        }
        else if( pix.load ( contact.fileName ))
        {
            // overlayTextOnBitmap ( pix, "Kalervo" );

            // Scale pixmap to fit in label'size and keep ratio of pixmap.
            pix = pix.scaled( ui->labelIcon2->size(), Qt::KeepAspectRatio );
            ui->labelIcon2->setPixmap ( pix );
            ui->labelIconTxt2->setText ( contact.name );
        }
        else
        {
            ui->statusbar->showMessage( "Can't load pixmap", 3000);
        }
    }

    // Try and display a connection icon. Icon 3.
    {
        ui->labelIcon3->setAlignment( Qt::AlignCenter );
        QPixmap pix;
        DisplayableContacts::MyContact contact;

        if ( !m_displayablecontacts->find ( "Imelda", contact ))
        {
            ui->statusbar->showMessage( "Can't find contact", 3000);
        }
        else if( pix.load ( contact.fileName ))
        {
            // overlayTextOnBitmap ( pix, "Kalervo" );

            // Scale pixmap to fit in label'size and keep ratio of pixmap.
            pix = pix.scaled( ui->labelIcon3->size(), Qt::KeepAspectRatio );
            ui->labelIcon3->setPixmap ( pix );
            ui->labelIconTxt3->setText ( contact.name );
        }
        else
        {
            ui->statusbar->showMessage( "Can't load pixmap", 3000);
        }
    }

    // Try and display a connection icon. Icon 4.
    {
        ui->labelIcon4->setAlignment( Qt::AlignCenter );
        QPixmap pix;
        DisplayableContacts::MyContact contact;

        if ( !m_displayablecontacts->find ( "Irmeli", contact ))
        {
            ui->statusbar->showMessage( "Can't find contact", 3000);
        }
        else if( pix.load ( contact.fileName ))
        {
            // overlayTextOnBitmap ( pix, "Kalervo" );

            // Scale pixmap to fit in label'size and keep ratio of pixmap.
            pix = pix.scaled( ui->labelIcon4->size(), Qt::KeepAspectRatio );
            ui->labelIcon4->setPixmap ( pix );
            ui->labelIconTxt4->setText ( contact.name );
        }
        else
        {
            ui->statusbar->showMessage( "Can't load pixmap", 3000);
        }
    }

    // Try and display a connection icon. Icon 5.
    {
        ui->labelIcon5->setAlignment( Qt::AlignCenter );
        QPixmap pix;
        DisplayableContacts::MyContact contact;

        if ( !m_displayablecontacts->find ( "Tippe", contact ))
        {
            ui->statusbar->showMessage( "Can't find contact", 3000);
        }
        else if( pix.load ( contact.fileName ))
        {
            // overlayTextOnBitmap ( pix, "Kalervo" );

            // Scale pixmap to fit in label'size and keep ratio of pixmap.
            pix = pix.scaled( ui->labelIcon5->size(), Qt::KeepAspectRatio );
            ui->labelIcon5->setPixmap ( pix );
            ui->labelIconTxt5->setText ( contact.name );
        }
        else
        {
            ui->statusbar->showMessage( "Can't load pixmap", 3000);
        }
    }

    // Try and display a connection icon. Icon 6.
    {
        ui->labelIcon6->setAlignment( Qt::AlignCenter );
        QPixmap pix;
        DisplayableContacts::MyContact contact;

        if ( !m_displayablecontacts->find ( "Justiina", contact ))
        {
            ui->statusbar->showMessage( "Can't find contact", 3000);
        }
        else if( pix.load ( contact.fileName ))
        {
            // overlayTextOnBitmap ( pix, "Kalervo" );

            // Scale pixmap to fit in label'size and keep ratio of pixmap.
            pix = pix.scaled( ui->labelIcon6->size(), Qt::KeepAspectRatio );
            ui->labelIcon6->setPixmap ( pix );
            ui->labelIconTxt6->setText ( contact.name );
        }
        else
        {
            ui->statusbar->showMessage( "Can't load pixmap", 3000);
        }
    }


    // For starters, show what we are running + version.
    QString versionInfo = "Egge's Messenger (eggemesg) Version ";
    versionInfo.append ( EGGEMESG_VERSION );
    ui->labelInformation->setText ( versionInfo );
}

void MainWindow::OnClickedSend()
{
    QString myMessage = ui->textEditMessages->toPlainText();
    if ( myMessage == "" )
    {
        ui->statusbar->showMessage ( "No message to send", 3000 );
        return;
    }
    if ( m_contacts == nullptr )
    {
        ui->statusbar->showMessage ( "No known contacts", 3000 );
        return;
    }

    QString pubkey;
    QString dummyAddress;

    if ( !m_contacts->findByName ( "qwe", pubkey, dummyAddress ) )
    {
        ui->statusbar->showMessage ( "No known contacts", 3000 );
        return;
    }


    egge::client::WebSocketClient * wsClient = m_connectdlg->getClient();
    if ( nullptr == wsClient )
    {
        ui->statusbar->showMessage ( "No active connection", 3000 );
        return;
    }
    else
    {
        ui->statusbar->showMessage ( "Connection created", 3000 );
    }

    if ( ! wsClient->send_text_message ( myMessage ))
    {
        ui->statusbar->showMessage ( "Failed to send a message", 3000 );
        return;
    }
    else
    {
        ui->statusbar->showMessage ( "Message sent", 3000 );
    }

    gcry_sexp_t myCipher;
    // Encrypt message using an RSA public key.
    /* m_eggecrypt->encode (myMessage.data(),
                          pubk, // egge: we need to obtain pubk somehow
                        gcry_sexp_t & myCipher);
    */
    // This call will fail until myCipher is good. (See comment above.)
    if ( ! wsClient->send_text_message ( (char *)myCipher))
    {
        ui->statusbar->showMessage ( "Failed to send an encoded message", 3000 );
        return;
    }


    QString user = m_pwdlg->getUserData()->getUser();
    ui->textEditMyMessages->append ( user + ": " + myMessage );
}

void MainWindow::OnClickedInfo()
{
    QMessageBox msgBox(this);
    QString msg ( "You are running Egge's Messenger (eggemesg), version " );
    msg.append( EGGEMESG_VERSION ).append( ".\n" );
    msg.append( "Programmer: Esa Kettunen aka Egge\n" );
    msg.append( "Source code: https://github.com/egge313/eggemesg\n" );
    msg.append( "Credits: " ).append ( EGGEMESG_CREDITS1 );
    msgBox.setText( msg );
    msgBox.exec();
}

void MainWindow::OnClickedTabs()
{
    QString fileName = ".";
    TabDialog tabdialog(fileName);
    switch ( tabdialog.exec() )
    {
    case QDialog::Accepted:
        ui->statusbar->showMessage ( "Tabs dialog accepted", 3000 );
        return;
    case QDialog::Rejected:
        ui->statusbar->showMessage ( "Tabs dialog cancelled", 3000 );
        return;
    default:
        ui->statusbar->showMessage ( "Tabs dialog weirdness prevails", 3000 );
        return;
    }
}

void MainWindow::OnClickedConnectionList()
{
    ConnectionListDialog connlistdialog;
    switch ( connlistdialog.exec() )
    {
    case QDialog::Accepted:
        ui->statusbar->showMessage ( "Connection list dialog accepted", 3000 );
        return;
    case QDialog::Rejected:
        ui->statusbar->showMessage ( "Connection list dialog cancelled", 3000 );
        return;
    default:
        ui->statusbar
	   ->showMessage ( "Connection list dialog weirdness prevails", 3000 );
        return;
    }
}


void MainWindow::OnClickedLoginRegister()
{
  ui->statusbar->showMessage(
			     "Clicked login/register",
			    3000);
  if (nullptr == m_pwdlg)
    {
      m_pwdlg = new PwDialog(this);
      // connect (m_pwdlg, SIGNAL(setUserSuccesfully()), this,
      //   SLOT(OnSetUserSuccessfully()));
    }
  int retval = m_pwdlg->exec();
  {
    QString str("Password dialog returns: ");
    QString rv;

    rv.setNum(retval);
    str.append(rv);
    debugprint(str);
  }
  UserData* ud = nullptr;
  QString info = "";
  switch (retval)
    {
    case QDialog::Accepted: // success
       ui->statusbar->showMessage(
				  "Password success",
			    3000);

       ud = m_pwdlg->getUserData();
       Q_ASSERT(NULL != ud);
       info = QString("User: ") + QString(ud->getUser());
       ui->labelInformation->setText(info);
       ui->pushButtonSetKeys->setDisabled(false);
       m_statusbarlabel->setText ( "Logged in" );
       break;
    case QDialog::Rejected: // failure
       ui->statusbar->showMessage(
				  "Password reject",
			    3000);
       m_statusbarlabel->setText ( "Not logged in" );
       break;
    default: // error
       ui->statusbar->showMessage(
				  "Password error",
			    3000);
       m_statusbarlabel->setText ( "Password error" );
    }
}

void MainWindow::OnClickedSetKeys()
{
  if (nullptr == m_cryptodlg)
    {
      m_cryptodlg = new CryptoDialog(this, m_pwdlg->getUserData());
    }
  switch (m_cryptodlg->exec())
    {
     case QDialog::Accepted: // success
       ui->statusbar->showMessage(
				  "Set keys: success",
			    3000);
       ui->pushButtonConnect->setDisabled(false);
       m_userdata = new UserData ( "", "", "", true );
       if ( m_userdata->readFile ( "eggemesg.json" ))
	  {
	     debugprint ( "User data OK." );
	  }
       else
	  {
	     debugprint ( "User data not readable." );
	  }
       m_statusbarlabel->setText ( "Crypto Ready" );
       break;
    case QDialog::Rejected: // failure 
       ui->statusbar->showMessage(
				  "Set keys: reject",
			    3000);

       break;
    default: // Something unexpected happened.
       ui->statusbar->showMessage(
				  "Set keys: FAILURE",
				  3000 );


    }
}

void MainWindow::OnClickedLogout()
{
  ui->statusbar->showMessage( "User logging out",
			      3000 );

  close();
}

void MainWindow::OnShowMessage(const QString & msg)
{
  ui->textEditMyMessages->append(msg);
}

void MainWindow::OnClickedConnect()
{
  if (nullptr == m_connectdlg)
    {
      m_connectdlg = new ConnectDialog(this, this);
    }

  switch (m_connectdlg->exec())
    {
    case QDialog::Accepted:
        {
            m_statusbarlabel->setText ( "Connected" );
            egge::server::WebSocketServer * wss = m_connectdlg->getServer();

            if ( nullptr != wss )
            {
                QString mymessage("");
                if ( wss->getMessage ( mymessage, true ))
                     ui->textEditMyMessages->append ( mymessage );
                connect ( wss, &egge::server::WebSocketServer::signalTextMessage, this, &MainWindow::OnShowMessage );
            }

            egge::client::WebSocketClient * wsClient = m_connectdlg->getClient();

            if ( nullptr != wsClient )
            {

            }

            break;
        }

    case QDialog::Rejected:
        m_statusbarlabel->setText ( "Local" );
        break;
    default:
        m_statusbarlabel->setText ( "??Confused??" );
        break;
    }
}

#if 0
void MainWindow::showContactIcon()
{
    // Try and display a connection icon. Icon 1.
    {
        ui->labelIcon1->setAlignment( Qt::AlignCenter );
        QPixmap pix;

        if( pix.load ( ":/images/man2.png" ))
        {
            overlayTextOnBitmap ( pix, "Kalervo" );

            // Scale pixmap to fit in label'size and keep ratio of pixmap.
            pix = pix.scaled( ui->labelIcon1->size(), Qt::KeepAspectRatio );
            ui->labelIcon1->setPixmap(pix);
        }
        else
        {
            ui->statusbar->showMessage( "Icon not loaded", 3000);
        }
    }

}
#endif
void MainWindow::showInfo ( QString infoMessage )
{
    ui->textEditMyMessages->append ( infoMessage );
}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_pwdlg;
    delete m_cryptodlg;
    delete m_connectdlg;
}


void MainWindow::setStyleSheet(QString & sheetName)
{
  QFile file(":/qss/" + sheetName.toLower() + ".qss");
  file.open(QFile::ReadOnly);
  QString styleSheet = QString::fromLatin1(file.readAll());
  qApp->setStyleSheet(styleSheet);
}
