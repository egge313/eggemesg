/********************************************************************************
** Form generated from reading UI file 'pwdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PWDIALOG_H
#define UI_PWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PwDialog
{
public:
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabLogin;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBoxGloballyVisible;
    QLabel *label;
    QLineEdit *lineEditUser1;
    QLabel *label_2;
    QLineEdit *lineEditPw1;
    QWidget *tabRegister;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lineEditUser2;
    QLabel *label_4;
    QLineEdit *lineEditPw2;
    QLabel *label_5;
    QLineEdit *lineEditPwRepeat2;
    QWidget *tabScorchedEarth;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEditPw3;
    QLineEdit *lineEditPw3Repeat;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PwDialog)
    {
        if (PwDialog->objectName().isEmpty())
            PwDialog->setObjectName(QStringLiteral("PwDialog"));
        PwDialog->resize(481, 187);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        PwDialog->setWindowIcon(icon);
        PwDialog->setSizeGripEnabled(false);
        gridLayout_2 = new QGridLayout(PwDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(PwDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setCursor(QCursor(Qt::PointingHandCursor));
        tabWidget->setMouseTracking(true);
        tabWidget->setStyleSheet(QStringLiteral("font: 75 9pt \"Noto Sans\";"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideRight);
        tabLogin = new QWidget();
        tabLogin->setObjectName(QStringLiteral("tabLogin"));
        tabLogin->setCursor(QCursor(Qt::PointingHandCursor));
        gridLayout_3 = new QGridLayout(tabLogin);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        checkBoxGloballyVisible = new QCheckBox(tabLogin);
        checkBoxGloballyVisible->setObjectName(QStringLiteral("checkBoxGloballyVisible"));

        gridLayout_3->addWidget(checkBoxGloballyVisible, 0, 1, 1, 1);

        label = new QLabel(tabLogin);
        label->setObjectName(QStringLiteral("label"));
        label->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout_3->addWidget(label, 1, 0, 1, 1);

        lineEditUser1 = new QLineEdit(tabLogin);
        lineEditUser1->setObjectName(QStringLiteral("lineEditUser1"));

        gridLayout_3->addWidget(lineEditUser1, 1, 1, 1, 1);

        label_2 = new QLabel(tabLogin);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 2, 0, 1, 1);

        lineEditPw1 = new QLineEdit(tabLogin);
        lineEditPw1->setObjectName(QStringLiteral("lineEditPw1"));
        lineEditPw1->setEchoMode(QLineEdit::Password);

        gridLayout_3->addWidget(lineEditPw1, 2, 1, 1, 1);

        tabWidget->addTab(tabLogin, QString());
        tabRegister = new QWidget();
        tabRegister->setObjectName(QStringLiteral("tabRegister"));
        tabRegister->setCursor(QCursor(Qt::PointingHandCursor));
        tabRegister->setMouseTracking(true);
        gridLayout = new QGridLayout(tabRegister);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(tabRegister);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lineEditUser2 = new QLineEdit(tabRegister);
        lineEditUser2->setObjectName(QStringLiteral("lineEditUser2"));

        gridLayout->addWidget(lineEditUser2, 0, 1, 1, 1);

        label_4 = new QLabel(tabRegister);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        lineEditPw2 = new QLineEdit(tabRegister);
        lineEditPw2->setObjectName(QStringLiteral("lineEditPw2"));
        lineEditPw2->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEditPw2, 1, 1, 1, 1);

        label_5 = new QLabel(tabRegister);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        lineEditPwRepeat2 = new QLineEdit(tabRegister);
        lineEditPwRepeat2->setObjectName(QStringLiteral("lineEditPwRepeat2"));
        lineEditPwRepeat2->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEditPwRepeat2, 2, 1, 1, 1);

        tabWidget->addTab(tabRegister, QString());
        tabScorchedEarth = new QWidget();
        tabScorchedEarth->setObjectName(QStringLiteral("tabScorchedEarth"));
        tabScorchedEarth->setEnabled(false);
        label_6 = new QLabel(tabScorchedEarth);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 10, 431, 20));
        label_6->setTextFormat(Qt::PlainText);
        label_6->setScaledContents(true);
        label_7 = new QLabel(tabScorchedEarth);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 40, 101, 20));
        label_8 = new QLabel(tabScorchedEarth);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 70, 111, 17));
        lineEditPw3 = new QLineEdit(tabScorchedEarth);
        lineEditPw3->setObjectName(QStringLiteral("lineEditPw3"));
        lineEditPw3->setGeometry(QRect(130, 40, 251, 25));
        lineEditPw3->setEchoMode(QLineEdit::Password);
        lineEditPw3Repeat = new QLineEdit(tabScorchedEarth);
        lineEditPw3Repeat->setObjectName(QStringLiteral("lineEditPw3Repeat"));
        lineEditPw3Repeat->setGeometry(QRect(130, 70, 251, 25));
        lineEditPw3Repeat->setEchoMode(QLineEdit::Password);
        tabWidget->addTab(tabScorchedEarth, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(PwDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setCursor(QCursor(Qt::PointingHandCursor));
        buttonBox->setMouseTracking(true);
        buttonBox->setFocusPolicy(Qt::StrongFocus);
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(PwDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PwDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PwDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PwDialog);
    } // setupUi

    void retranslateUi(QDialog *PwDialog)
    {
        PwDialog->setWindowTitle(QApplication::translate("PwDialog", "Egge's Messenger: Login", Q_NULLPTR));
#ifndef QT_NO_ACCESSIBILITY
        tabLogin->setAccessibleName(QApplication::translate("PwDialog", "Login", Q_NULLPTR));
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_TOOLTIP
        checkBoxGloballyVisible->setToolTip(QApplication::translate("PwDialog", "User visible to all other users", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBoxGloballyVisible->setText(QApplication::translate("PwDialog", "Globally visible", Q_NULLPTR));
        label->setText(QApplication::translate("PwDialog", "User:", Q_NULLPTR));
        label_2->setText(QApplication::translate("PwDialog", "Password:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabLogin), QApplication::translate("PwDialog", "Login", Q_NULLPTR));
#ifndef QT_NO_ACCESSIBILITY
        tabRegister->setAccessibleName(QApplication::translate("PwDialog", "New user", Q_NULLPTR));
#endif // QT_NO_ACCESSIBILITY
        label_3->setText(QApplication::translate("PwDialog", "User:", Q_NULLPTR));
        label_4->setText(QApplication::translate("PwDialog", "Password:", Q_NULLPTR));
        label_5->setText(QApplication::translate("PwDialog", "Repeat password:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabRegister), QApplication::translate("PwDialog", " Register ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        tabScorchedEarth->setToolTip(QApplication::translate("PwDialog", "Scorched earth means you are leaving nothing behind. You burn everything. This is the ultimate precaution, the ultimate get-away.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tabScorchedEarth->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        label_6->setText(QApplication::translate("PwDialog", "Loggin in with this password leaves schorched earth behind.", Q_NULLPTR));
        label_7->setText(QApplication::translate("PwDialog", "Password:", Q_NULLPTR));
        label_8->setText(QApplication::translate("PwDialog", "Repeat password:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabScorchedEarth), QApplication::translate("PwDialog", "Precaution", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PwDialog: public Ui_PwDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PWDIALOG_H
