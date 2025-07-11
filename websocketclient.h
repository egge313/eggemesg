#pragma once

#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>

//Util
#include <QObject>
#include <QDebug>

namespace egge
{
    namespace client
    {
        class WebSocketClient : public QObject
        {
            public:
                WebSocketClient(const QUrl& url, QString& message);
            private slots:
                void handle_new_connection();
                void handle_close_connection();
                void handle_new_text_message(const QString & message);
                void handle_ssl_errors(const QList<QSslError> &errors);
                void handle_socket_error();
                void handle_new_binary_message(const QByteArray & binary_message);
            private:
                QWebSocket m_socket;
                QNetworkProxy m_proxy;
                QString m_message;
        };
    }
}


