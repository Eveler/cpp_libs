#ifndef RESULTLOADER_P_H
#define RESULTLOADER_P_H

#include <QThread>

#include "resultloader.h"
#include "resultinfo.h"

#include <QHash>


class ResultLoader_P : public QThread
{
    Q_OBJECT
    friend class ResultLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( ResultInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit ResultLoader_P( ResultLoader *parent );
    ~ResultLoader_P();

    ResultLoader * p_dptr() const;
};

#endif // RESULTLOADER_P_H
