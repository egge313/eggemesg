/********************************************************************************
** Form generated from reading UI file 'cryptodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRYPTODIALOG_H
#define UI_CRYPTODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CryptoDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *cryptoLabel;
    QListWidget *cryptoListWidget;
    QLabel *generateLabel;
    QPushButton *generatePushButton;
    QTextBrowser *keyTextBrowser;
    QDialogButtonBox *cryptoButtonBox;

    void setupUi(QDialog *CryptoDialog)
    {
        if (CryptoDialog->objectName().isEmpty())
            CryptoDialog->setObjectName(QStringLiteral("CryptoDialog"));
        CryptoDialog->resize(640, 562);
        verticalLayout = new QVBoxLayout(CryptoDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(CryptoDialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cryptoLabel = new QLabel(frame);
        cryptoLabel->setObjectName(QStringLiteral("cryptoLabel"));
        cryptoLabel->setStyleSheet(QStringLiteral("QLabel { font-style: italic}"));
        cryptoLabel->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(cryptoLabel, 0, 0, 1, 2);

        cryptoListWidget = new QListWidget(frame);
        cryptoListWidget->setObjectName(QStringLiteral("cryptoListWidget"));
        cryptoListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        cryptoListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        cryptoListWidget->setViewMode(QListView::ListMode);
        cryptoListWidget->setSelectionRectVisible(true);

        gridLayout->addWidget(cryptoListWidget, 1, 0, 1, 2);

        generateLabel = new QLabel(frame);
        generateLabel->setObjectName(QStringLiteral("generateLabel"));
        generateLabel->setFrameShape(QFrame::NoFrame);
        generateLabel->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(generateLabel, 2, 0, 1, 1);

        generatePushButton = new QPushButton(frame);
        generatePushButton->setObjectName(QStringLiteral("generatePushButton"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        generatePushButton->setFont(font);
        generatePushButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(generatePushButton, 2, 1, 1, 1);

        keyTextBrowser = new QTextBrowser(frame);
        keyTextBrowser->setObjectName(QStringLiteral("keyTextBrowser"));

        gridLayout->addWidget(keyTextBrowser, 3, 0, 1, 2);


        verticalLayout->addWidget(frame);

        cryptoButtonBox = new QDialogButtonBox(CryptoDialog);
        cryptoButtonBox->setObjectName(QStringLiteral("cryptoButtonBox"));
        cryptoButtonBox->setCursor(QCursor(Qt::PointingHandCursor));
        cryptoButtonBox->setOrientation(Qt::Horizontal);
        cryptoButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        cryptoButtonBox->setCenterButtons(false);

        verticalLayout->addWidget(cryptoButtonBox);


        retranslateUi(CryptoDialog);
        QObject::connect(cryptoButtonBox, SIGNAL(accepted()), CryptoDialog, SLOT(accept()));
        QObject::connect(cryptoButtonBox, SIGNAL(rejected()), CryptoDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CryptoDialog);
    } // setupUi

    void retranslateUi(QDialog *CryptoDialog)
    {
        CryptoDialog->setWindowTitle(QApplication::translate("CryptoDialog", "Egge's Messenger: Cryptographic Keys", Q_NULLPTR));
        cryptoLabel->setText(QApplication::translate("CryptoDialog", "Modes for public key encryption and digital signatures:", Q_NULLPTR));
        generateLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        generatePushButton->setToolTip(QApplication::translate("CryptoDialog", "Generate an RSA keypair based on your selection", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        generatePushButton->setText(QApplication::translate("CryptoDialog", "Generate", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CryptoDialog: public Ui_CryptoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRYPTODIALOG_H
