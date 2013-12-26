#ifndef RESULTLOADER_P_H
#define RESULTLOADER_P_H

#include <QThread>

#include "resultloader.h"
#include "resultinfo.h"

#include <QSqlQuery>


class ResultLoader_P : public QThread
{
    Q_OBJECT
    friend class ResultLoader;


  public:


  signals:
    void sendError( QString errorText );
    void availableCountChanged();


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;
    QSqlQuery *m__Query;
    int m__AvailableCount;
    int m__ReceivedCount;

    explicit ResultLoader_P( ResultLoader *parent );
    ~ResultLoader_P();

    ResultLoader * p_dptr() const;

    ResultInfo * newInfo();
};

#endif // RESULTLOADER_P_H
