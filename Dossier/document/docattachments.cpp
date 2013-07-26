#include "docattachments.h"

DocAttachments::DocAttachments(){
  m_Attachments= QList< DocAttachment* >();

  nullAttachment=new DocAttachment( QString(), QString(), QByteArray() );
}

DocAttachments::~DocAttachments(){
  removeAttachments( 0, count() );

  delete nullAttachment;
}

int DocAttachments::addAttachment(DocAttachment &attachment){
  if ( !attachment.isValid() ) return -1;
  m_Attachments.append(
        /*new DocAttachment( attachment.fileName(),attachment.mimeType(),
                           attachment.data() )*/ &attachment);

  return m_Attachments.count()-1;

}

bool DocAttachments::insertAttachment(int intoPos, DocAttachment &attachment){
  if ( intoPos < 0 || intoPos >= count() || !attachment.isValid() ) return false;
  m_Attachments.insert( intoPos,
                        new DocAttachment(attachment.fileName(),
                                          attachment.mimeType(),
                                          attachment.data()));

  return true;
}

bool DocAttachments::removeAttachment(int attachmentPos){
  if ( attachmentPos < 0 || attachmentPos >= count() ) return false;
  delete m_Attachments.takeAt( attachmentPos);

  return true;
}

bool DocAttachments::removeAttachment(const QString &fileName){
  for ( int attIdx = 0; attIdx < count(); attIdx++ )
    if ( m_Attachments[attIdx]->fileName() == fileName )
    {
      delete m_Attachments.takeAt( attIdx );
      return true;
    }

  return false;
}

bool DocAttachments::removeAttachments(int from, int cnt){
  int fullCount = from+cnt;
  if ( from < 0 || cnt <= 0 || fullCount > count() ) return false;
  for ( int attIdx = fullCount-1; attIdx > from-1; attIdx-- )
    delete m_Attachments.takeAt( attIdx );

  return true;
}

DocAttachment *DocAttachments::getAttachment(int attachmentPos){
  if ( attachmentPos < 0 || attachmentPos >= count() ) return nullAttachment;

  return m_Attachments[attachmentPos];
}

DocAttachment *DocAttachments::getAttachment(const QString &fileName){
  for ( int attIdx = 0; attIdx < count(); attIdx++ )
    if ( m_Attachments[attIdx]->fileName() == fileName )
      return m_Attachments[attIdx];

  return nullAttachment;
}

const DocAttachment & DocAttachments::takeAttachment(int attachmentPos){
  if ( attachmentPos < 0 || attachmentPos >= count() ) return *nullAttachment;

  return *( m_Attachments.takeAt( attachmentPos ) );
}

const DocAttachment & DocAttachments::takeAttachment(const QString &fileName){
  for ( int attIdx = 0; attIdx < count(); attIdx++ )
    if ( m_Attachments[attIdx]->fileName() == fileName )
      return *( m_Attachments.takeAt( attIdx ) );

  return *nullAttachment;
}

int DocAttachments::count(){
  return m_Attachments.count();
}
