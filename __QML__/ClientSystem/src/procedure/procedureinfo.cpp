#include "procedureinfo.h"


ProcedureInfo::ProcedureInfo() :
    m__Identifier(QVariant()),
    m__Name(QString())
{
}

ProcedureInfo::ProcedureInfo( const ProcedureInfo &other ) :
    m__Identifier(other.identifier()),
    m__Name(other.name())
{
}

ProcedureInfo::~ProcedureInfo()
{
}

QVariant ProcedureInfo::identifier() const
{
    return m__Identifier;
}

void ProcedureInfo::setIdentifier( QVariant identifier )
{
    m__Identifier = identifier;
}

const QString & ProcedureInfo::name() const
{
    return m__Name;
}

void ProcedureInfo::setName( const QString &name )
{
    m__Name = name;
}
