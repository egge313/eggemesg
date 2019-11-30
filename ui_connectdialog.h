/********************************************************************************
** Form generated from reading UI file 'connectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTDIALOG_H
#define UI_CONNECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectDialog
{
public:
    QGridLayout *gridLayout_3;
    QTabWidget *tabConnect;
    QWidget *tabClient;
    QGridLayout *gridLayout;
    QLabel *labelClientInfo;
    QComboBox *comboBoxServerIP;
    QLabel *labelServerIP;
    QComboBox *comboBoxServerPortNumber;
    QLabel *labelServerPortNumber;
    QLabel *labelClientInfo_2;
    QPushButton *pushButtonConnect2Server;
    QWidget *tabServer;
    QListWidget *listWidgetHostInfo;
    QGroupBox *groupBoxServerOnOff;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButtonStartServerOK;
    QRadioButton *radioButtonStartServerNAK;
    QPushButton *pushButtonLaunchServer;
    QLabel *labelServerInfo;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelServerPortNumber_2;
    QLineEdit *lineEditServerPortNumber;
    QLabel *labelServerInfo_2;
    QWidget *tabTorControl;
    QVBoxLayout *verticalLayout;
    QLabel *labelTorControlInfo;
    QListWidget *listWidgetTorControlHistory;
    QWidget *tabTorClient;
    QHBoxLayout *horizontalLayout;
    QLabel *labelTorClientInfo2;
    QListWidget *listWidgetTorClientFeedback;
    QLabel *labelTorClientInfo;
    QComboBox *comboBoxTorClientServer;
    QPushButton *pushButtonTorClientConnect;

    void setupUi(QDialog *ConnectDialog)
    {
        if (ConnectDialog->objectName().isEmpty())
            ConnectDialog->setObjectName(QStringLiteral("ConnectDialog"));
        ConnectDialog->resize(613, 448);
        ConnectDialog->setMouseTracking(true);
        ConnectDialog->setFocusPolicy(Qt::StrongFocus);
        ConnectDialog->setAutoFillBackground(true);
        ConnectDialog->setModal(true);
        gridLayout_3 = new QGridLayout(ConnectDialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tabConnect = new QTabWidget(ConnectDialog);
        tabConnect->setObjectName(QStringLiteral("tabConnect"));
        tabConnect->setMaximumSize(QSize(601, 461));
        tabConnect->setUsesScrollButtons(false);
        tabConnect->setDocumentMode(false);
        tabConnect->setTabsClosable(false);
        tabConnect->setMovable(true);
        tabConnect->setTabBarAutoHide(false);
        tabClient = new QWidget();
        tabClient->setObjectName(QStringLiteral("tabClient"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        tabClient->setFont(font);
        tabClient->setCursor(QCursor(Qt::PointingHandCursor));
        tabClient->setMouseTracking(true);
        gridLayout = new QGridLayout(tabClient);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelClientInfo = new QLabel(tabClient);
        labelClientInfo->setObjectName(QStringLiteral("labelClientInfo"));
        labelClientInfo->setStyleSheet(QStringLiteral("QLabel {font-style: italic}"));

        gridLayout->addWidget(labelClientInfo, 0, 0, 1, 1);

        comboBoxServerIP = new QComboBox(tabClient);
        comboBoxServerIP->setObjectName(QStringLiteral("comboBoxServerIP"));
        comboBoxServerIP->setCursor(QCursor(Qt::PointingHandCursor));
        comboBoxServerIP->setMouseTracking(true);
        comboBoxServerIP->setEditable(true);

        gridLayout->addWidget(comboBoxServerIP, 1, 0, 1, 1);

        labelServerIP = new QLabel(tabClient);
        labelServerIP->setObjectName(QStringLiteral("labelServerIP"));

        gridLayout->addWidget(labelServerIP, 2, 0, 1, 1);

        comboBoxServerPortNumber = new QComboBox(tabClient);
        comboBoxServerPortNumber->setObjectName(QStringLiteral("comboBoxServerPortNumber"));
        comboBoxServerPortNumber->setCursor(QCursor(Qt::PointingHandCursor));
        comboBoxServerPortNumber->setEditable(true);

        gridLayout->addWidget(comboBoxServerPortNumber, 3, 0, 1, 1);

        labelServerPortNumber = new QLabel(tabClient);
        labelServerPortNumber->setObjectName(QStringLiteral("labelServerPortNumber"));

        gridLayout->addWidget(labelServerPortNumber, 4, 0, 1, 1);

        labelClientInfo_2 = new QLabel(tabClient);
        labelClientInfo_2->setObjectName(QStringLiteral("labelClientInfo_2"));

        gridLayout->addWidget(labelClientInfo_2, 5, 0, 1, 1);

        pushButtonConnect2Server = new QPushButton(tabClient);
        pushButtonConnect2Server->setObjectName(QStringLiteral("pushButtonConnect2Server"));

        gridLayout->addWidget(pushButtonConnect2Server, 6, 0, 1, 1);

        tabConnect->addTab(tabClient, QString());
        tabServer = new QWidget();
        tabServer->setObjectName(QStringLiteral("tabServer"));
        tabServer->setFont(font);
        listWidgetHostInfo = new QListWidget(tabServer);
        listWidgetHostInfo->setObjectName(QStringLiteral("listWidgetHostInfo"));
        listWidgetHostInfo->setGeometry(QRect(20, 60, 241, 201));
        QFont font1;
        font1.setPointSize(8);
        listWidgetHostInfo->setFont(font1);
        groupBoxServerOnOff = new QGroupBox(tabServer);
        groupBoxServerOnOff->setObjectName(QStringLiteral("groupBoxServerOnOff"));
        groupBoxServerOnOff->setGeometry(QRect(280, 60, 292, 96));
        gridLayout_2 = new QGridLayout(groupBoxServerOnOff);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        radioButtonStartServerOK = new QRadioButton(groupBoxServerOnOff);
        radioButtonStartServerOK->setObjectName(QStringLiteral("radioButtonStartServerOK"));

        gridLayout_2->addWidget(radioButtonStartServerOK, 0, 0, 1, 1);

        radioButtonStartServerNAK = new QRadioButton(groupBoxServerOnOff);
        radioButtonStartServerNAK->setObjectName(QStringLiteral("radioButtonStartServerNAK"));
        radioButtonStartServerNAK->setChecked(true);

        gridLayout_2->addWidget(radioButtonStartServerNAK, 1, 0, 1, 1);

        pushButtonLaunchServer = new QPushButton(tabServer);
        pushButtonLaunchServer->setObjectName(QStringLiteral("pushButtonLaunchServer"));
        pushButtonLaunchServer->setGeometry(QRect(450, 210, 121, 40));
        labelServerInfo = new QLabel(tabServer);
        labelServerInfo->setObjectName(QStringLiteral("labelServerInfo"));
        labelServerInfo->setGeometry(QRect(20, 20, 561, 17));
        labelServerInfo->setStyleSheet(QStringLiteral("QLabel {font-style: italic}"));
        frame = new QFrame(tabServer);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(280, 187, 145, 68));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        labelServerPortNumber_2 = new QLabel(frame);
        labelServerPortNumber_2->setObjectName(QStringLiteral("labelServerPortNumber_2"));

        verticalLayout_3->addWidget(labelServerPortNumber_2);

        lineEditServerPortNumber = new QLineEdit(frame);
        lineEditServerPortNumber->setObjectName(QStringLiteral("lineEditServerPortNumber"));

        verticalLayout_3->addWidget(lineEditServerPortNumber);

        labelServerInfo_2 = new QLabel(tabServer);
        labelServerInfo_2->setObjectName(QStringLiteral("labelServerInfo_2"));
        labelServerInfo_2->setGeometry(QRect(20, 280, 561, 17));
        tabConnect->addTab(tabServer, QString());
        tabTorControl = new QWidget();
        tabTorControl->setObjectName(QStringLiteral("tabTorControl"));
        verticalLayout = new QVBoxLayout(tabTorControl);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelTorControlInfo = new QLabel(tabTorControl);
        labelTorControlInfo->setObjectName(QStringLiteral("labelTorControlInfo"));

        verticalLayout->addWidget(labelTorControlInfo);

        listWidgetTorControlHistory = new QListWidget(tabTorControl);
        listWidgetTorControlHistory->setObjectName(QStringLiteral("listWidgetTorControlHistory"));

        verticalLayout->addWidget(listWidgetTorControlHistory);

        tabConnect->addTab(tabTorControl, QString());
        tabTorClient = new QWidget();
        tabTorClient->setObjectName(QStringLiteral("tabTorClient"));
        tabTorClient->setFocusPolicy(Qt::TabFocus);
        horizontalLayout = new QHBoxLayout(tabTorClient);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelTorClientInfo2 = new QLabel(tabTorClient);
        labelTorClientInfo2->setObjectName(QStringLiteral("labelTorClientInfo2"));
        QFont font2;
        font2.setItalic(true);
        labelTorClientInfo2->setFont(font2);

        horizontalLayout->addWidget(labelTorClientInfo2);

        listWidgetTorClientFeedback = new QListWidget(tabTorClient);
        listWidgetTorClientFeedback->setObjectName(QStringLiteral("listWidgetTorClientFeedback"));

        horizontalLayout->addWidget(listWidgetTorClientFeedback);

        labelTorClientInfo = new QLabel(tabTorClient);
        labelTorClientInfo->setObjectName(QStringLiteral("labelTorClientInfo"));
        labelTorClientInfo->setFont(font2);

        horizontalLayout->addWidget(labelTorClientInfo);

        comboBoxTorClientServer = new QComboBox(tabTorClient);
        comboBoxTorClientServer->setObjectName(QStringLiteral("comboBoxTorClientServer"));
        comboBoxTorClientServer->setCursor(QCursor(Qt::OpenHandCursor));
        comboBoxTorClientServer->setEditable(true);

        horizontalLayout->addWidget(comboBoxTorClientServer);

        pushButtonTorClientConnect = new QPushButton(tabTorClient);
        pushButtonTorClientConnect->setObjectName(QStringLiteral("pushButtonTorClientConnect"));
        pushButtonTorClientConnect->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonTorClientConnect->setMouseTracking(true);

        horizontalLayout->addWidget(pushButtonTorClientConnect);

        tabConnect->addTab(tabTorClient, QString());

        gridLayout_3->addWidget(tabConnect, 0, 0, 1, 1);


        retranslateUi(ConnectDialog);

        tabConnect->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ConnectDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectDialog)
    {
        ConnectDialog->setWindowTitle(QApplication::translate("ConnectDialog", "Egge's Messenger: Connect", Q_NULLPTR));
        labelClientInfo->setText(QApplication::translate("ConnectDialog", "Create connection to server as client", Q_NULLPTR));
        labelServerIP->setText(QApplication::translate("ConnectDialog", "Server IP number:", Q_NULLPTR));
        labelServerPortNumber->setText(QApplication::translate("ConnectDialog", "Server port number:", Q_NULLPTR));
        labelClientInfo_2->setText(QApplication::translate("ConnectDialog", "(Currently no connection.)", Q_NULLPTR));
        pushButtonConnect2Server->setText(QApplication::translate("ConnectDialog", "Connect", Q_NULLPTR));
        tabConnect->setTabText(tabConnect->indexOf(tabClient), QApplication::translate("ConnectDialog", "Client", Q_NULLPTR));
        groupBoxServerOnOff->setTitle(QApplication::translate("ConnectDialog", "Start server on this host?", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        radioButtonStartServerOK->setToolTip(QApplication::translate("ConnectDialog", "Accept providing server capability on this host. ", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        radioButtonStartServerOK->setText(QApplication::translate("ConnectDialog", "Yes, I'm cool with it!", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        radioButtonStartServerNAK->setToolTip(QApplication::translate("ConnectDialog", "No server capability will be provided on this host.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        radioButtonStartServerNAK->setText(QApplication::translate("ConnectDialog", "Sorry, I'm otherwise ... ahem ... engaged.", Q_NULLPTR));
        pushButtonLaunchServer->setText(QApplication::translate("ConnectDialog", "Launch", Q_NULLPTR));
        labelServerInfo->setText(QApplication::translate("ConnectDialog", "Provide server functionality from this host", Q_NULLPTR));
        labelServerPortNumber_2->setText(QApplication::translate("ConnectDialog", "Server port number:", Q_NULLPTR));
        labelServerInfo_2->setText(QString());
        tabConnect->setTabText(tabConnect->indexOf(tabServer), QApplication::translate("ConnectDialog", "Server", Q_NULLPTR));
        labelTorControlInfo->setText(QApplication::translate("ConnectDialog", "Tor control and oversight", Q_NULLPTR));
        tabConnect->setTabText(tabConnect->indexOf(tabTorControl), QApplication::translate("ConnectDialog", " Tor Control ", Q_NULLPTR));
        labelTorClientInfo2->setText(QString());
        labelTorClientInfo->setText(QApplication::translate("ConnectDialog", "Connect to server via Tor", Q_NULLPTR));
        pushButtonTorClientConnect->setText(QApplication::translate("ConnectDialog", "Connect", Q_NULLPTR));
        tabConnect->setTabText(tabConnect->indexOf(tabTorClient), QApplication::translate("ConnectDialog", " Tor Client ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConnectDialog: public Ui_ConnectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTDIALOG_H
