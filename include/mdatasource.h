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
    Q_INVOKABLE void saveObject( QObject *object );

    QString connectionName() const;
    void setConnectionName( const QString & connectionName );
    int status() const;
    MDataSourceModel * founded() const;
    MDataSourceModel * initiated() const;


  signals:
    void connectionNameChanged();
    void statusChanged();
    void foundedChanged();
    void initiatedChanged();
    void saved();


  public slots:


  protected:
    void setDBWrapper( MAbstractDBWrapper *wrapper );
    MAbstractDBWrapper *dbWrapper() const;


  private:
    MAbstractDBWrapper *m__Wrapper;
    MDataSourceModel *m__Founded;
    MDataSourceModel *m__Initiated;
    int m__SavedObjectIndex;


  private slots:
    void findObjectFinished();
    void initiateObjectFinished();
    void saveObjectFinished();
};

QML_DECLARE_TYPE( MDataSource )

#endif // MDATASOURCE_H
