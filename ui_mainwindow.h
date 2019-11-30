/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *frame001;
    QFrame *frame003;
    QLabel *labelInformation;
    QFrame *frame002;
    QTextEdit *textEditMyMessages;
    QPushButton *Send;
    QTextEdit *textEditMessages;
    QPushButton *pushButtonLogin;
    QPushButton *pushButtonSetKeys;
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonInvisible;
    QPushButton *pushButtonLogout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(722, 566);
        MainWindow->setMinimumSize(QSize(722, 566));
        QIcon icon;
        icon.addFile(QStringLiteral("icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QFont font;
        font.setPointSize(11);
        centralwidget->setFont(font);
        centralwidget->setMouseTracking(true);
        centralwidget->setTabletTracking(true);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame001 = new QFrame(centralwidget);
        frame001->setObjectName(QStringLiteral("frame001"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame001->sizePolicy().hasHeightForWidth());
        frame001->setSizePolicy(sizePolicy);
        frame001->setSizeIncrement(QSize(1, 1));
        frame001->setStyleSheet(QStringLiteral(""));
        frame001->setFrameShape(QFrame::StyledPanel);
        frame001->setFrameShadow(QFrame::Sunken);
        frame003 = new QFrame(frame001);
        frame003->setObjectName(QStringLiteral("frame003"));
        frame003->setGeometry(QRect(10, 46, 681, 41));
        frame003->setFrameShape(QFrame::StyledPanel);
        frame003->setFrameShadow(QFrame::Raised);
        labelInformation = new QLabel(frame003);
        labelInformation->setObjectName(QStringLiteral("labelInformation"));
        labelInformation->setGeometry(QRect(20, 20, 621, 61));
        frame002 = new QFrame(frame001);
        frame002->setObjectName(QStringLiteral("frame002"));
        frame002->setGeometry(QRect(10, 107, 401, 211));
        textEditMyMessages = new QTextEdit(frame002);
        textEditMyMessages->setObjectName(QStringLiteral("textEditMyMessages"));
        textEditMyMessages->setGeometry(QRect(10, 10, 381, 191));
        Send = new QPushButton(frame001);
        Send->setObjectName(QStringLiteral("Send"));
        Send->setGeometry(QRect(540, 360, 125, 30));
        textEditMessages = new QTextEdit(frame001);
        textEditMessages->setObjectName(QStringLiteral("textEditMessages"));
        textEditMessages->setGeometry(QRect(25, 340, 371, 82));
        textEditMessages->setMinimumSize(QSize(256, 82));
        textEditMessages->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditMessages->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        pushButtonLogin = new QPushButton(frame001);
        pushButtonLogin->setObjectName(QStringLiteral("pushButtonLogin"));
        pushButtonLogin->setGeometry(QRect(11, 12, 104, 26));
        pushButtonLogin->setMinimumSize(QSize(104, 26));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        pushButtonLogin->setFont(font1);
        pushButtonLogin->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonLogin->setMouseTracking(true);
        pushButtonLogin->setFocusPolicy(Qt::StrongFocus);
        pushButtonLogin->setAutoFillBackground(false);
        pushButtonLogin->setStyleSheet(QStringLiteral(""));
        pushButtonLogin->setFlat(false);
        pushButtonSetKeys = new QPushButton(frame001);
        pushButtonSetKeys->setObjectName(QStringLiteral("pushButtonSetKeys"));
        pushButtonSetKeys->setGeometry(QRect(121, 12, 80, 26));
        pushButtonSetKeys->setMinimumSize(QSize(80, 26));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        pushButtonSetKeys->setFont(font2);
        pushButtonSetKeys->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonSetKeys->setMouseTracking(true);
        pushButtonSetKeys->setFocusPolicy(Qt::StrongFocus);
        pushButtonSetKeys->setAutoFillBackground(false);
        pushButtonSetKeys->setFlat(false);
        pushButtonConnect = new QPushButton(frame001);
        pushButtonConnect->setObjectName(QStringLiteral("pushButtonConnect"));
        pushButtonConnect->setGeometry(QRect(207, 12, 80, 26));
        pushButtonConnect->setMinimumSize(QSize(80, 26));
        pushButtonConnect->setFont(font2);
        pushButtonConnect->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonConnect->setMouseTracking(true);
        pushButtonConnect->setFocusPolicy(Qt::StrongFocus);
        pushButtonConnect->setAutoFillBackground(false);
        pushButtonConnect->setFlat(false);
        pushButtonInvisible = new QPushButton(frame001);
        pushButtonInvisible->setObjectName(QStringLiteral("pushButtonInvisible"));
        pushButtonInvisible->setEnabled(false);
        pushButtonInvisible->setGeometry(QRect(293, 11, 101, 28));
        pushButtonInvisible->setMinimumSize(QSize(101, 28));
        pushButtonInvisible->setFocusPolicy(Qt::NoFocus);
        pushButtonLogout = new QPushButton(frame001);
        pushButtonLogout->setObjectName(QStringLiteral("pushButtonLogout"));
        pushButtonLogout->setGeometry(QRect(400, 12, 80, 26));
        pushButtonLogout->setMinimumSize(QSize(80, 26));
        QFont font3;
        font3.setPointSize(10);
        pushButtonLogout->setFont(font3);
        pushButtonLogout->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonLogout->setMouseTracking(true);

        gridLayout->addWidget(frame001, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Egge's Messenger", Q_NULLPTR));
        labelInformation->setText(QString());
        Send->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButtonLogin->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButtonLogin->setStatusTip(QApplication::translate("MainWindow", "Login or sign in", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        pushButtonLogin->setText(QApplication::translate("MainWindow", "Login/Register", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        pushButtonSetKeys->setStatusTip(QApplication::translate("MainWindow", "Set cryptographic keys for encryption and signing", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        pushButtonSetKeys->setText(QApplication::translate("MainWindow", "Set keys", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        pushButtonConnect->setStatusTip(QApplication::translate("MainWindow", "Connect to network", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        pushButtonConnect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        pushButtonInvisible->setText(QString());
        pushButtonLogout->setText(QApplication::translate("MainWindow", "Logout", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
