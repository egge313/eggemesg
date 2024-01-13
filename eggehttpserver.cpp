
#include <QHttpServer>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QFile>
#include <QDebug>
#include "eggehttpserver.h"

// Create an HTTP server at a given port.
// eggehttpserver -- Returns 0 on success, 1 on failure.
    int eggehttpserver ( const int port,
                   QByteArray & message,
                   QString & errmsg )
{

    // Create an HTTP server
    QHttpServer httpServer;

    httpServer.route ( "/", [](const QHttpServerRequest & request ){
        // Check if the request method is POST
        if (request.method() == QHttpServerRequest::Method::Post) {
            // Read the binary data from the request body
            QByteArray data = request.body();

            qDebug() << "Data = '" << data << "'\n" << "Length = " << data.length();

            // Save the data to a file
            QFile file("data.bin");
            file.open(QIODevice::Append);
            file.write(data);
            file.close();

            // Send a response with status code 200 (OK)
            return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
        } else {
            // Send a response with status code 405 (Method Not Allowed)
            return QHttpServerResponse(QHttpServerResponse::StatusCode::MethodNotAllowed);
        }
    });

    const auto myport = httpServer.listen(QHostAddress::Any, port);
    if (!myport) {
        errmsg = "Server failed to listen on a port.";
        return 1;
    }
    else
    {
        // Save the data to a file
        QFile file("data.bin");
        file.open(QIODevice::ReadOnly);
        message = file.readAll() ;
        file.close();
        return 0;
    }
}
