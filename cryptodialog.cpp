#include <QFileDialog>

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
  ui->cryptoListWidget->addItem("(Frankly, need to list known public keys here soon!)");
  ui->cryptoListWidget->addItem("RSA 1024 bit -- not really safe");
  ui->cryptoListWidget->addItem("RSA 2048 bit -- relatively safe");
  ui->cryptoListWidget->addItem("RSA 3072 bit -- safe");
  ui->cryptoListWidget->addItem("RSA 4096 bit -- safe,"
                                " computationally expensive");  
  ui->generatePushButton->setDisabled(true);

  // Initialise own keys.
  EggeCrypt * ecrypt = new EggeCrypt(m_userdata->getUser(),
                                    m_userdata->getPassword());

  ui->generateLabel->setText(tr("Loading own keypair."));
  ecrypt->initialize();
  // debugprint(ecrypt->getPrintablePubKey().toUtf8().to);
  QString pubkey = "";
  ecrypt->getPrintablePubKey ( pubkey );
  ui->keyTextBrowser->setText ( pubkey );
  m_userdata->setOwnKeyPair ( ecrypt->getKeyPair() );

  connect(ui->cryptoListWidget, SIGNAL(itemSelectionChanged()), this,
	  SLOT(onSelectionChanged()));
  connect(ui->generatePushButton, SIGNAL(clicked()), this,
	  SLOT(onGeneratePushButtonClicked()));
  connect(ui->pushButtonSaveOwnPubKey, SIGNAL(clicked()), this,
          SLOT(onPushButtonSaveOwnPubKeyClicked()));
  connect(ui->pushButtonImport, SIGNAL(clicked()), this,
         SLOT(onPushButtonImport()));

}

void CryptoDialog::onPushButtonImport()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Import File"),
                                                    ".",
                                                    tr("JSON files (*.json)"));
    qDebug() << "Importing " << fileName << "\n";
}

void CryptoDialog::onPushButtonSaveOwnPubKeyClicked()
{
    ui->generateLabel->setText(tr("Saving own public key..."));
    if ( m_userdata->writeOwnPubKey ( "eggemesg-pubkey.json" ) )
        ui->generateLabel->setText(tr("Saved own public key in 'eggemesg-pubkey.json'."));
    else
        ui->generateLabel->setText(tr("Failed to save own public key in 'eggemesg-pubkey.json'."));
}

void CryptoDialog::onGeneratePushButtonClicked ()
{
    EggeCrypt * ecrypt = new EggeCrypt(m_userdata->getUser(),
                                      m_userdata->getPassword());

  ui->generateLabel->setText(tr("Generating RSA keys..."));
  ecrypt->generatekeys();
  ui->generateLabel->setText(tr("Generating RSA keys... SUCCESS!"));
  ecrypt->initialize();
  // debugprint(ecrypt->getPrintablePubKey().toUtf8().to);
  QString pubkey = "";
  ecrypt->pubKeyToBase64 ( pubkey );
  ui->keyTextBrowser->setText ( pubkey );
  m_userdata->setOwnKeyPair ( ecrypt->getKeyPair() );
  m_userdata->writeFile( "eggemesg.json" );
}

void CryptoDialog::onSelectionChanged()
{ 
  ui->generatePushButton->setDisabled(false);
}

CryptoDialog::~CryptoDialog()
{
    delete ui;
}
