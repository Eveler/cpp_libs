#ifndef USERLOADER_P_H
#define USERLOADER_P_H

#include <QThread>

#include "userloader.h"
#include "userinfo.h"

#include <QHash>


class UserLoader_P : public QThread
{
    Q_OBJECT
    friend class UserLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( UserInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit UserLoader_P( UserLoader *parent );
    ~UserLoader_P();

    UserLoader * p_dptr() const;
};

#endif // USERLOADER_P_H
