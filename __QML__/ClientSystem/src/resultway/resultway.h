#ifndef RESULTWAY_H
#define RESULTWAY_H

#include <QObject>

#include "resultwayinfo.h"

#include <QtQml>


class Resultway_P;
class ResultwayList;

class Resultway : public QObject, public ResultwayInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Resultway)
    friend class ResultwayList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


  public:
    Resultway( ResultwayList *parent = 0 );
    Resultway( ResultwayList *parent, const ResultwayInfo &info );
    Resultway( ResultwayList *parent, Resultway *link );
    ~Resultway();

    Q_INVOKABLE ResultwayList * resultwayList() const;

    int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName(  const QString &name );


  signals:
    void indexChanged();
    void identifierChanged();
    void nameChanged();


  public slots:


  private:
    Resultway_P *p;
};

QML_DECLARE_TYPE(Resultway)

#endif // RESULTWAY_H
