#pragma once

#include <QString>

class EggeMessage
{
private:
    // Forbid copy constructor.
    EggeMessage(EggeMessage const &);

    // Forbid assignment operator.
    EggeMessage& operator=(EggeMessage const &);

public:
    EggeMessage() : m_message ( "" ) {}
    EggeMessage ( const QString & str ) : m_message ( str ) {}
    append ( const QString & str ) { m_message += str; }
    retrieve ( QString & str ) { str = m_message; }
    destroy () { m_message = ""; }

    ~EggeMessage() {}

public:
    QString m_message;
};
