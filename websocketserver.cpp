#include "websocketserver.h"

egge::server::WebSocketServer::WebSocketServer(int port, QObject* parent):
    QObject(parent),
    m_ws_server(new QWebSocketServer("Eggemesg onion service", QWebSocketServer::NonSecureMode, this)){
    if(m_ws_server->listen(QHostAddress::Any, port)){
        qDebug() << "Connect handlers";
        connect(m_ws_server, &QWebSocketServer::newConnection, this, &WebSocketServer::handle_new_connection);
        connect(m_ws_server, &QWebSocketServer::closed, this, &WebSocketServer::handle_close_connection);
    }
    if(m_ws_server->isListening()){
        qDebug() << "Still Listening";
    }
}


void egge::server::WebSocketServer::handle_new_connection(){
    qDebug() << "New Connection";
    QWebSocket *client = m_ws_server->nextPendingConnection();

    connect(client, &QWebSocket::textMessageReceived, this, &WebSocketServer::handle_text_message);
    connect(client, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::handle_binary_message);
    connect(client, &QWebSocket::disconnected, this, &WebSocketServer::handle_disconnect);

    m_clients.push_back(client);
}

void egge::server::WebSocketServer::handle_close_connection(){
    qDebug() << "Closed Connection";
}

void egge::server::WebSocketServer::handle_text_message(){
    qDebug() << "Text message";
}

void egge::server::WebSocketServer::handle_binary_message(){
    qDebug() << "Binary message";
}

void egge::server::WebSocketServer::handle_disconnect(){
    qDebug() << "Disconnect";
}
