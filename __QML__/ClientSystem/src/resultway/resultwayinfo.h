#ifndef RESULTWAYINFO_H
#define RESULTWAYINFO_H

#include <QObject>

#include <QtQml>


class ResultwayInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ResultwayInfo)


  public:
    ResultwayInfo();
    ~ResultwayInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName( QString name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

QML_DECLARE_TYPE(ResultwayInfo)

#endif // RESULTWAYINFO_H
