#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pwdialog.h"
#include "connectdialog.h"
#include <QTextStream>
#include <QString>
#include "debugprint.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_statusbarlabel = new QLabel("Starting");
    ui->statusbar->addPermanentWidget(m_statusbarlabel);
    ui->statusbar->showMessage(
			   "Welcome, your holiness! ", 
			    5000);

    connect(ui->pushButtonLogin, SIGNAL(clicked()), this,
	    SLOT(OnClickedLoginRegister()));
    connect(ui->pushButtonConnect, SIGNAL(clicked()), this,
	    SLOT(OnClickedConnect()));
    ui->pushButtonSetKeys->setDisabled(true);
    connect(ui->pushButtonSetKeys, SIGNAL(clicked()), this,
	    SLOT(OnClickedSetKeys()));
    connect(ui->pushButtonLogout, SIGNAL(clicked()), this,
	    SLOT(OnClickedLogout()));


    ui->pushButtonConnect->setDisabled(true);

    // This pushbutton is a placeholder
    ui->pushButtonInvisible->hide();

    // set style sheet
    QString coffee_stylesheet ("coffee");
    setStyleSheet(coffee_stylesheet);

    // set application icon
    QIcon windowicon(":/images/icon.png");
    setWindowIcon(windowicon);
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
       info = QString("User: ") + QString(ud->m_user);
       ui->labelInformation->setText(info);
       ui->pushButtonSetKeys->setDisabled(false);
       break;
    case QDialog::Rejected: // failure
       ui->statusbar->showMessage(
				  "Password reject",
			    3000);
       // ud = m_pwdlg->getUserData();
       // Q_ASSERT(NULL != ud);
       // m_eggecrypt = new EggeCrypt(ud->m_user, ud->m_password);
       // m_eggecrypt->initialize();
       break;
    default: // error
       ui->statusbar->showMessage(
				  "Password error",
			    3000);
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
				  "Set keys:  success",
			    3000);
       ui->pushButtonConnect->setDisabled(false);
       break;
    case QDialog::Rejected: // failure 
       ui->statusbar->showMessage(
				  "Set keys:  reject",
			    3000);

       break;
    default:
       ui->statusbar->showMessage(
				  "Set keys:  FAILURE",
			    3000);


    }
}

void MainWindow::OnClickedLogout()
{
  ui->statusbar->showMessage( "User logging out",
			      3000);

  close();
}

void MainWindow::OnShowMessage(const QString & msg)
{
  ui->textEditMessages->append(msg);
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
    case QDialog::Rejected:
    default:
      break;
    }
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
