#ifndef DOCTYPE_H
#define DOCTYPE_H

#include <QObject>

#include "doctypeinfo.h"

#include <QtQml>


class Doctype_P;
class DoctypeList;

class Doctype : public QObject, public DoctypeInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Doctype)
    friend class DoctypeList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


  public:
    Doctype( DoctypeList *parent = 0 );
    Doctype( DoctypeList *parent, const DoctypeInfo &info );
    Doctype( DoctypeList *parent, Doctype *link );
    ~Doctype();

    Q_INVOKABLE DoctypeList * doctypeList() const;

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
    Doctype_P *p;
};

QML_DECLARE_TYPE(Doctype)

#endif // DOCTYPE_H
