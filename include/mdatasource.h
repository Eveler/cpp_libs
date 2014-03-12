#ifndef MDATASOURCE_H
#define MDATASOURCE_H

#include <QObject>

#include "export/mdataset_export_lib.h"
#include "mdatasourcemodel.h"


class MAbstractDBWrapper;

class EXPORT_MDATASET MDataSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString connectionName READ connectionName WRITE setConnectionName NOTIFY connectionNameChanged)
    Q_PROPERTY(int status READ status NOTIFY statusChanged)
    Q_PROPERTY(MDataSourceModel * founded READ founded NOTIFY foundedChanged)
    Q_PROPERTY(MDataSourceModel * initiated READ initiated NOTIFY initiatedChanged)
    Q_PROPERTY(MDataSourceModel * selected READ selected NOTIFY selectedChanged)


  public:
    enum Statuses {
      Ready = 0,
      Loading
    };

    explicit MDataSource( QObject *parent = NULL );
    explicit MDataSource( MAbstractDBWrapper *wrapper, QObject *parent = NULL );
    ~MDataSource();

    Q_INVOKABLE void findObject( const QString &filter = QString() );
    Q_INVOKABLE void initiateObject();
    Q_INVOKABLE void selectObject( int indexInFounded );
    Q_INVOKABLE void saveObject( int indexInInitiated );

    QString connectionName() const;
    void setConnectionName( const QString & connectionName );
    int status() const;
    MDataSourceModel * founded() const;
    MDataSourceModel * initiated() const;
    MDataSourceModel * selected() const;


  signals:
    void connectionNameChanged();
    void statusChanged();
    void foundedChanged();
    void initiatedChanged();
    void selectedChanged();
    void saved();


  public slots:


  protected:
    void setDBWrapper( MAbstractDBWrapper *wrapper );
    MAbstractDBWrapper *dbWrapper() const;

    int savedObjectIndex() const;
    void setSavedObjectIndex( int savedObjectIndex );


  protected slots:
    virtual void findObjectFinished() = 0;
    virtual void initiateObjectFinished() = 0;
    virtual void saveObjectFinished() = 0;


  private:
    MAbstractDBWrapper *m__Wrapper;
    MDataSourceModel *m__Founded;
    MDataSourceModel *m__Initiated;
    MDataSourceModel *m__Selected;
    int m__SavedObjectIndex;
};

QML_DECLARE_TYPE( MDataSource )

#endif // MDATASOURCE_H
