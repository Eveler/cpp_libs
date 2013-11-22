#ifndef DECLARLOADER_P_H
#define DECLARLOADER_P_H

#include <QThread>

#include "declarloader.h"
#include "declarlist.h"

#include <QHash>


class DeclarLoader_P : public QThread
{
    Q_OBJECT
    friend class DeclarLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendDeclarInfo( DeclarInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    DeclarList *m__Source;

    explicit DeclarLoader_P( DeclarLoader *parent );
    ~DeclarLoader_P();

    DeclarLoader * p_dptr() const;
};

#endif // DECLARLOADER_P_H
