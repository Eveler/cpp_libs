#ifndef PROCEDUREINFO_H
#define PROCEDUREINFO_H

#include <QObject>

#include <QtQml>


class ProcedureInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ProcedureInfo)


  public:
    ProcedureInfo();
    ~ProcedureInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName( QString name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

QML_DECLARE_TYPE(ProcedureInfo)

#endif // PROCEDUREINFO_H
