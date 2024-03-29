#ifndef CRYPTODIALOG_H
#define CRYPTODIALOG_H

#include "userdata.h"
#include <QDialog>
#include <QListWidget>

namespace Ui {
class CryptoDialog;
}

class CryptoDialog : public QDialog
{
    Q_OBJECT

 public:
    explicit CryptoDialog(QWidget *parent = 0, UserData * userdata = 0);
    ~CryptoDialog();

 private slots:
    void onGeneratePushButtonClicked ();
    void onSelectionChanged();

 private:
    Ui::CryptoDialog *ui;
    UserData * m_userdata;

};

#endif // CRYPTODIALOG_H
