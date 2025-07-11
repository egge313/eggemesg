#pragma once

//Qt includes
//WebSocket
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
//Util
#include <QObject>
#include <QDebug>
#include <QString>
#include <QByteArray>

namespace egge {
    namespace server{
        class WebSocketServer : public QObject
        {
            Q_OBJECT

        signals:
                void signalTextMessage ( QString message );
                void signalBinaryMessage ( QByteArray binmessage );

        public:
                WebSocketServer(int port, QObject* parent = nullptr);
                bool isListening() { if ( nullptr == m_ws_server ) return false; else return m_ws_server->isListening(); }

                // Get one message. Return false if there are no messages. Delete message if requested.
                bool getMessage ( QString & message, bool deleteMessage );

        private:
                void handle_new_connection();
                void handle_close_connection();
                void handle_text_message( QString message );
                void handle_binary_message( QByteArray binmessage );
                void handle_disconnect();

                QWebSocketServer* m_ws_server;
                std::vector<QWebSocket*> m_clients;
                QList< QString > m_messages;
        };
    }
}

// end of websocketserver.h

