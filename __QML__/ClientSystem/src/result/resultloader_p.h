#ifndef RESULTLOADER_P_H
#define RESULTLOADER_P_H

#include <QThread>

#include "resultloader.h"
#include "resultlist.h"

#include <QHash>


class ResultLoader_P : public QThread
{
    Q_OBJECT
    friend class ResultLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendResultInfo( ResultInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    ResultList *m__Source;

    explicit ResultLoader_P( ResultLoader *parent );
    ~ResultLoader_P();

    ResultLoader * p_dptr() const;
};

#endif // RESULTLOADER_P_H
