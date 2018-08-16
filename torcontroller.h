#ifndef TORCONTROLLER_H
#define TORCONTROLLER_H 1

#include <QTcpSocket>
#include <QDataStream>
#include <QNetworkSession>
#include <QMessageBox>

class TorController
{
    Q_OBJECT

public:
    TorController () : m_tcpsocket(new QTcpSocket(this))
      {
	m_in.setDevice(m_tcpsocket);
	m_in.setVersion(QDataStream::Qt_4_0);
	m_out.setDevice(m_tcpsocket);
	m_out.setVersion(QDataStream::Qt_4_0);	
	connect(tcpSocket, &QIODevice::readyRead, this,
		&TorController::readit);
	connect(tcpSocket,
		QOverload<QAbstractSocket::SocketError>
		            ::of(&QAbstractSocket::error),
		this, &TorController::handleerror);
      }

    // ---
    bool connect (const QString host, const int port)
      {
	m_tcpsocket->connectToHost(host, port, QIODevice::ReadWrite);
	return (m_tcpsocket->waitForConnected(50000));
      }

    // ---
    void readit () // emits incoming
    {
      while (m_tcpsocket->bytesAvailable())
	{
	  QString readstr;
	  m_in >> readstr;
	  emit incoming (readstr);
	}
    }

    // ---
    void writeit (const QString message) // emits incoming
    {
      m_out << message;
    }

    // -----
    ~TorController ()
      {
	m_tcpsocket->abort();
	delete m_tcpsocket;
      };

signals:

    void incoming (const QString message);

private slots:
    void requestNewFortune();
    void readFortune();

    void handleerror(QAbstractSocket::SocketError socketError)
    {
      switch (socketError)
	{
	case QAbstractSocket::RemoteHostClosedError:
	  break;
	case QAbstractSocket::HostNotFoundError:
	  QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
	  break;
	case QAbstractSocket::ConnectionRefusedError:
	  QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
	  break;
	default:
	  QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
	}


    }

private:
    QTcpSocket *m_tcpsocket = nullptr;
    QDataStream m_in;
    QDataStream m_out;    

    QNetworkSession *networkSession = nullptr;
};

#endif // TORCONTROLLER_H
