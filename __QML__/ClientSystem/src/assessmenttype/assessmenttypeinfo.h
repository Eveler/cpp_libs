#ifndef ASSESSMENTTYPEINFO_H
#define ASSESSMENTTYPEINFO_H

#include <QObject>

#include <QtQml>


class AssessmenttypeInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AssessmenttypeInfo)


  public:
    AssessmenttypeInfo();
    ~AssessmenttypeInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName( QString name );

  private:
    QVariant m__Identifier;
    QString m__Name;
};

QML_DECLARE_TYPE(AssessmenttypeInfo)

#endif // ASSESSMENTTYPEINFO_H
