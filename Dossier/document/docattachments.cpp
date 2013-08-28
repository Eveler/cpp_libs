#include "docattachments.h"

DocAttachments::DocAttachments( QObject *parent ) :
    QObject(parent)
{
  m_Attachments= QList< DocAttachment* >();

  nullAttachment=new DocAttachment( QString(), QString(), QByteArray() );
}

DocAttachments::~DocAttachments(){
  removeAttachments( 0, count() );

  delete nullAttachment;
}

int DocAttachments::addAttachment( const QString fileName,
                                   const QString mimeType,
                                   const QByteArray &fileData )
{
    m_Attachments.append(
                new DocAttachment( fileName, mimeType, fileData ) );

    emit countChanged( m_Attachments.count() );

    return m_Attachments.count()-1;
}

bool DocAttachments::insertAttachment( int intoPos,
                                       const QString fileName,
                                       const QString mimeType,
                                       const QByteArray &fileData){
  if ( intoPos < 0 || intoPos >= count() ) return false;
  m_Attachments.insert( intoPos, new DocAttachment( fileName, mimeType, fileData ) );

  emit countChanged( m_Attachments.count() );

  return true;
}

bool DocAttachments::removeAttachment(int attachmentPos){
  if ( attachmentPos < 0 || attachmentPos >= count() ) return false;
  delete m_Attachments.takeAt( attachmentPos);

  emit countChanged( m_Attachments.count() );

  return true;
}

bool DocAttachments::removeAttachment(const QString &fileName){
  for ( int attIdx = 0; attIdx < count(); attIdx++ )
    if ( m_Attachments[attIdx]->fileName() == fileName )
    {
        delete m_Attachments.takeAt( attIdx );

        emit countChanged( m_Attachments.count() );

        return true;
    }

  return false;
}

bool DocAttachments::removeAttachments(int from, int cnt){
  int fullCount = from+cnt;
  if ( from < 0 || cnt <= 0 || fullCount > count() ) return false;
  for ( int attIdx = fullCount-1; attIdx > from-1; attIdx-- )
    delete m_Attachments.takeAt( attIdx );

  emit countChanged( m_Attachments.count() );

  return true;
}

const DocAttachment & DocAttachments::getAttachment( int attachmentPos )
{
  if ( attachmentPos < 0 || attachmentPos >= count() ) return *nullAttachment;

  return *m_Attachments[attachmentPos];
}

const DocAttachment & DocAttachments::getAttachment( const QString &fileName )
{
  for ( int attIdx = 0; attIdx < count(); attIdx++ )
    if ( m_Attachments[attIdx]->fileName() == fileName )
      return *m_Attachments[attIdx];

  return *nullAttachment;
}

int DocAttachments::count(){
  return m_Attachments.count();
}
