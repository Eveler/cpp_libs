#ifndef DOCATTACHMENTS_H
#define DOCATTACHMENTS_H

#include <QObject>

#include "export/dossier_export.h"
#include "docattachment.h"


class DOSSIER_EXPORT DocAttachments: public QObject
{
    Q_OBJECT


public:
  DocAttachments( QObject *parent = 0 );
  ~DocAttachments();
  int addAttachment( const QString fileName,const QString mimeType,
                     const QByteArray &fileData );
  bool insertAttachment( int intoPos, const QString fileName,
                         const QString mimeType, const QByteArray &fileData );

  bool removeAttachment( int attachmentPos );
  bool removeAttachment( const QString & fileName );

  bool removeAttachments( int from, int cnt );

  const DocAttachment & getAttachment( int attachmentPos );
  const DocAttachment & getAttachment( const QString & fileName );

  int count();


signals:
  void countChanged( int count );


private:
  QList< DocAttachment * > m_Attachments;

  DocAttachment *nullAttachment;
};

#endif // DOCATTACHMENTS_H
