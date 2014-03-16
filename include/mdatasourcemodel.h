#ifndef MDATASOURCEMODEL_H
#define MDATASOURCEMODEL_H

#include "mobjectmodel.h"

#include "export/mdataset_export_lib.h"

#include <QObjectList>


class EXPORT_MDATASET ObjectListPrivate
{
  public:
    ObjectListPrivate();
    ~ObjectListPrivate();

    virtual QObject * object( int sourceType, int index ) const = 0;
    virtual int count( int sourceType ) const = 0;
    virtual int index( int sourceType, QObject *object ) const = 0;

    virtual QObject * object( void *sourceType, int index ) const = 0;
    virtual int count( void *sourceType ) const = 0;
    virtual int index( void *sourceType, QObject *object ) const = 0;


  protected:
    QObject * pObject( int sourceType, int index ) const;
    int pCount( int sourceType ) const;
    int pIndex( int sourceType, QObject *object ) const;
    void pAppend( int sourceType, QObject *object );
    QObject * pTake( int sourceType, int index );

    QObject * pObject( void *sourceType, int index ) const;
    int pCount( void *sourceType ) const;
    int pIndex( void *sourceType, QObject *object ) const;
    void pAppend( void *sourceType, QObject *object );
    QObject * pTake( void *sourceType, int index );


  private:
    QHash<int, QObjectList> m__Objects;
    QHash<void *, QObjectList> m__StarObjects;
};


class EXPORT_MDATASET MDataSourceModel : public MObjectModel
{
    Q_OBJECT
    Q_PROPERTY(int sourceType READ sourceType WRITE setSourceType NOTIFY sourceTypeChanged)


  public:
    explicit MDataSourceModel(QObject *parent = 0);
    ~MDataSourceModel();

    int rowCount( const QModelIndex &parent = QModelIndex() ) const;
    QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const;

    SafelyValue * get( int index ) const;
    void append( QObject *object );
    void insert( int index, QObject *object );
    void remove( int index );
    void replace( int index, QObject *object );
    int count() const;
    int index( QObject *object ) const;

    void setSource( ObjectListPrivate *source );

    int sourceType() const;
    void setSourceType( int sourceType );

    void resetModel();
    void insertObjects( int first, int last );
    void removeObjects( int first, int last );


  signals:
    void sourceTypeChanged();


  public slots:


  protected:


  private:
    ObjectListPrivate *m__Source;
    int m__SourceType;
};

QML_DECLARE_TYPE( MDataSourceModel )

#endif // MDATASOURCEMODEL_H
