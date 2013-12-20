#include "procedureinfo.h"


ProcedureInfo::ProcedureInfo() :
  QObject(NULL),
  m__Identifier(QVariant()),
  m__Name(QString())
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
