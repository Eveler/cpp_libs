#ifndef ASSESSMENTTYPE_H
#define ASSESSMENTTYPE_H

#include <QObject>

#include "assessmenttypeinfo.h"

#include <QtQml>


class Assessmenttype_P;
class AssessmenttypeList;

class Assessmenttype : public QObject, public AssessmenttypeInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Assessmenttype)
    friend class AssessmenttypeList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


  public:
    Assessmenttype( AssessmenttypeList *parent = 0 );
    Assessmenttype( AssessmenttypeList *parent, const AssessmenttypeInfo &info );
    Assessmenttype( AssessmenttypeList *parent, Assessmenttype *link );
    ~Assessmenttype();

    Q_INVOKABLE AssessmenttypeList * assessmenttypeList() const;

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
    Assessmenttype_P *p;
};

QML_DECLARE_TYPE(Assessmenttype)

#endif // ASSESSMENTTYPE_H
