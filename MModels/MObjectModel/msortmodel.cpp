#include "msortmodel.h"

#include "mobjectmodel.h"

#include <QHash>
#include <QDateTime>


MSortModel::MSortModel( QObject *parent ) :
  QSortFilterProxyModel(parent),
  m__SortProperties(new MSortProperties)
{
}

MSortModel::~MSortModel()
{
  delete m__SortProperties;
  m__SortProperties = NULL;
}

MObjectModel * MSortModel::sourceModel() const
{
  QAbstractItemModel *sourceModel = QSortFilterProxyModel::sourceModel();
  if ( sourceModel == NULL ) return NULL;
  return qobject_cast<MObjectModel *>( sourceModel );
}

void MSortModel::setSourceModel( MObjectModel * sourceModel )
{
  QSortFilterProxyModel::setSourceModel( sourceModel );

  emit sourceModelChanged();
}

MSortProperties * MSortModel::sortProperties() const
{
  return m__SortProperties;
}

void MSortModel::sort()
{
  QSortFilterProxyModel::sort( 0 );
}

bool MSortModel::lessThan( const QModelIndex &left, const QModelIndex &right ) const
{
//  qDebug() << left << right;
  if ( !left.isValid() || !right.isValid() || left.model()->roleNames().isEmpty() || right.model()->roleNames().isEmpty() ) return false;

  int leftRoleIndex = left.model()->roleNames().keys().first();
  int rightRoleIndex = right.model()->roleNames().keys().first();

//  qDebug() << __func__;
  if ( !left.data( leftRoleIndex ).canConvert<QObject *>() || !right.data( rightRoleIndex ).canConvert<QObject *>() ) return false;
  QObject *leftObject = left.data( leftRoleIndex ).value<QObject *>();
  QObject *rightObject = right.data( rightRoleIndex ).value<QObject *>();

  bool result = lessThan( leftObject, rightObject, m__SortProperties );
  if ( right.row() % 1000 == 0 ) qApp->processEvents();
//  qDebug() << __func__ << result;
  return result;
}

bool MSortModel::lessThan( QObject *left, QObject *right, MSortProperties *sortProperties ) const
{
  bool result = false;

  for ( int index = 0; index < sortProperties->count(); index++ )
  {
    int res = 0;

    QString sortProperty = sortProperties->sortProperty( index );
    QVariant sortOrder = sortProperties->sortOrder( index )->value();
    if ( sortOrder.type() == (int)QMetaType::QObjectStar )
    {
      MSortProperties *sort = sortOrder.value<MSortProperties *>();
      QObject *leftObject = left->property( sortProperty.toLocal8Bit() ).value<QObject *>();
      QObject *rightObject = right->property( sortProperty.toLocal8Bit() ).value<QObject *>();
      result = lessThan( leftObject, rightObject, sort );
    }
    else
    {
//      qDebug() << sortOrder.toInt();
      if ( sortOrder.toInt() == (int)Qt::AscendingOrder )
//        result = ( left->property( sortProperty.toLocal8Bit() ) < right->property( sortProperty.toLocal8Bit() ) );
        res = compare( left->property( sortProperty.toLocal8Bit() ), right->property( sortProperty.toLocal8Bit() ) );
      else
//        result = ( left->property( sortProperty.toLocal8Bit() ) > right->property( sortProperty.toLocal8Bit() ) );
        res = compare( right->property( sortProperty.toLocal8Bit() ), left->property( sortProperty.toLocal8Bit() ) );

//      qDebug() << res << left->property( sortProperty.toLocal8Bit() ) << right->property( sortProperty.toLocal8Bit() );
    }

    result = ( res < 0 );

    if ( result || res > 0 ) break;
  }

  return result;
}

int MSortModel::compare( const QVariant &left, const QVariant &right ) const
{
  int result = ( left < right ? -1 : ( left > right ? 1 : 0 ) );
//  int result = 0;

//  switch ( left.type() ) {
//    case QVariant::Int:
//      result = ( left.toInt() < right.toInt() ? -1 : ( left.toInt() > right.toInt() ? 1 : 0 ) );
//      break;
//    case QVariant::UInt:
//      result = ( left.toInt() < right.toUInt() ? -1 : ( left.toUInt() > right.toUInt() ? 1 : 0 ) );
//      break;
//    case QVariant::LongLong:
//      result = ( left.toLongLong() < right.toLongLong() ? -1 : ( left.toLongLong() > right.toLongLong() ? 1 : 0 ) );
//      break;
//    case QVariant::ULongLong:
//      result = ( left.toULongLong() < right.toULongLong() ? -1 : ( left.toULongLong() > right.toULongLong() ? 1 : 0 ) );
//      break;
//    case QVariant::Double:
//      result = ( left.toDouble() < right.toDouble() ? -1 : ( left.toDouble() > right.toDouble() ? 1 : 0 ) );
//      break;
//    case QVariant::Char:
//      result = ( left.toChar() < right.toChar() ? -1 : ( left.toChar() > right.toChar() ? 1 : 0 ) );
//      break;
//    case QVariant::DateTime:
//      result = ( left.toDateTime() < right.toDateTime() ? -1 : ( left.toDateTime() > right.toDateTime() ? 1 : 0 ) );
//      break;
//    case QVariant::Date:
//      result = ( left.toDate() < right.toDate() ? -1 : ( left.toDate() > right.toDate() ? 1 : 0 ) );
//      break;
//    case QVariant::Time:
//      result = ( left.toTime() < right.toTime() ? -1 : ( left.toTime() > right.toTime() ? 1 : 0 ) );
//      break;
//    default:
//      result = QString::compare( left.toString(), right.toString() );
//      result = ( result < 0 ? -1 : ( result > 0 ? 1 : 0 ) );
//      break;
//  }

  return result;
}
