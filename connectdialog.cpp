#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QHostInfo>
#include <QNetworkInterface>
#include "fortuneserver.h"
#include <QMessageBox>
#include <QNetworkInformation>
#include <QSettings>
#include "curlpost.h"
#include <QTime>
#include "torprocess.h"
#include <QTimer>
#include <QDateTime>
#include <QRandomGenerator>

ConnectDialog::ConnectDialog(QWidget *parent,
			     QMainWindow * mainwindow,
			     FortuneServer * fs) :
    QDialog(parent),
    m_fortuneserver(fs),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    connect(ui->pushButtonLaunchServer, SIGNAL(clicked()),
            this, SLOT(onPushButtonLaunchServer()));
    connect(ui->pushButtonConnect2Server, SIGNAL(clicked()),
            this, SLOT(onPushButtonConnect2Server()));
    connect(ui->pushButtonTorClientConnect, SIGNAL(clicked()),
            this, SLOT(onPushButtonTorClientConnect()));

    // connect(ui->buttonBox, &QDialogButtonBox::accepted, this, SLOT(accept()))   
    // getownipaddress (QString & ownipaddr);
    showhostname ();
    showhostip ();
    m_fortuneserver = new FortuneServer;
    ui->comboBoxServerIP->addItem("localhost");
    ui->comboBoxServerIP->addItem("127.0.0.1");    
    m_instream.setDevice(m_tcpsocket);
    m_instream.setVersion(QDataStream::Qt_6_9); // Qt 6.9 is the earliest
                                                // version with 
                                                // a compatible interface

    //    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
    //! [2] //! [3]
    connect(m_tcpsocket, &QIODevice::readyRead, this,
	    &ConnectDialog::readFortune);
    //! [2] //! [4]
    /* connect(m_tcpsocket,
	    QOverload<QAbstractSocket::SocketError>::of(
						&QAbstractSocket::error),
	    //! [3]
            this, &ConnectDialog::displayError);

    QNetworkConfigurationManager manager;
    if (manager.capabilities() &
	QNetworkConfigurationManager::NetworkSessionRequired) {
      // Get saved network configuration
      QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
      settings.beginGroup(QLatin1String("QtNetwork"));
      const QString id = settings.
	value(QLatin1String("DefaultNetworkConfiguration")).toString();
      settings.endGroup();

      // If the saved network configuration is not currently
      // discovered use the system default
      QNetworkConfiguration config = manager.configurationFromIdentifier(id);
      if ((config.state() & QNetworkConfiguration::Discovered) !=
	  QNetworkConfiguration::Discovered) {
	config = manager.defaultConfiguration();
      }
*/
      // egge: work on this -- m_networksession = new QNetworkSession(config, this);
      // egge: work on this -- connect(m_networksession, &QNetworkSession::opened, this,
    // egge: work on this --   &ConnectDialog::sessionOpened);

      // getFortuneButton->setEnabled(false);
  /*    ui->labelClientInfo_2->setText(tr("Opening network session."));
      m_networksession->open();
    } */

    // Tor Control stuff:
    ui->comboBoxAvailableServices->addItem("8888");
    ui->comboBoxAvailableServices->addItem("9999");
    connect(ui->pushButtonLaunchService, SIGNAL(clicked()),
            this, SLOT(onPushButtonLaunchService()));
    tabTorControlUpdate();
}

void ConnectDialog::showhostname()
{
  QString name = QHostInfo::localHostName();
  if (!name.isEmpty())
    {
      QString domain = QHostInfo::localDomainName();
      if (!domain.isEmpty())
        {
            name = name + QChar('.') + domain;
        }
    }
  QString hostinfo = QString("Host name: ") + name;
  ui->listWidgetHostInfo->addItem(hostinfo);
}

void ConnectDialog::tabTorControlUpdate()
{
    return;
  QString controlportpasswd("");
  tabTorControlGeneratePassword (controlportpasswd);
  m_torprocess = new TorProcessThread ("/home/egge/",
				       QStringList() 
					 << "--hash-password"
					 << controlportpasswd);
  m_torprocess->start();
  ui->listWidgetTorControlHistory->addItem("Control port password is: " +
					   controlportpasswd);
  QTimer::singleShot(3000, this, SLOT(tabTorControlUpdateHandler()));

  while ( true )
    {
      if ( m_torprocess->isfinished() )
        {
            break;
        }
      if ( m_torprocess->erroroccurred() )
        {
            break;
        }
      ui->listWidgetTorControlHistory->addItem("Sleep 200 ms.");
      QThread::msleep(200);
    }

  ui->listWidgetTorControlHistory->addItem("Process exited.");

  if (m_torprocess->isfinished())
    {
        ui->listWidgetTorControlHistory->addItem(
					  "Process checks out as finished.");
    }
  else
    {
        ui->listWidgetTorControlHistory->addItem(
					"Process checks out as not finished.");      
    }

  QString stdoutmsg;
  QString stderrmsg;
  m_torprocess->readall(stdoutmsg, stderrmsg);      

  QString controlportpasswordhash = stdoutmsg;
  if (m_torprocess->isfinished())
    {
      for (int i = 0; ; ++i)
	{
	  if (controlportpasswordhash.at(i) == '\n')
	    {
	      controlportpasswordhash[i] = '\0';
	      break;
	    }
	  else if (controlportpasswordhash.at(i) == '\0')
	    {
	      break;
	    }
	}
      ui->listWidgetTorControlHistory->addItem(controlportpasswordhash);
    }
  if (m_torprocess->erroroccurred())
    {
      ui->listWidgetTorControlHistory->addItem("Error occurred:");
      ui->listWidgetTorControlHistory->addItem(stderrmsg);
    }
}

void ConnectDialog::tabTorControlUpdateHandler()
{
  if (m_torprocess != nullptr)
    {
      QString stdoutmsg;
      QString stderrmsg;

      m_torprocess->readall(stdoutmsg, stderrmsg);
      ui->listWidgetTorControlHistory->addItem(stdoutmsg);
      ui->listWidgetTorControlHistory->addItem(stderrmsg);

      if (m_torprocess->isfinished())
	{
	  ui->listWidgetTorControlHistory->addItem("Tor finished");
	}
      if (m_torprocess->erroroccurred())
	{
	  ui->listWidgetTorControlHistory->addItem(
					       "Tor process error occurred");
	  QString errmsg;
	  m_torprocess->geterrormessage(errmsg);
	  ui->listWidgetTorControlHistory->addItem(errmsg);
	}
    }
}

void ConnectDialog::tabTorControlGeneratePassword (QString & password)
{
  QString table =
    "qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM!#¤%&()=?";
  int siz = table.length();
  QString str;
  str.resize(40);
  // DateTime now = QDateTime::currentDateTime();
  // qsrand (now.toMSecsSinceEpoch());
  for (int s = 0; s < 40 ; ++s)
    {
      str[s] = table[ QRandomGenerator::global()->generate() % siz];
    }
  password = str;
}

void ConnectDialog::showhostip()
{
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
             ui->listWidgetHostInfo->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
             ui->listWidgetHostInfo->addItem(ipAddressesList.at(i).toString());
    }
}

void ConnectDialog::onPushButtonLaunchService ()
{
    QString portnumber = ui->comboBoxAvailableServices->currentText();

    if ( portnumber == "" )
    {
        QMessageBox::warning(this,
                             "Port number required",
                             "First select a port!"
                            );
        return;
    }

    // Launch an eggemesg onion (Tor) service.
    m_EggemesgServer = new egge::server::WebSocketServer ( portnumber.toInt(), this );
    if ( m_EggemesgServer->isListening() )
    {
        ui->listWidgetTorControlHistory->addItem ( "Eggemesg listening port " + portnumber + ".");
    }
    else
    {
        ui->listWidgetTorControlHistory->addItem ( "Eggemesg started, not yet listening." );
    }
}

void ConnectDialog::onPushButtonLaunchServer ()
{
  QString portnumber = ui->lineEditServerPortNumber->text();
  bool worked = false;
  quint16 portnumber16 = (quint16)portnumber.toULongLong(&worked);

  if (!worked) 
    {
	  QMessageBox::warning(this, "Illegal entry", 
			    "Socket number expected in range 49152 ... 65535. "
			       );

	  return;
    }

  //   49152–65535
  else if (portnumber16 < 49152)
    {
	  QMessageBox::warning(this, "Out of recommended range", 
			    "Socket number expected in range 49152 ... 65535. "
			       );

	  return;
    }

  if (!m_fortuneserver->listen(QHostAddress::Any, portnumber16))
    {
      if (m_fortuneserver->isListening())
	{
	  QMessageBox::critical(this, tr("Threaded Fortune Server"),
			tr("is already listening for an incoming connection."));
	  
	}
      else
	{
	  QMessageBox::critical(this, tr("Threaded Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(m_fortuneserver->errorString()));
	}
    }
  else
    {
      ui->labelServerInfo_2
->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            "Run the Fortune Client example now.")
                         .arg("127.0.0.1").arg(m_fortuneserver->serverPort()));
    }
      
}

bool ConnectDialog::isonline ()
{
        if ( QNetworkInformation::loadDefaultBackend() && QNetworkInformation::loadBackendByFeatures( QNetworkInformation::Feature::Reachability ) )
        {
            QNetworkInformation* net_info = QNetworkInformation::instance();
            if ( nullptr != net_info ) {
                if(net_info->reachability() == QNetworkInformation::Reachability::Online) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else
                return false;
        }
        else
            return false;
}

void ConnectDialog::accept ()
{
  QDialog::accept();
}

void ConnectDialog::reject ()
{
  QDialog::reject();
}

void ConnectDialog::onPushButtonTorClientConnect()
{
  QString torserverip = ui->comboBoxTorClientServer->currentText();
  Curlpost curlpost;
  QString readbuffer;
  QTime now;

  now = now.currentTime();
  QString feedback = now.toString().append(" Connecting to ")
    .append (torserverip)
    .append (" via Tor.");
  ui->listWidgetTorClientFeedback->addItem (feedback);
  try 
    {
      curlpost.send (torserverip, "1234567890zxcvb", readbuffer, true);
    } 
  catch (CurlpostException & excp)
    {
      ui->listWidgetTorClientFeedback->addItem (excp.what());

      // Check if Tor is on in the first place
      //
      try
	{
	  if (curlpost.is_Tor_on ())
	    {  
	      ui->labelTorClientInfo2 ->setText(tr("Tor is ON."));
	    }
	  else
	    {  
	      ui->labelTorClientInfo2 ->setText(tr("Tor is OFF."));
	    }
	}
      catch (CurlpostException & excp2)
	{
	  ui->listWidgetTorClientFeedback->addItem (excp2.what());
	  ui->labelTorClientInfo2 ->setText(tr("Tor is OFF."));
	}
      return;
    }
  ui->listWidgetTorClientFeedback->addItem (readbuffer);

}

void ConnectDialog::onPushButtonConnect2Server()
{
  QString serverip = ui->comboBoxServerIP->currentText();
  QString serverport = ui->comboBoxServerPortNumber->currentText();
  // getFortuneButton->setEnabled(false);
  m_tcpsocket->abort();
//! [7]
  m_tcpsocket->connectToHost(serverip,
			     serverport.toInt());

  
}

void ConnectDialog::readFortune()
{
    m_instream.startTransaction();

    /*    QString nextFortune;
    m_instream >> nextFortune;

    if (!m_instream.commitTransaction())
        return;

    if (nextFortune == currentFortune) {
        QTimer::singleShot(0, this, &Client::requestNewFortune);
        return;
    }

    currentFortune = nextFortune;
    statusLabel->setText(currentFortune);

    */

    //  getFortuneButton->setEnabled(true);
}
//! [8]

void ConnectDialog::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
      /*
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
      */
      {}
    }

    // getFortuneButton->setEnabled(true);
}

  /*
void Client::enableGetFortuneButton()
{

    getFortuneButton->setEnabled((!networkSession || networkSession->isOpen()) &&
                                 !hostCombo->currentText().isEmpty() &&
                                 !portLineEdit->text().isEmpty());


}
  */

void ConnectDialog::sessionOpened()
{
    // Save the used configuration
    /* QNetworkConfiguration config = m_networksession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = m_networksession->sessionProperty(
			  QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
    */
    /*
    statusLabel->setText(tr("This examples requires that you run the "
                            "Fortune Server example as well."));

    enableGetFortuneButton();
    */
}


ConnectDialog::~ConnectDialog()
{
    delete ui;
}
