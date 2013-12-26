#ifndef DOCTYPEINFO_H
#define DOCTYPEINFO_H

#include <QObject>

#include <QtQml>


class DoctypeInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DoctypeInfo)


  public:
    DoctypeInfo();
    ~DoctypeInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName( QString name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

QML_DECLARE_TYPE(DoctypeInfo)

#endif // DOCTYPEINFO_H
