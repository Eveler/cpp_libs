#ifndef DOCTYPELOADER_P_H
#define DOCTYPELOADER_P_H

#include <QThread>

#include "doctypeloader.h"
#include "doctypelist.h"

#include <QHash>


class DoctypeLoader_P : public QThread
{
    Q_OBJECT
    friend class DoctypeLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendDoctypeInfo( DoctypeInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    DoctypeList *m__Source;

    explicit DoctypeLoader_P( DoctypeLoader *parent );
    ~DoctypeLoader_P();

    DoctypeLoader * p_dptr() const;
};

#endif // DOCTYPELOADER_P_H
