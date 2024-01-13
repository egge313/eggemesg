#ifndef SERVERCTRL_H
#define SERVERCTRL_H

#include <QThread>
#include <QByteArray>
#include "eggehttpserver.h"
#include <QDebug>

class ServerWorker : public QThread
{
    Q_OBJECT

public:
    ServerWorker ( const int swport ) : m_port(swport) {}

    bool testrun ()
    {
        QByteArray* message = new QByteArray;
        qDebug() << "Testrun\n";
        emit resultReady ( true, *message, "Testrun");
        return 0;
    }

    void run () override
    {
        QByteArray* message = new QByteArray;
        QString errmsg;

        if ( ! eggehttpserver ( m_port, *message, errmsg ) )
        {
            qDebug() << "ServerWorker true";
            emit resultReady ( true, *message, "");
        }
        else
        {
            qDebug() << "ServerWorker false" << errmsg;
            emit resultReady ( false, *message, errmsg );
        }
    }

signals:
    void resultReady (const bool success, const QByteArray & message, const QString & errmsg);

private:
    int m_port;
};

class ServerController : public QObject
{
    Q_OBJECT

public:
    ServerController ( const int port )
    {
        ServerWorker *worker = new ServerWorker ( port );

        connect(worker, &QThread::finished, worker, &QObject::deleteLater);
        // connect(this, &ServerController::operate, worker, &ServerWorker::doWork );
        connect(worker, &ServerWorker::resultReady, this, &ServerController::handleResults);
        worker->start();
    }

    ~ServerController()
    {
        // workerThread.quit();
        // workerThread.wait();
    }

public slots:
    void handleResults(const bool success, const QByteArray & message, const QString & errmsg)
    {
        qDebug() << (success ? "Success " : "Failed ") << message << errmsg << "\n";
    };

};

#endif // SERVERCTRL_H
