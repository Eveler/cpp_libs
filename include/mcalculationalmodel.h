#ifndef MCALCULATIONALMODEL_H
#define MCALCULATIONALMODEL_H

#include <QAbstractItemModel>

#include "lib_export.h"


class MCalculationalRow;
class MCalculationalModelPrivate;

class EXPORT MCalculationalModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  explicit MCalculationalModel(QObject *parent = 0);

  int rowCount(const QModelIndex & = QModelIndex()) const;
  int columnCount( const QModelIndex & = QModelIndex() ) const;

  QModelIndex index( int row, int column, const QModelIndex & = QModelIndex() ) const;
  QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const;
  QVariant headerData( int section, Qt::Orientation orientation = Qt::Horizontal,
                       int role = Qt::DisplayRole ) const;

  QModelIndex parent( const QModelIndex & ) const;

  bool insertRow( int row, const QModelIndex & parent = QModelIndex() );
  bool insertRows( int row, int count, const QModelIndex &parent = QModelIndex() );

  bool removeRow( int row, const QModelIndex &parent = QModelIndex() );
  bool removeRows( int row, int count, const QModelIndex &parent = QModelIndex() );

  bool insertColumn( int column, const QModelIndex &parent = QModelIndex() );
  bool insertColumns( int column, int count, const QModelIndex &parent = QModelIndex() );

  bool removeColumn( int column, const QModelIndex &parent = QModelIndex() );
  bool removeColumns( int column, int count, const QModelIndex &parent = QModelIndex() );

  bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole );
  bool setHeaderData(
      int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::DisplayRole );

  MCalculationalRow * row( int rowIndex ) const;

  int findRow( MCalculationalRow *row ) const;


signals:


public slots:


private:
  MCalculationalModelPrivate *p;

  void declareValues();
};

#endif // MCALCULATIONALMODEL_H
