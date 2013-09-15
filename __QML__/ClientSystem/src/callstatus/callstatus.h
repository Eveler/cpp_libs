#ifndef CALLSTATUS_H
#define CALLSTATUS_H

#include <QObject>

#include "callstatusinfo.h"

#include <QtQml>


class Callstatus_P;
class CallstatusList;

class Callstatus : public QObject, public CallstatusInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Callstatus)
    friend class CallstatusList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


public:
    Callstatus( CallstatusList *parent = 0 );
    Callstatus( CallstatusList *parent, const CallstatusInfo &info );
    Callstatus( CallstatusList *parent, Callstatus *link );
    ~Callstatus();

    Q_INVOKABLE CallstatusList * callstatusList() const;

    int index() const;

    QVariant identifier() const;

    const QString & name() const;
    void setName(  const QString &name );


signals:
    void indexChanged();
    void nameChanged();


public slots:


private:
    Callstatus_P *p;
};

QML_DECLARE_TYPE(Callstatus)

#endif // CALLSTATUS_H
