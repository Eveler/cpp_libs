#ifndef MABSTRACTDBWRAPPER_H
#define MABSTRACTDBWRAPPER_H

#include <QThread>
#include "mdatasourcemodel.h"

#include "export/mdataset_export_lib.h"


class QReadWriteLock;
class MAbstractDataSource;


class EXPORT_MDATASET MAbstractDBWrapper : public QThread, public ObjectListPrivate
{
    Q_OBJECT


  public:
    enum SourceType {
      Founded = 0,
      Initiated,
      Selected
    };
    enum JobType {
      None = 0,
      Searching,
      Initiating,
      Saving
    };

    explicit MAbstractDBWrapper( MAbstractDataSource *parent = NULL );
    ~MAbstractDBWrapper();

    void setParent( MAbstractDataSource *parent );

    QString connectionName() const;
    bool setConnectionName( const QString &connectionName );

    bool find( const QString &filter );
    bool initiate();
    bool select( int indexInFounded );
    bool save( int indexInInitiated );

    QObject * object( int sourceType, int index ) const;
    int count( int sourceType ) const;
    int index( int sourceType, QObject *object ) const;

    QObject * object( void *sourceType, int index ) const;
    int count( void *sourceType ) const;
    int index( void *sourceType, QObject *object ) const;


  signals:

  public slots:


  protected:
    QReadWriteLock * locker() const;
    void run();
    void job( int objectiveType, const QVariant &objectiveValue );
    QPair<int, QVariant> objective();
    virtual bool searching( const QString &queryText ) = 0;
    virtual bool initiating() = 0;
    virtual bool saving( QObject *object ) = 0;


  private:
    QReadWriteLock *m__Locker;
    QString m__ConnectionName;
    int m__ObjectiveType;
    QVariant m__ObjectiveValue;
};

#endif // MABSTRACTDBWRAPPER_H
