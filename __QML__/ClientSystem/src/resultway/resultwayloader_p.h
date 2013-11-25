#ifndef RESULTWAYLOADER_P_H
#define RESULTWAYLOADER_P_H

#include <QThread>

#include "resultwayloader.h"
#include "resultwaylist.h"

#include <QHash>


class ResultwayLoader_P : public QThread
{
    Q_OBJECT
    friend class ResultwayLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendResultwayInfo( ResultwayInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    ResultwayList *m__Source;

    explicit ResultwayLoader_P( ResultwayLoader *parent );
    ~ResultwayLoader_P();

    ResultwayLoader * p_dptr() const;
};

#endif // RESULTWAYLOADER_P_H
