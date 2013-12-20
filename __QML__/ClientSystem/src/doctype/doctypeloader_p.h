#ifndef DOCTYPELOADER_P_H
#define DOCTYPELOADER_P_H

#include <QThread>

#include "doctypeloader.h"
#include "doctypeinfo.h"

#include <QHash>


class DoctypeLoader_P : public QThread
{
    Q_OBJECT
    friend class DoctypeLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( DoctypeInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit DoctypeLoader_P( DoctypeLoader *parent );
    ~DoctypeLoader_P();

    DoctypeLoader * p_dptr() const;
};

#endif // DOCTYPELOADER_P_H
