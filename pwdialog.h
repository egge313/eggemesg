#ifndef PWDIALOG_H
#define PWDIALOG_H

#include <QDialog>
#include "userdata.h"

namespace Ui {
class PwDialog;
}

class PwDialog : public QDialog
{
    Q_OBJECT

 public:
    UserData * m_userdata = NULL;

 public:
    explicit PwDialog(QWidget *parent = 0);
    UserData * getUserData () { return m_userdata; }
    ~PwDialog();
    
 public slots:
      void accept ();
      void reject ();

 private:
    Ui::PwDialog *ui;
};

#endif // PWDIALOG_H
