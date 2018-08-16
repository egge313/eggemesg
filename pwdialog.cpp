#include "pwdialog.h"
#include "ui_pwdialog.h"
#include "userdata.h"
#include <QMessageBox>

PwDialog::PwDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PwDialog)
{
    ui->setupUi(this);
    //    connect(ui->buttonBox, SIGNAL(clicked()),
    //        this, SLOT(onButtonClick));
    // connect(ui->buttonBox, &QDialogButtonBox::accepted, this, SLOT(accept()));    
    //    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, SLOT(accept));
    // connect(ui->buttonBox, &QDialogButtonBox::rejected, this, SLOT(reject));
}

void PwDialog::accept ()
{
  switch (ui->tabWidget->currentIndex())
    {
    case 0:
      if (ui->lineEditUser1->text().length() > 0 &&
	  ui->lineEditPw1->text().length() > 0)
	{
	  m_userdata = new UserData(ui->lineEditUser1->text(),
				  ui->lineEditPw1->text(),
				  false);
	  QDialog::accept();
	}
      else
	{
	  QMessageBox::warning(this, "Illegal entry", 
			       "Empty user name or password"
			       );
	  return;
	}
      break;

    case 1:
      if (ui->lineEditUser2->text().length() > 0 &&
	  ui->lineEditPw2->text().length() > 0)
	{
	  if (ui->lineEditPw2->text() !=
	      ui->lineEditPwRepeat2->text())
	    {
	      QMessageBox::warning(this, "Password not repeated",
				   "Need to repeat the same password!");
	      return;
	    }
	  m_userdata = new UserData(ui->lineEditUser2->text(),
				  ui->lineEditPw2->text(),
				  true);
	  QDialog::accept();
	}
      else
	{
	  QMessageBox::warning(this, 
			       "Illegal entry",
			       "Empty user name or password");
	  return;
	}
      break;
					 
    default:
      QMessageBox::warning(this, "Dialog problem",
			       "Tab not set upon exit");
    }

  QDialog::accept();
}

void PwDialog::reject ()
{
  QDialog::reject();
}

PwDialog::~PwDialog()
{
    delete ui;
}
