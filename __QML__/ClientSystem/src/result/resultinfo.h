#ifndef RESULTINFO_H
#define RESULTINFO_H

#include <QObject>

#include <QtQml>


class ResultInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ResultInfo)


  public:
    ResultInfo();
    ~ResultInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName( QString name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

QML_DECLARE_TYPE(ResultInfo)

#endif // RESULTINFO_H
