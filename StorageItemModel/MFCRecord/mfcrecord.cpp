#include "mfcrecord.h"
#include <QDebug>

#include <QBitArray>
#include <QBitmap>
#include <QEasingCurve>
#include <QMatrix4x4>
#include <QPen>
#include <QTextFormat>
#include <QTextLength>
#include <QUrl>
#include <QVector2D>
#include <QDateTime>
#include <QCursor>
#include <QIcon>
#include <QKeySequence>
#include <QPalette>
#include <QSizePolicy>

QList<QVariant::Type> MFCRecord::integerTypes =
    QList<QVariant::Type>() << QVariant::Int << QVariant::UInt <<
                               QVariant::Double << QVariant::LongLong << QVariant::ULongLong;


QString MFCRecord::unionValues( const QStringList &keyWords, MFCRecord *record )
{
  QString values = QString();

  if ( record != 0 )
    foreach ( QString keyWord, keyWords )
      if ( record->properties()->propertyNames().contains( keyWord ) )
      {
        QString value = QString();
        if ( record->properties()->propertyType( keyWord ) == QVariant::DateTime )
          value = record->currentProperty( keyWord ).toDateTime().toString( tr( "dd.MM.yyyy hh:mm:ss" ) );
        else if ( record->properties()->propertyType( keyWord ) == QVariant::Date )
          value = record->currentProperty( keyWord ).toDate().toString( tr( "dd.MM.yyyy" ) );
        else if ( record->properties()->propertyType( keyWord ) == QVariant::Time )
          value = record->currentProperty( keyWord ).toTime().toString( tr( "hh:mm:ss" ) );
        else
          value = record->currentProperty( keyWord ).toString();

        values += ( !values.isEmpty() ? " " : "" )+value;
      }

  return values;
}

QString MFCRecord::unionValuesShortDate( const QStringList &keyWords, MFCRecord *record )
{
  QString values = QString();

  if ( record != 0 )
    foreach ( QString keyWord, keyWords )
      if ( record->properties()->propertyNames().contains( keyWord ) )
      {
        QString value = QString();
        if ( record->properties()->propertyType( keyWord ) == QVariant::DateTime )
          value = record->currentProperty( keyWord ).toDateTime().toString( tr( "dd.MM.yyyy" ) );
        else if ( record->properties()->propertyType( keyWord ) == QVariant::Date )
          value = record->currentProperty( keyWord ).toDate().toString( tr( "dd.MM.yyyy" ) );
        else if ( record->properties()->propertyType( keyWord ) == QVariant::Time )
          value = QString( "" );
        else
          value = record->currentProperty( keyWord ).toString();

        values += ( !values.isEmpty() ? " " : "" )+value;
      }

  return values;
}

MFCRecord::MFCRecord( PropertiesLink *pLink )
{
  m_Uuid = QUuid::createUuid();

  m_PropertiesLink = 0;
  m_Parents = QList<MFCRecord *>();
  m_Children = QList<MFCRecord *>();
  m_PropertiesView = PropertiesView::getPropertiesView( pLink->propertiesViewAlias() );
  m_Properties = m_PropertiesView->root();

  m_NULL = QVariant();

  blockPropertyChanged = false;
  blockOnChangeChild = false;

  bool isValid = true;

  if ( m_PropertiesView->isNull() )
  {
    qDebug() <<QObject::tr( "PropertiesView: '" )+pLink->propertiesViewAlias()+
            QObject::tr( "' is not available!" );
    isValid = false;
  }
  if ( isValid )
  {
    m_PropertiesLink = pLink;
    QStringList pNames = m_PropertiesView->root()->propertyNames();
    foreach( QString pName, pNames )
    {
      QVariant val = m_NULL;
      switch ( m_PropertiesView->root()->propertyType( pName ) )
      {
      case QVariant::BitArray:
        val = QBitArray();
        break;
      case QVariant::Bitmap:
        val = QBitmap();
        break;
      case QVariant::Bool:
        val = false;
        break;
      case QVariant::Brush:
        val = QBrush();
        break;
      case QVariant::ByteArray:
        val = QByteArray();
        break;
      case QVariant::Char:
        val = QChar();
        break;
      case QVariant::Color:
        val = QColor();
        break;
      case QVariant::Cursor:
        val = QCursor();
        break;
      case QVariant::Date:
        val = QDate();
        break;
      case QVariant::DateTime:
        val = QDateTime();
        break;
      case QVariant::Double:
        val = QVariant();
        break;
      case QVariant::EasingCurve:
        val = QEasingCurve();
        break;
      case QVariant::Font:
        val = QFont();
        break;
      case QVariant::Hash:
        val = QVariantHash();
        break;
      case QVariant::Icon:
        val = QIcon();
        break;
      case QVariant::Image:
        val = QImage();
        break;
      case QVariant::Int:
        val = QVariant();
        break;
      case QVariant::KeySequence:
        val = QKeySequence();
        break;
      case QVariant::Line:
        val = QLine();
        break;
      case QVariant::LineF:
        val = QLineF();
        break;
      case QVariant::List:
        val = QVariantList();
        break;
      case QVariant::Locale:
        val = QLocale();
        break;
      case QVariant::LongLong:
        val = QVariant();
        break;
      case QVariant::Map:
        val = QVariantMap();
        break;
      case QVariant::Matrix:
        val = QMatrix();
        break;
      case QVariant::Transform:
        val = QTransform();
        break;
      case QVariant::Matrix4x4:
        val = QMatrix4x4();
        break;
      case QVariant::Palette:
        val = QPalette();
        break;
      case QVariant::Pen:
        val = QPen();
        break;
      case QVariant::Pixmap:
        val = QPixmap();
        break;
      case QVariant::Point:
        val = QPoint();
        break;
      case QVariant::PointF:
        val = QPointF();
        break;
      case QVariant::Polygon:
        val = QPolygon();
        break;
      case QVariant::Quaternion:
        val = QQuaternion();
        break;
      case QVariant::Rect:
        val = QRect();
        break;
      case QVariant::RectF:
        val = QRectF();
        break;
      case QVariant::RegExp:
        val = QRegExp();
        break;
      case QVariant::Region:
        val = QRegion();
        break;
      case QVariant::Size:
        val = QSize();
        break;
      case QVariant::SizeF:
        val = QSizeF();
        break;
      case QVariant::SizePolicy:
        val = QSizePolicy();
        break;
      case QVariant::String:
        val = QString();
        break;
      case QVariant::StringList:
        val = QStringList();
        break;
      case QVariant::TextFormat:
        val = QTextFormat();
        break;
      case QVariant::TextLength:
        val = QTextLength();
        break;
      case QVariant::Time:
        val = QTime();
        break;
      case QVariant::UInt:
        val = QVariant();
        break;
      case QVariant::ULongLong:
        val = QVariant();
        break;
      case QVariant::Url:
        val = QUrl();
        break;
      case QVariant::Vector2D:
        val = QVector2D();
        break;
      case QVariant::Vector3D:
        val = QVector3D();
        break;
      case QVariant::Vector4D:
        val = QVector4D();
        break;
      default:
        break;
      }

      m_DefaultProperties << new MFCProperty( pName, val );
      m_CurrentProperties << new MFCProperty( pName, val );
    }
  }
}

MFCRecord::~MFCRecord()
{
  emit recordDestroyed( m_Uuid );
  foreach ( MFCProperty *p, m_DefaultProperties ) delete p;
  foreach ( MFCProperty *p, m_CurrentProperties ) delete p;
  m_Parents.clear();
  m_Children.clear();
}

//bool MFCRecord::addParentRecord( MFCRecord *parent )
//{
//  if ( parent == 0 || parent->propertiesLink()->links( m_Properties ).count() == 0 ) return false;

//  if ( !m_Parents.contains( parent ) )
//    m_Parents << parent;
//  if ( !parent->childrenRecord().contains( this ) )
//    parent->addChildRecord( this );

//  return true;
//}

bool MFCRecord::addParentRecord( MFCRecord *parent )
{
  if ( parent == 0 || parent->propertiesLink()->links(
         m_PropertiesLink->propertiesViewAlias() ).count() == 0 ||
       !parent->childrenRecord().contains( this ) || m_Parents.contains( parent ) )
    return false;

  m_Parents << parent;
  connect( parent, SIGNAL(destroyed(QObject*)), this, SLOT(parentDestroyed(QObject*)) );

  return true;
}

bool MFCRecord::removeParentRecord( MFCRecord *parent )
{
  if ( parent == 0 || !m_Parents.contains( parent ) ||
       parent->childrenRecord().contains( this ) ) return false;

  m_Parents.removeOne( parent );
  disconnect( parent, SIGNAL(destroyed(QObject*)), this, SLOT(parentDestroyed(QObject*)) );

  return true;
}

const QList<MFCRecord *> & MFCRecord::parentRecords() const
{
  return m_Parents;
}

bool MFCRecord::addChildRecord( MFCRecord *child )
{
  if ( child == 0 ) return false;

//  bool hasLink = false;
//  foreach( MFCRecord *childRecord, m_Children )
//    if ( childRecord->propertiesLink() == child->propertiesLink() )
//    {
//      hasLink = true;
//      break;
//    }
//  if ( !hasLink )
//  {
    if ( propertiesLink()->links(
           child->propertiesLink()->propertiesViewAlias() ).count() == 0 ) return false;

    if ( !child->parentRecords().contains( this ) )
    {
      m_Children << child;
      child->addParentRecord( this );
      connect( child, SIGNAL(destroyed(QObject*)), this, SLOT(childDestroyed(QObject*)) );
      if ( !blockOnChangeChild ) emit childAdded( child );
    }
//  }

  return true;
}

bool MFCRecord::replaceChildRecord( MFCRecord *old_child, MFCRecord *new_child )
{
  blockOnChangeChild = true;
  if ( !removeChildRecord( old_child ) )
  {
    blockOnChangeChild = false;
    return false;
  }
  if ( !addChildRecord( new_child ) )
  {
    addChildRecord( old_child );
    blockOnChangeChild = false;
    return false;
  }
  blockOnChangeChild = false;
  emit childReplaced( old_child, new_child );
  return true;
}

//bool MFCRecord::removeChildRecord( MFCRecord *child )
//{
//  if ( child == 0 || !m_Children.contains( child ) ) return false;

//  if ( child->parentRecords().contains( this ) )
//  {
//    m_Children.removeOne( child );
//    child->removeParentRecord( this );
//    if ( !blockOnChangeChild ) emit childRemoved( child );
//  }
//  else
//  {
//    m_Children.removeOne( child );
//    if ( !blockOnChangeChild ) emit childRemoved( child );
//  }

//  return true;
//}

bool MFCRecord::removeChildRecord( MFCRecord *child )
{
  if ( child == 0 || !m_Children.contains( child ) ||
       !child->parentRecords().contains( this ) ) return false;

  m_Children.removeOne( child );
  child->removeParentRecord( this );
  disconnect( child, SIGNAL(destroyed(QObject*)), this, SLOT(childDestroyed(QObject*)) );
  if ( !blockOnChangeChild ) emit childRemoved( child );

  return true;
}

const QList<MFCRecord *> & MFCRecord::childrenRecord() const
{
  return m_Children;
}

PropertiesLink *MFCRecord::propertiesLink() const
{
  return m_PropertiesLink;
}

PropertiesView *MFCRecord::propertiesView() const
{
  return m_PropertiesView;
}

Properties * MFCRecord::properties() const
{
  return m_Properties;
}

bool MFCRecord::setDefaultProperty( const QString &p_Name, QVariant p_Value )
{
  return setProperty( m_DefaultProperties, p_Name, p_Value );
}

bool MFCRecord::setProperty( const QString &p_Name, QVariant p_Value )
{
  qDebug() <<sender();
  if ( !setDefaultProperty( p_Name, p_Value ) ) return false;
  return setCurrentProperty( p_Name, p_Value );
}

const QVariant & MFCRecord::defaultProperty( const QString &p_Name ) const
{
  return property( m_DefaultProperties, p_Name );
}

const QVariant & MFCRecord::currentProperty( const QString &p_Name ) const
{
  return property( m_CurrentProperties, p_Name );
}

QStringList MFCRecord::changedProperties()
{
  QStringList properties = QStringList();
  foreach( MFCProperty *property, m_DefaultProperties )
    if ( defaultProperty( property->name() ) != currentProperty( property->name() ) )
      properties << property->name();

  return properties;
}

//MFCRecord * MFCRecord::findChildByName( const QString &name )
//{
//  foreach ( MFCRecord *record, m_Children )
//    if ( record->properties()->name() == name ) return record;

//  return 0;
//}

MFCRecord * MFCRecord::findChildByName( const QString &propertiesView_Alias ) const
{
  foreach ( MFCRecord *record, m_Children )
    if ( record->propertiesLink()->propertiesViewAlias() == propertiesView_Alias ) return record;

  return 0;
}

//bool MFCRecord::setDefaultValue( Properties *properties, const QString &p_Name, QVariant p_Value )
//{
//  MFCRecord *record = getRecordByProperty( properties );

//  bool res = ( record != 0 );
//  if ( !res ) return res;
//  res = ( properties != 0 && properties->propertyNames().contains( p_Name ) &&
//      properties->propertyType( p_Name ) == p_Value.type() );
//  if ( !res ) return res;

//  res = record->setDefaultProperty( p_Name, p_Value );
//  if ( !res ) qDebug() <<tr( "Õìì... Îøèáêà â setDefaultProperty." );

//  return res;
//}

//bool MFCRecord::setCurrentValue( Properties *properties, const QString &p_Name, QVariant p_Value )
//{
//  MFCRecord *record = getRecordByProperty( properties );

//  bool res = ( record != 0 );
//  if ( !res ) return res;
//  res = ( properties != 0 && properties->propertyNames().contains( p_Name ) &&
//      properties->propertyType( p_Name ) == p_Value.type() );
//  if ( !res ) return res;

//  res = record->setCurrentProperty( p_Name, p_Value );
//  if ( !res ) qDebug() <<tr( "Õìì... Îøèáêà â setCurrentProperty." );

//  return res;
//}

//QVariant MFCRecord::getDefaultValue( Properties *properties, const QString &p_Name )
//{
//  MFCRecord *record = getRecordByProperty( properties );

//  bool res = ( record != 0 );
//  if ( !res ) return m_NULL;
//  res = ( properties != 0 && properties->propertyNames().contains( p_Name ) );
//  if ( !res ) return m_NULL;

//  return record->defaultProperty( p_Name );
//}

//QVariant MFCRecord::getCurrentValue( Properties *properties, const QString &p_Name )
//{
//  MFCRecord *record = getRecordByProperty( properties );

//  bool res = ( record != 0 );
//  if ( !res ) return QVariant();
//  res = ( properties != 0 && properties->propertyNames().contains( p_Name ) );
//  if ( !res ) return QVariant();

//  return record->currentProperty( p_Name );
//}

bool MFCRecord::setDefaultValue( PropertiesView *pv, const QString &p_Name, QVariant p_Value )
{
  MFCRecord *record = getRecordByPropertiesView( pv );

  bool res = ( record != 0 );
  if ( !res ) return res;
  res = ( pv->root()->propertyNames().contains( p_Name ) &&
          ( pv->root()->propertyType( p_Name ) == p_Value.type() ||
            ( !p_Value.isValid() &&
              ( pv->root()->propertyType( p_Name ) == QVariant::Int ||
                pv->root()->propertyType( p_Name ) == QVariant::UInt ||
                pv->root()->propertyType( p_Name ) == QVariant::Double ||
                pv->root()->propertyType( p_Name ) == QVariant::LongLong ||
                pv->root()->propertyType( p_Name ) == QVariant::ULongLong ) ) ) );
  if ( !res ) return res;

  res = record->setDefaultProperty( p_Name, p_Value );
  if ( !res ) qDebug() <<tr( "Õìì... Îøèáêà â setDefaultProperty." );

  return res;
}

bool MFCRecord::setCurrentValue( PropertiesView *pv, const QString &p_Name, QVariant p_Value )
{
  MFCRecord *record = getRecordByPropertiesView( pv );

  bool res = ( record != 0 );
  if ( !res ) return res;
  res = ( pv->root()->propertyNames().contains( p_Name ) &&
          ( pv->root()->propertyType( p_Name ) == p_Value.type() ||
            ( !p_Value.isValid() &&
              ( pv->root()->propertyType( p_Name ) == QVariant::Int ||
                pv->root()->propertyType( p_Name ) == QVariant::UInt ||
                pv->root()->propertyType( p_Name ) == QVariant::Double ||
                pv->root()->propertyType( p_Name ) == QVariant::LongLong ||
                pv->root()->propertyType( p_Name ) == QVariant::ULongLong ) ) ) );
  if ( !res ) return res;

  res = record->setCurrentProperty( p_Name, p_Value );
  if ( !res ) qDebug() <<tr( "Õìì... Îøèáêà â setCurrentProperty." );

  return res;
}

QVariant MFCRecord::getDefaultValue( PropertiesView *pv, const QString &p_Name )
{
  MFCRecord *record = getRecordByPropertiesView( pv );

  bool res = ( record != 0 );
  if ( !res ) return m_NULL;
  res = ( pv->root()->propertyNames().contains( p_Name ) );
  if ( !res ) return m_NULL;

  return record->defaultProperty( p_Name );
}

QVariant MFCRecord::getCurrentValue( PropertiesView *pv, const QString &p_Name )
{
  MFCRecord *record = getRecordByPropertiesView( pv );

  bool res = ( record != 0 );
  if ( !res ) return QVariant();
  res = ( pv->root()->propertyNames().contains( p_Name ) );
  if ( !res ) return QVariant();

  return record->currentProperty( p_Name );
}

//MFCRecord * MFCRecord::getRecordByProperty( Properties *properties )
//{
//  bool res = false;
//  foreach ( PropertiesLink *pLink, m_PropertiesView->availableLinks() )
//    if ( pLink->parent() == properties ) res = true;
//  if ( !res ) return 0;

//  return recordByProperty( this, properties );
//}

MFCRecord * MFCRecord::getRecordByPropertiesView( PropertiesView *pv_Child,
                                                  PropertiesView *pv_Parent,
                                                  QString keyField )
{
  if ( pv_Child != 0 && !pv_Child->isNull() )
  {
    if ( pv_Parent == this->propertiesView() &&
         propertiesLink()->hasLinkOption( keyField, pv_Child->alias() ) )
    {
      foreach ( MFCRecord *child, m_Children )
        if ( this->keyFieldForChild( child ).contains( keyField ) )
          return child;
    }
    else if ( ( pv_Parent == 0 || pv_Parent->isNull() ) &&
         pv_Child == m_PropertiesView )
      return this;
    else
      foreach ( MFCRecord *child, m_Children )
      {
        MFCRecord *resRecord = child->getRecordByPropertiesView( pv_Child, pv_Parent, keyField );
        if ( resRecord != 0 ) return resRecord;
      }
  }

  return 0;
}

QList<MFCRecord *> MFCRecord::getRootRecords( PropertiesView *pv )
{
  QList<MFCRecord *> rootRecords = QList<MFCRecord *> ();

  if ( m_PropertiesView == pv ) rootRecords << this;
  foreach ( MFCRecord *parentRecord, m_Parents )
    rootRecords << parentRecord->getRootRecords( pv );

  return rootRecords;
}

//MFCRecord * MFCRecord::findRecord( Properties *properties, const QString &p_Name, QVariant p_Value )
//{
//  if ( this->properties() == properties )
//  {
//    if ( currentProperty( p_Name ) == p_Value ) return this;
//  }
//  else
//    foreach ( MFCRecord *childRecord, this->childrenRecord() )
//    {
//      MFCRecord *result = childRecord->findRecord( properties, p_Name, p_Value );
//      if ( result != 0 ) return result;
//    }

//  return 0;
//}

MFCRecord * MFCRecord::findRecord( PropertiesView *pv, const QString &p_Name, QVariant p_Value )
{
  if ( m_PropertiesView == pv )
  {
    if ( currentProperty( p_Name ) == p_Value ) return this;
  }
  else
    foreach ( MFCRecord *childRecord, this->childrenRecord() )
    {
      MFCRecord *result = childRecord->findRecord( pv, p_Name, p_Value );
      if ( result != 0 ) return result;
    }

  return 0;
}

MFCRecord * MFCRecord::copy( PropertiesLink *pLink )
{
  if ( PropertiesView::getPropertiesView(
         pLink->propertiesViewAlias() )->root()->parent() != properties() ) return 0;

  MFCRecord *record = new MFCRecord( pLink );
  foreach ( QString p_Name, properties()->propertyNames() )
  {
    record->setDefaultProperty( p_Name, defaultProperty( p_Name ) );
    record->setCurrentProperty( p_Name, currentProperty( p_Name ) );
  }

  return record;
}

bool MFCRecord::copy( MFCRecord *other )
{
  if ( other == 0 || other->properties() != properties() ) return 0;

  foreach ( QString p_Name, properties()->propertyNames() )
  {
    other->setDefaultProperty( p_Name, defaultProperty( p_Name ) );
    other->setCurrentProperty( p_Name, currentProperty( p_Name ) );
  }

  return true;
}

void MFCRecord::dataRecovery()
{
  foreach ( QString p_Name, properties()->propertyNames() )
    setCurrentProperty( p_Name, defaultProperty( p_Name ) );

  emit dataReversed();
}

void MFCRecord::dataSync()
{
  foreach ( QString p_Name, properties()->propertyNames() )
    setDefaultProperty( p_Name, currentProperty( p_Name ) );

  emit dataReversed();
}

const QUuid & MFCRecord::uuid() const
{
  return m_Uuid;
}

bool MFCRecord::operator ==( const MFCRecord &other ) const
{
  if ( properties() != other.properties() ) return false;

  bool same = true;
  if ( properties()->primaryKey().count() == 0 )
    same = isSame( other, properties()->propertyNames() );
  else
    same = isSame( other, properties()->primaryKey() );

  return same;
}

bool MFCRecord::isSame( const MFCRecord &other, const QStringList &propertyNames ) const
{
  if ( properties() != other.properties() ) return false;

  bool same = true;
  foreach ( QString p_Name, propertyNames )
    if ( currentProperty( p_Name ) != other.currentProperty( p_Name ) )
    {
      same = false;
      break;
    }

  return same;
}

void MFCRecord::requestEdit()
{
  emit editRequested();
}

QStringList MFCRecord::keyFieldForChild(MFCRecord *child) const{
  QStringList result=QStringList();
  if(!m_Children.contains(child)) return result;
  QList< QPair< QString,LinkOptions* > > fLinks=
      m_PropertiesLink->links(child->propertiesView()->alias());
  for(int lIdx=0;lIdx<fLinks.count();lIdx++){
    if(currentProperty(fLinks[lIdx].first)==
       child->currentProperty(fLinks[lIdx].second->propertyName()))
      result<<fLinks[lIdx].first;
  }
  return result;
}

bool MFCRecord::setCurrentProperty( const QString &p_Name, QVariant p_Value )
{
  QVariant oldValue = currentProperty( p_Name );
  if ( oldValue == p_Value ) return true;
//  if ( p_Name == "human_id" )
//    qDebug() <<"TYT";
  if ( setProperty( m_CurrentProperties, p_Name, p_Value ) )
  {
//    if ( p_Name == "human_id" )
//      qDebug() <<"TYT";
    emit propertyChanged( p_Name, oldValue, p_Value );
//    if ( p_Name == "human_id" )
//      qDebug() <<"TYT";
    emit propertyChanged( p_Name, p_Value );
//    if ( p_Name == "human_id" )
//      qDebug() <<"TYT";
    emit propertyChanged( p_Name );
//    if ( p_Name == "human_id" )
//      qDebug() <<"TYT";
    return true;
  }
  return false;
}

void MFCRecord::setParent( QObject *obj )
{
  QObject::setParent( obj );
}

QObject * MFCRecord::parent()
{
  return QObject::parent();
}

QList<QObject *> MFCRecord::children()
{
  return QObject::children();
}

bool MFCRecord::setProperty( QList<MFCProperty *> & m_MFCProperties,
                             const QString &p_Name, QVariant p_Value )
{
  if ( m_Properties->isNull() ||
       !m_Properties->propertyNames().contains( p_Name ) )
  {
    if ( integerTypes.contains( m_Properties->propertyType( p_Name ) ) )
    {
      if ( !integerTypes.contains( p_Value.type() ) && p_Value.isValid()  )
      {
        qDebug() <<"setProperty first check fail";
        return false;
      }
    }
    else if ( /*m_Properties->propertyType( p_Name ) != p_Value.type()*/
              !( m_Properties->propertyType( p_Name ) == p_Value.type() ||
                 ( !p_Value.isValid() &&
                   ( m_Properties->propertyType( p_Name ) == QVariant::Int ||
                     m_Properties->propertyType( p_Name ) == QVariant::UInt ||
                     m_Properties->propertyType( p_Name ) == QVariant::Double ||
                     m_Properties->propertyType( p_Name ) == QVariant::LongLong ||
                     m_Properties->propertyType( p_Name ) == QVariant::ULongLong ) ) ))
    {
      qDebug() <<"setProperty second check fail";
      return false;
    }
  }
  foreach( MFCProperty *property, m_MFCProperties )
  {
    if ( property->name() == p_Name )
    {
      property->setValue( p_Value );
      return true;
    }
  }
  return false;
}

const QVariant & MFCRecord::property( const QList<MFCProperty *> & m_MFCProperties, const QString &p_Name ) const
{
  foreach( MFCProperty *property, m_MFCProperties )
    if ( property->name() == p_Name )
      return property->value();
  return m_NULL;
}

//MFCRecord * MFCRecord::recordByProperty( MFCRecord *record, Properties *properties )
//{
//  if ( record->properties() == properties ) return record;
//  else
//    foreach ( MFCRecord *child, record->childrenRecord() )
//    {
//      MFCRecord *result = recordByProperty( child, properties );
//      if ( result != 0 ) return result;
//    }

//  return 0;
//}

void MFCRecord::parentDestroyed( QObject *obj )
{
  MFCRecord *parentRecord = (MFCRecord *)obj;
  m_Parents.removeOne( parentRecord );
}

void MFCRecord::childDestroyed( QObject *obj )
{
  MFCRecord *childRecord = (MFCRecord *)obj;
  m_Children.removeOne( childRecord );
}
