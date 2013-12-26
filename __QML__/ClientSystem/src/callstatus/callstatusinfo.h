#ifndef CALLSTATUSINFO_H
#define CALLSTATUSINFO_H

#include <QObject>

#include <QtQml>


class CallstatusInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CallstatusInfo)


public:
    CallstatusInfo();
    ~CallstatusInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName( QString name );


private:
    QVariant m__Identifier;
    QString m__Name;
};

QML_DECLARE_TYPE(CallstatusInfo)

#endif // CALLSTATUSINFO_H
