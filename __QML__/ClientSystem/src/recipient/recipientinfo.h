#ifndef RECIPIENTINFO_H
#define RECIPIENTINFO_H

#include <QObject>

#include <QtQml>


class RecipientInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RecipientInfo)


  public:
    RecipientInfo();
    ~RecipientInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE const QString & name() const;
    Q_INVOKABLE void setName( const QString &name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

QML_DECLARE_TYPE(RecipientInfo)

#endif // RECIPIENTINFO_H
