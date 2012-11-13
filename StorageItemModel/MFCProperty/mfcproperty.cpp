#include "mfcproperty.h"
#include <QDebug>

MFCProperty::MFCProperty( QString p_Name, QVariant p_Value )
{
  if ( p_Name.isNull() || p_Name.isEmpty() )
    m_Name = new QString();
  m_Name = new QString( p_Name );
  m_Value = new QVariant();
  setValue( p_Value );
}

MFCProperty::~MFCProperty()
{
//  qDebug() <<*m_Name << *m_Value;
  delete m_Name;
  delete m_Value;
//  qDebug() <<"~/*MFCProperty*/()";
}

bool MFCProperty::isNull() const
{
  return !m_Name->isEmpty();
}

void MFCProperty::setValue( QVariant p_Value )
{
  m_Value->clear();
  m_Value->setValue( p_Value );
}

const QString & MFCProperty::name() const
{
  return *m_Name;
}

const QVariant & MFCProperty::value() const
{
  return *m_Value;
}
