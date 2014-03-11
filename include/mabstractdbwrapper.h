#ifndef MABSTRACTDBWRAPPER_H
#define MABSTRACTDBWRAPPER_H

#include <QThread>
#include "mdatasourcemodel.h"

#include "export/mdataset_export_lib.h"


class QReadWriteLock;
class MDataSource;


class EXPORT_MDATASET MAbstractDBWrapper : public QThread, public ObjectListPrivate
{
    Q_OBJECT


  public:
    enum SourceType {
      Founded = 0,
      Initiated
    };
    enum JobType {
      None = 0,
      Searching,
      Initiating,
      Saving
    };

    explicit MAbstractDBWrapper( MDataSource *parent = NULL );
    ~MAbstractDBWrapper();

    void setParent( MDataSource *parent );

    QString connectionName() const;
    bool setConnectionName( const QString &connectionName );

    void find( const QString &filter );
    void initiate();
    void save( QObject *object );

    QObject * object( int sourceType, int index ) const;
    int count( int sourceType ) const;
    int index( int sourceType, QObject *object ) const;


  signals:

  public slots:


  protected:
    QReadWriteLock * locker() const;
    void run();
    void job();
    QPair<JobType, QVariant> objective();
    virtual bool searching( const QString &queryText ) = 0;
    virtual bool initiating() = 0;
    virtual bool saving( QObject *object ) = 0;


  private:
    QReadWriteLock *m__Locker;
    QString m__ConnectionName;
    JobType m__ObjectiveType;
    QVariant m__ObjectiveValue;
};

#endif // MABSTRACTDBWRAPPER_H
