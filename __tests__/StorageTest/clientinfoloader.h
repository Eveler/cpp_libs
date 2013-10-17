#ifndef CLIENTINFOLOADER_H
#define CLIENTINFOLOADER_H

#include <QObject>

#include <QVariant>


class ClientInfoLoader : public QObject
{
    Q_OBJECT


  public:
    explicit ClientInfoLoader( const QString &connectionName, QObject *parent = NULL );

    void load( QVariant declarId ) const;


  signals:
    void clientInfoLoaded( QString fio, QString phone, QString address, QVariant id ) const;
    void databaseError( QString error ) const;


  public slots:


  private:
    QString m__ConnectionName;
};

#endif // CLIENTINFOLOADER_H
