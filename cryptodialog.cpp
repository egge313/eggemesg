#include "cryptodialog.h"
#include "ui_cryptodialog.h"
#include "eggecrypt.h"
#include "userdata.h"
#include "debugprint.h"

CryptoDialog::CryptoDialog(QWidget * parent, UserData * userdata) :
    QDialog(parent),
    ui(new Ui::CryptoDialog),
    m_userdata(userdata)

{
  ui->setupUi(this);
  ui->cryptoListWidget->addItem("RSA 1024 bit -- not really safe");
  ui->cryptoListWidget->addItem("RSA 2048 bit -- relatively safe");
  ui->cryptoListWidget->addItem("RSA 3072 bit -- safe");
  ui->cryptoListWidget->addItem("RSA 4096 bit -- safe,"
                                " computationally expensive");  
  ui->generatePushButton->setDisabled(true);
  connect(ui->cryptoListWidget, SIGNAL(itemSelectionChanged()), this,
	  SLOT(onSelectionChanged()));
  connect(ui->generatePushButton, SIGNAL(clicked()), this,
	  SLOT(onGeneratePushButtonClicked()));

}

void CryptoDialog::onGeneratePushButtonClicked ()
{
  EggeCrypt * ecrypt = new EggeCrypt(m_userdata->m_user,
				     m_userdata->m_password);

  ui->generateLabel->setText(tr("Generating RSA keys..."));
  ecrypt->generatekeys();
  ui->generateLabel->setText(tr("Generating RSA keys... SUCCESS!"));
  ecrypt->initialize();
  debugprint((char *)ecrypt->getprintablepubkey());
  ui->keyTextBrowser->setText(tr(ecrypt->getprintablepubkey()));
}

void CryptoDialog::onSelectionChanged()
{ 
  ui->generatePushButton->setDisabled(false);
}

CryptoDialog::~CryptoDialog()
{
    delete ui;
}
