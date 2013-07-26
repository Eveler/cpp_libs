#ifndef DOCATTACHMENTS_H
#define DOCATTACHMENTS_H

#include "docattachment.h"

class DocAttachments
{
public:
  DocAttachments();
  ~DocAttachments();
  int addAttachment( DocAttachment &attachment );
  bool insertAttachment( int intoPos, DocAttachment &attachment);

  bool removeAttachment( int attachmentPos );
  bool removeAttachment( const QString & fileName );

  bool removeAttachments( int from, int cnt );

  DocAttachment* getAttachment( int attachmentPos );
  DocAttachment* getAttachment( const QString & fileName );

  const DocAttachment & takeAttachment( int attachmentPos );
  const DocAttachment & takeAttachment( const QString & fileName );

  int count();

private:
  QList< DocAttachment * > m_Attachments;

  DocAttachment *nullAttachment;
};

#endif // DOCATTACHMENTS_H
