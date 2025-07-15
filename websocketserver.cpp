#include "websocketserver.h"

egge::server::WebSocketServer::WebSocketServer(int port, QObject* parent):
    QObject(parent),
    m_ws_server(new QWebSocketServer("Eggemesg onion service", QWebSocketServer::NonSecureMode, this))
    {
        if(m_ws_server->listen(QHostAddress::Any, port))
        {
            qDebug() << "Connect handlers";
            connect(m_ws_server, &QWebSocketServer::newConnection, this, &WebSocketServer::handle_new_connection);
            connect(m_ws_server, &QWebSocketServer::closed, this, &WebSocketServer::handle_close_connection);
        }
    if(m_ws_server->isListening())
        {
            qDebug() << "Still Listening";
        }
}


void egge::server::WebSocketServer::handle_new_connection()
{
    qDebug() << "New Connection";
    QWebSocket *client = m_ws_server->nextPendingConnection();

    connect(client, &QWebSocket::textMessageReceived, this, &WebSocketServer::handle_text_message, Qt::UniqueConnection);
    connect(client, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::handle_binary_message);
    connect(client, &QWebSocket::disconnected, this, &WebSocketServer::handle_disconnect);

    m_clients.push_back(client);
}

void egge::server::WebSocketServer::handle_close_connection()
{
    qDebug() << "Connection closed ";
}

// Get one message. Return false if there are no messages. Delete message if requested.
bool egge::server::WebSocketServer::getMessage ( QString & message, bool deleteMessage = false )
{
    if ( m_messages.size() == 0)
        return false;
    message = m_messages[0];
    if ( deleteMessage )
        m_messages.removeFirst();
    return true;
}

void egge::server::WebSocketServer::handle_text_message( QString message )
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "handLe_text_message: Text message:" + message;
    m_messages.append ( message );
    emit signalTextMessage ( message );
}

void egge::server::WebSocketServer::handle_binary_message (QByteArray binmessage )
{
    qDebug() << "Binary message";
    emit signalBinaryMessage( binmessage );
}

void egge::server::WebSocketServer::handle_disconnect()
{
    // Need to remove sender from connections.
    qDebug() << "Disconnect";
}
