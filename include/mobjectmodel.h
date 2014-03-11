#ifndef MOBJECTMODEL_H
#define MOBJECTMODEL_H

#include <QQuickItem>
#include <QAbstractListModel>

#include "export/mmodels_export_lib.h"


class EXPORT_MMODELS SafelyValue : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value NOTIFY valueChanged)


  public:
    explicit SafelyValue( QObject *value = NULL );
    ~SafelyValue();

    QVariant value() const;


  signals:
    void valueChanged();
};


class EXPORT_MMODELS MObjectModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    enum ModelRole {
      ObjectRole = Qt::UserRole+1
    };

    explicit MObjectModel( QObject *parent = NULL );
    ~MObjectModel();

    int rowCount( const QModelIndex &parent = QModelIndex() ) const;
    QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const;

    Q_INVOKABLE virtual SafelyValue * get( int index ) const;
    Q_INVOKABLE virtual void append( QObject *object );
    Q_INVOKABLE virtual void insert( int index, QObject *object );
    Q_INVOKABLE virtual void remove( int index );
    Q_INVOKABLE virtual void replace( int index, QObject *object );
    Q_INVOKABLE virtual int index( QObject *object ) const;

    virtual int count() const;


  signals:
    void countChanged();


  protected:
    QHash<int, QByteArray> roleNames() const;


  public slots:


  private:
    QList<QObject *> m__Objects;
};

QML_DECLARE_TYPE( MObjectModel )

#endif // MOBJECTMODEL_H
