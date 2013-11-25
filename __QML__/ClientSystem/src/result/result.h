#ifndef RESULT_H
#define RESULT_H

#include <QObject>

#include "resultinfo.h"

#include <QtQml>


class Result_P;
class ResultList;

class Result : public QObject, public ResultInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Result)
    friend class ResultList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


  public:
    Result( ResultList *parent = 0 );
    Result( ResultList *parent, const ResultInfo &info );
    Result( ResultList *parent, Result *link );
    ~Result();

    Q_INVOKABLE ResultList * resultList() const;

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
    Result_P *p;
};

QML_DECLARE_TYPE(Result)

#endif // RESULT_H
