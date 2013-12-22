#ifndef HUMANLOADER_P_H
#define HUMANLOADER_P_H

#include <QThread>

#include "humanloader.h"
#include "humaninfo.h"

#include <QHash>


class HumanLoader_P : public QThread
{
    Q_OBJECT
    friend class HumanLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( HumanInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit HumanLoader_P( HumanLoader *parent );
    ~HumanLoader_P();

    HumanLoader * p_dptr() const;
};

#endif // HUMANLOADER_P_H
