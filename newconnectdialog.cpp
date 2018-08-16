#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QHostInfo>
#include <QNetworkInterface>
#include "fortuneserver.h"

ConnectDialog::ConnectDialog(QWidget *parent, FortuneServer * fs) :
    QDialog(parent),
    m_fortuneserver(fs),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    //    connect(ui->buttonBox, SIGNAL(clicked()),
    //        this, SLOT(onButtonClick));
    // connect(ui->buttonBox, &QDialogButtonBox::accepted, this, SLOT(accept()))   
    // getownipaddress (QString & ownipaddr);
    showhostname();
    showhostip();
    m_fortuneserver = new FortuneServer;
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
