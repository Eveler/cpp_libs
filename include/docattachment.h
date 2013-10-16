#ifndef DOCATTACHMENT_H
#define DOCATTACHMENT_H

#include <QObject>

#include "export/dossier_export.h"

#include <QString>
#include <QByteArray>
#include <QTemporaryFile>


class DOSSIER_EXPORT DocAttachment : public QObject
{
    Q_OBJECT


  public:
    DocAttachment(const QString fileName,const QString mimeType,
                  const QByteArray &fileData);
    ~DocAttachment();
    QString fileName() const;
    QString mimeType() const;
    QByteArray data() const;
    QIODevice *device() const;
    bool isValid();

  private:
    QString fName;
    QString mType;
    QTemporaryFile *m_File;

    void initFile();


  private slots:
    void tempDestroyed();
};

#endif // DOCATTACHMENT_H
