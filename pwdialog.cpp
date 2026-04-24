#include "pwdialog.h"
#include "ui_pwdialog.h"
#include "userdata.h"
#include <QMessageBox>
#include "sodium.h"
#include "pwhash.h"

PwDialog::PwDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PwDialog)
{
    ui->setupUi(this);
    ui->tabScorchedEarth->setEnabled ( false );
}

void PwDialog::accept ()
{
  switch (ui->tabWidget->currentIndex())
    {
    case 0: /* login tab */
      if (ui->lineEditUser1->text().length() > 0 &&
          ui->lineEditPw1->text().length() > 0)
        {
          PwHash pwhash;
          pwhash.readFile();
          if ( !pwhash.verify ( ui->lineEditPw1->text(),
                             ui->lineEditUser1->text() ))
          {
              QMessageBox::warning(this, "Illegal user name or password",
                                   "Verification failure"
                                   );
              return;
          }
          m_userdata = new UserData ( ui->lineEditUser1->text(),
                                      ui->lineEditPw1->text(),
                                      "",
                                      false );
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

    case 1: /* register tab */
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
          PwHash pwhash;
          if ( !pwhash.createHash ( ui->lineEditPw2->text(), ui->lineEditUser2->text() ))
          {
              QMessageBox::warning(this, "Password hash not created",
                                   "(Probably out of memory)");
              return;
          }
          pwhash.writeFile();

          m_userdata = new UserData(ui->lineEditUser2->text(),
                                  ui->lineEditPw2->text(),
                                    "",
                                  true);
          ui->tabScorchedEarth->setEnabled(true);
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

    case 2: /* scorched earth tab */
      if (ui->lineEditPw3->text().length() > 0 &&
          ui->lineEditPw3Repeat->text().length() > 0)
        {
          if (ui->lineEditPw3->text() !=
              ui->lineEditPw3Repeat->text())
            {
              QMessageBox::warning(this, "Password not repeated",
                                   "Need to repeat the same password!");
              return;
            }
          m_userdata = new UserData("",
                                    "",
                                    ui->lineEditPw3->text(),
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
      break; /* Just to make the compiler happy. */
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
