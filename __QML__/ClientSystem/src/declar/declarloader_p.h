#ifndef DECLARLOADER_P_H
#define DECLARLOADER_P_H

#include <QThread>

#include "declarloader.h"
#include "declarinfo.h"

#include <QHash>


class DeclarLoader_P : public QThread
{
    Q_OBJECT
    friend class DeclarLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( DeclarInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit DeclarLoader_P( DeclarLoader *parent );
    ~DeclarLoader_P();

    DeclarLoader * p_dptr() const;
};

#endif // DECLARLOADER_P_H
