#ifndef DOCTYPELOADER_P_H
#define DOCTYPELOADER_P_H

#include <QThread>

#include "doctypeloader.h"
#include "doctypeinfo.h"

#include <QSqlQuery>


class DoctypeLoader_P : public QThread
{
    Q_OBJECT
    friend class DoctypeLoader;


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

    explicit DoctypeLoader_P( DoctypeLoader *parent );
    ~DoctypeLoader_P();

    DoctypeLoader * p_dptr() const;

    DoctypeInfo * newInfo();
};

#endif // DOCTYPELOADER_P_H
