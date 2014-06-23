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

    virtual bool find( const QString &filter );
    virtual bool initiate();
    virtual bool select( int indexInFounded );
    virtual bool save( QObject *object );

    QObject * object( int sourceType, int index ) const;
    int count( int sourceType ) const;
    int index( int sourceType, QObject *object ) const;

    QObject * object( QObject * sourceType, int index ) const;
    int count( QObject *sourceType ) const;
    int index( QObject * sourceType, QObject *object ) const;

    void releaseOldResources();


  signals:
    void aboutToReleaseOldResources();

  public slots:


  protected:
    QReadWriteLock * locker() const;
    const QString & pConnectionName() const;
    void setObjective( int objectiveType, QVariant objectiveValue );
    void run();
    QPair<int, QVariant> objective();
    virtual void job( int objectiveType, const QVariant &objectiveValue );
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
