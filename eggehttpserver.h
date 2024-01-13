#ifndef EGGEHTTPSERVER
#define EGGEHTTPSERVER 1

#include <QByteArray>
#include <QString>

// Create an HTTP server at a given port.
// eggehttpserver -- Returns 0 on success, 1 on failure.
int eggehttpserver ( const int port,
                     QByteArray & message,
                     QString & errmsg );

#endif
