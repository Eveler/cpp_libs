#include "properties.h"
#include <QDebug>

QHash<QString, Properties *> Properties::m_Properties = QHash<QString, Properties *>();
Properties Properties::nullProperty;

Properties * Properties::addProperties( const QString &ps_Name )
{
  if ( ps_Name.isEmpty() )
  {
    qDebug() <<QObject::tr( "Properties name is empty!" );
    return &nullProperty;
  }
  if ( !m_Properties.contains( ps_Name ) )
  {
    m_Properties.insert( ps_Name, new Properties( ps_Name ) );
//    qDebug() <<QObject::tr( "Properties: '" )+ps_Name+
//                   QObject::tr( "' has been added." );
  }
//  else qDebug() <<QObject::tr( "Properties: '" )+ps_Name+
//               QObject::tr( "' already exists! Nothing to add." );

  return m_Properties.value( ps_Name );
}

Properties * Properties::getProperties( const QString &ps_Name )
{
  if ( ps_Name.isEmpty() || !m_Properties.contains( ps_Name ) )
    return &nullProperty;

  return m_Properties.value( ps_Name );
}

bool Properties::exists( const QString &ps_Name )
{
  return m_Properties.contains( ps_Name );
}

bool Properties::release( const QString &ps_Name )
{
  if ( ps_Name.isEmpty() || !m_Properties.contains( ps_Name ) ) return false;

  Properties *p = m_Properties.take( ps_Name );
  delete p;

  return true;
}

void Properties::releaseAll()
{
  foreach ( QString ps_Name, m_Properties.keys() )
  {
    Properties *p = m_Properties.take( ps_Name );
    delete p;
  }
}

bool Properties::isNull()
{
  return m_Name->isEmpty();
}

const QString & Properties::name() const
{
  return *m_Name;
}

QByteArray Properties::hash()
{
  QByteArray data = QByteArray();

  QStringList ps = QStringList();

  foreach ( QString p_Name, propertyNames() )
    ps << ( p_Name+":"+QVariant::typeToName( propertyType( p_Name ) ) );

  return data.append( ps.join( ";" ) );
}

bool Properties::addProperty( const QString &p_Name, QVariant::Type p_Type )
{
  if ( isNull() || p_Name.isEmpty() || p_Type == QVariant::Invalid )
    return false;
  foreach ( QString *propertyName, m_PropertyNames )
    if ( *propertyName == p_Name ) return false;

  m_PropertyNames << new QString( p_Name );
  m_PropertyTypes.insert( m_PropertyNames.last(), p_Type );

  return true;
}

bool Properties::removeProperty( const QString &p_Name )
{
  foreach ( QString *propertyName, m_PropertyNames )
    if ( *propertyName == p_Name )
    {
      m_PropertyNames.removeOne( propertyName );
      m_PropertyTypes.remove( propertyName );
      delete propertyName;
    }

  return false;
}

void Properties::clear()
{
  foreach ( QString p_Name, propertyNames() ) removeProperty( p_Name );
}

bool Properties::addPrimaryKey(const QString &p_Name, QVariant::Type p_Type){
  if ( isNull() || p_Name.isEmpty() || p_Type == QVariant::Invalid )
    return false;
  if(!addProperty(p_Name,p_Type))
    if(p_Type!=propertyType(p_Name)) return false;
  foreach(QString *str,m_PrimaryKey)
    if(str==p_Name) return false;
  m_PrimaryKey<<new QString(p_Name);
  return true;
}

QStringList Properties::primaryKey(){
  QStringList result=QStringList();
  foreach(QString *p_Name,m_PrimaryKey) result<<*p_Name;
  return result;
}

QStringList Properties::propertyNames()
{
  QStringList result = QStringList();

  foreach ( QString *p_Name, m_PropertyNames )
    result << *p_Name;

  return result;
}

QVariant::Type Properties::propertyType( const QString &p_Name ) const
{
  foreach ( QString *propertyName, m_PropertyNames )
    if ( *propertyName == p_Name )
      return m_PropertyTypes.value( propertyName );

  return QVariant::Invalid;
}

bool Properties::addChildProperties( Properties *properties )
{
  if ( properties == 0 || m_ParentProperties.contains( properties ) ||
       m_ChildrenProperties.contains( properties ) ) return false;
  m_ChildrenProperties << properties;
  properties->addParentProperties( this );
  return true;
}

bool Properties::removeChildProperies( Properties *properties )
{
  if ( properties == 0 || !m_ChildrenProperties.contains( properties ) ) return false;
  m_ChildrenProperties.removeOne( properties );
  properties->removeParentProperies( this );
  return true;
}

QList<Properties *> Properties::childrenProperties() const
{
  return m_ChildrenProperties;
}

bool Properties::addParentProperties( Properties *properties )
{
  if ( properties == 0 || m_ParentProperties.contains( properties ) ||
       m_ChildrenProperties.contains( properties ) ) return false;
  m_ParentProperties << properties;
  properties->addChildProperties( this );
  return true;
}

bool Properties::removeParentProperies( Properties *properties )
{
  if ( properties == 0 || !m_ParentProperties.contains( properties ) ) return false;
  m_ParentProperties.removeOne( properties );
  properties->removeChildProperies( this );
  return true;
}

QList<Properties *> Properties::parentProperties() const
{
  return m_ParentProperties;
}

Properties::Properties()
{
  m_Name = new QString();
  m_PropertyNames = QList<QString *>();
  m_PropertyTypes = QHash<QString *, QVariant::Type>();
}

Properties::Properties( const QString &ps_Name )
{
  m_Name = new QString( ps_Name );
  m_ParentProperties = QList<Properties *>();
  m_ChildrenProperties = QList<Properties *>();
  m_PropertyNames = QList<QString *>();
  m_PropertyTypes = QHash<QString *, QVariant::Type>();
}

Properties::~Properties()
{
  QString ps_Name = *m_Name;
  delete m_Name;
  m_PropertyTypes.clear();
  foreach ( QString *propertyName, m_PropertyNames )
  {
    m_PropertyNames.removeOne( propertyName );
    delete propertyName;
  }
  foreach(QString *primaryKey,m_PrimaryKey){
    m_PrimaryKey.removeOne(primaryKey);
    delete primaryKey;
  }
//  if ( !ps_Name.isEmpty() )
//    qDebug() <<QObject::tr( "Properties: '" )+ps_Name+
//            QObject::tr( "' has been removed." );
}
