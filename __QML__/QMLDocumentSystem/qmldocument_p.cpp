#include "qmldocument_p.h"

QMLDocument_P::QMLDocument_P(QMLDocument *parent) :
    QObject(parent),
    m__Source( NULL )
{
}

QMLDocument * QMLDocument_P::p_dptr() const
{
    return qobject_cast<QMLDocument *>( parent() );
}
