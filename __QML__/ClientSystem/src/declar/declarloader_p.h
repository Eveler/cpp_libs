#ifndef DECLARLOADER_P_H
#define DECLARLOADER_P_H

#include <QThread>

#include "declarloader.h"
#include "declarinfo.h"

#include <QSqlQuery>


class DeclarLoader_P : public QThread
{
    Q_OBJECT
    friend class DeclarLoader;


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

    explicit DeclarLoader_P( DeclarLoader *parent );
    ~DeclarLoader_P();

    DeclarLoader * p_dptr() const;

    DeclarInfo * newInfo();
};

#endif // DECLARLOADER_P_H
