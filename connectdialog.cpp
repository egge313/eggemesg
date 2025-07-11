#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QHostInfo>
#include <QNetworkInterface>
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
                             QMainWindow *mainwindow) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);

    // The form editor refuses to get rid of old tabs, so the lazy programmer has to do it programmatically.
    delete ui->tabClient;
    delete ui->tabServer;

    m_mainwindow = mainwindow;

    connect(ui->pushButtonTorClientConnect, SIGNAL(clicked()),
            this, SLOT(onPushButtonTorClientConnect()));

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    // getownipaddress (QString & ownipaddr);
    showhostname ();
    showhostip ();

    // Tor Control stuff:
    ui->comboBoxAvailableServices->addItem("8888");
    ui->comboBoxAvailableServices->addItem("9999");
    connect(ui->pushButtonLaunchService, SIGNAL(clicked()),
            this, SLOT(onPushButtonLaunchService()));
    tabTorControlUpdate();

    // Tor Client stuff:
    connect(ui->pushButtonTorClientConnect, SIGNAL(clicked()),
            this, SLOT(onPushButtonTorClientConnect()));
    connect(ui->pushButtonTorClientDisconnect, SIGNAL(clicked()),
            this, SLOT(onPushButtonTorClientDisconnect()));
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
  // ui->listWidgetHostInfo->addItem(hostinfo);
}

void ConnectDialog::tabTorControlUpdate()
{
    return;
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
        {} //  ui->listWidgetHostInfo->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
        {}// ui->listWidgetHostInfo->addItem(ipAddressesList.at(i).toString());
    }
}

egge::server::WebSocketServer * ConnectDialog::getServer()
{
    return m_EggemesgServer;
}

/*
egge::client::WebSocketClient * ConnectDialog::getClient();
{
    return m_EggemesgClient;
}
*/

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
        // egge: does not work: m_mainwindow->showInfo ( "Eggemesg listening port " + portnumber + ".");
    }
    else
    {
        ui->listWidgetTorControlHistory->addItem ( "Eggemesg started, not yet listening." );
    }
}

// Connect to an Eggemesg service (i.e. a Tor onion service).
void ConnectDialog::onPushButtonTorClientConnect()
{
    QString eggemesgService = ui->comboBoxTorClientServer->currentText();

    if ( eggemesgService == "" )
    {
        QMessageBox::warning(this,
                             "Eggemesg service required",
                             "You need to select or fill in a service name!"
                             );
        return;
    }

    QString portnumber = ui->comboBoxTorClientServer->currentText();

    if ( portnumber == "" )
    {
        QMessageBox::warning(this,
                             "Port number required",
                             "You need to fill in a port!"
                             );
        return;
    }


    // Try to open an eggemesg onion (Tor) service.
    QString msg = "Initial connection attempt.";
    m_EggemesgClient = new egge::client::WebSocketClient (QUrl("ws://g6katdgrmawavzqzrhgf5ysct6y6l5424zy27b3ncjqehdz664jop4yd.onion:8888"), msg );

    ui->listWidgetTorControlHistory->addItem ( "Eggemesg attempting connection to  " + portnumber + ".");

}

void ConnectDialog::onPushButtonTorClientDisconnect()
{
    ui->listWidgetTorControlHistory->addItem ( "DISCONNECT not yet implemented." );
    return;
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


ConnectDialog::~ConnectDialog()
{
    delete ui;
}
