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

    virtual QObject * object( QObject *sourceType, int index ) const = 0;
    virtual int count( QObject *sourceType ) const = 0;
    virtual int index( QObject *sourceType, QObject *object ) const = 0;


  protected:
    QVariantList sourceTypes() const;

    QObject * pObject( int sourceType, int index ) const;
    int pCount( int sourceType ) const;
    int pIndex( int sourceType, QObject *object ) const;
    void pInsert( int sourceType, QObject *object, int index = -1 );
    QObject * pTake( int sourceType, int index );

    QObject * pObject( QObject *sourceType, int index ) const;
    int pCount( QObject * sourceType ) const;
    int pIndex( QObject *sourceType, QObject *object ) const;
    void pInsert( QObject *sourceType, QObject *object, int index = -1 );
    QObject * pTake( QObject *sourceType, int index );


  private:
    QHash<int, QObjectList> m__Objects;
    QHash<QObject *, QObjectList> m__StarObjects;
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
    int index( QObject *object ) const;
    int count() const;
    void clear();

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
