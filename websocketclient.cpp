#include "websocketclient.h"

egge::client::WebSocketClient::WebSocketClient(const QUrl &url):
    m_socket(),
    m_proxy(QNetworkProxy::Socks5Proxy, "127.0.0.1", 9050)
{
    // Set up Tor a SOCKS5 proxy.

    m_socket.setProxy(m_proxy);

    connect(&m_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::errorOccurred),
            this, &WebSocketClient::handle_socket_error);
    connect(&m_socket, &QWebSocket::connected, this, &WebSocketClient::handle_new_connection);
    connect(&m_socket, &QWebSocket::disconnected, this, &WebSocketClient::handle_close_connection);
    connect(&m_socket, QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),
            this, &WebSocketClient::handle_ssl_errors);
    qDebug() << url.path();
    qDebug() << url.port();
    qDebug() << url.url();
    qDebug() << url.host();

    m_socket.open(url);

    qDebug() << m_socket.state();
}

bool egge::client::WebSocketClient::send_text_message ( const QString & message )
{

            int sent = m_socket.sendTextMessage ( message );
            if ( 0 != sent )
                return true;
            else
                return false;


}


bool egge::client::WebSocketClient::send_binary_message ( const QByteArray & binary_message )
{

    int sent = m_socket.sendBinaryMessage ( binary_message );
    if ( 0 != sent )
        return true;
    else
        return false;

}

void egge::client::WebSocketClient::handle_socket_error()
{
    qDebug() << "Error:" << m_socket.errorString();
}


void egge::client::WebSocketClient::handle_new_connection()
{
    qDebug() << "New Connection";

    connect(&m_socket, &QWebSocket::textMessageReceived,
            this, &WebSocketClient::handle_new_text_message);
    connect(&m_socket, &QWebSocket::binaryMessageReceived,
            this, &WebSocketClient::handle_new_binary_message);
}

void egge::client::WebSocketClient::handle_close_connection()
{
    qDebug() << "Connection closed.";
}

void egge::client::WebSocketClient::handle_new_text_message(const QString & message)
{
    qDebug() << "New Text Message:" << message;
}

void egge::client::WebSocketClient::handle_new_binary_message(const QByteArray & bin_message)
{
    qDebug() << "New binary message:" << bin_message;
}

void egge::client::WebSocketClient::handle_ssl_errors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);
    qDebug() << "SSL error:" << m_socket.errorString();
    m_socket.ignoreSslErrors();
}


