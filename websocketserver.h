#pragma once

//Qt includes
//WebSocket
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
//Util
#include <QObject>
#include <QDebug>

namespace egge {
    namespace server{
        class WebSocketServer : public QObject{
            Q_OBJECT
            public:
                WebSocketServer(int port, QObject* parent = nullptr);
            private:
                void handle_new_connection();
                void handle_close_connection();
                void handle_text_message();
                void handle_binary_message();
                void handle_disconnect();

                QWebSocketServer* m_ws_server;
                std::vector<QWebSocket*> m_clients;
        };
    }
}

// end of websocketserver.h

