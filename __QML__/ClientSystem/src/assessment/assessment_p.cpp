#include "assessment_p.h"


Assessment_P::Assessment_P(Assessment *parent) :
    QObject(parent),
    m__Link(NULL),
    m__NullString(QString())
{
}

Assessment * Assessment_P::p_dptr() const
{
    return qobject_cast<Assessment *>( parent() );
}
