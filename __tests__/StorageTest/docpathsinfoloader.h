#ifndef DOCPATHSINFOLOADER_H
#define DOCPATHSINFOLOADER_H

#include <QObject>

#include <QVariant>


class DocpathsInfoLoader : public QObject
{
    Q_OBJECT
  public:
    explicit DocpathsInfoLoader( const QString &connectionName, QObject *parent = NULL );

    void load( int declarId ) const;


  signals:
    void docpathInfoLoaded( QVariant id ) const;
    void databaseError( QString error ) const;


  public slots:


  private:
    QString m__ConnectionName;
};

#endif // DOCPATHSINFOLOADER_H
