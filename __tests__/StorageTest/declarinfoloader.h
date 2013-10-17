#ifndef DECLARINFOLOADER_H
#define DECLARINFOLOADER_H

#include <QObject>

#include <QVariant>


class DeclarInfoLoader : public QObject
{
    Q_OBJECT


  public:
    explicit DeclarInfoLoader( const QString &connectionName, QObject *parent = NULL );

    void load( int declarNum ) const;


  signals:
    void declarInfoLoaded( QVariant id, QVariant serviceId ) const;
    void databaseError( QString error ) const;


  public slots:


  private:
    QString m__ConnectionName;
};

#endif // DECLARINFOLOADER_H
