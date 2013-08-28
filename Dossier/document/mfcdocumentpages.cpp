#include "mfcdocumentpages.h"

MFCDocumentPages::MFCDocumentPages( QObject *parent ) :
    QObject(parent)
{
  m_Pages = QList<MFCDocumentPage *>();

  nullPage = new MFCDocumentPage( QString("null page"), QByteArray() );
}

MFCDocumentPages::~MFCDocumentPages()
{
  removePages( 0, count() );

  delete nullPage;
}

int MFCDocumentPages::addPage( MFCDocumentPage &page )
{
  if ( !page.isValid() ){
    error(QObject::tr("Ошибочная страница"));
    return -1;
  }
  m_Pages.append( /*new MFCDocumentPage( page.getPageName(),
                                       page.getBody() )*/ &page);

  emit countChanged( count() );

  return m_Pages.count()-1;
}

bool MFCDocumentPages::insertPage( int intoPos, MFCDocumentPage &page )
{
  if ( intoPos < 0 || intoPos > count() || !page.isValid() ){
    error(QObject::tr("Индекс \"%1\" выходит за границы списка").arg(intoPos));
    return false;
  }
  m_Pages.insert( intoPos, /*new MFCDocumentPage( page.getPageName(),
                                                page.getBody() )*/ &page);

  emit countChanged( count() );

  return true;
}

bool MFCDocumentPages::removePage( int pagePos )
{
  if ( pagePos < 0 || pagePos >= count() ){
    error(QObject::tr("Индекс выходит за границы списка"));
    return false;
  }
  MFCDocumentPage *page=m_Pages.takeAt( pagePos );
  delete page;
  page = NULL;

  emit countChanged( count() );

  return true;
}

bool MFCDocumentPages::removePage( const QString & pageName )
{
  for ( int pageIdx = 0; pageIdx < count(); pageIdx++ )
    if ( m_Pages[pageIdx]->getPageName() == pageName )
    {
      MFCDocumentPage *page = m_Pages.takeAt( pageIdx );
      delete page;
      page = NULL;

      emit countChanged( count() );

      return true;
    }
  error(QObject::tr("Страница с указанным именем не найдена"));
  return false;
}

bool MFCDocumentPages::removePages( int fromPage, int cnt )
{
  int fullCount = fromPage+cnt;
  if ( fromPage < 0 || cnt <= 0 || fullCount > count() ){
    error(QObject::tr("Диапазон выходит за границы списка"));
    return false;
  }
  for ( int pageIdx = fullCount-1; pageIdx > fromPage-1; pageIdx-- )
    if ( !removePage( pageIdx ) ) return false;

  return true;
}

MFCDocumentPage *MFCDocumentPages::getPage( int pagePos )
{
  if ( pagePos < 0 || pagePos >= count() ) return nullPage;

  return m_Pages[pagePos];
}

MFCDocumentPage *MFCDocumentPages::getPage( const QString & pageName )
{
  for ( int pageIdx = 0; pageIdx < count(); pageIdx++ )
    if ( m_Pages[pageIdx]->getPageName() == pageName )
      return m_Pages[pageIdx];

  return nullPage;
}

const MFCDocumentPage & MFCDocumentPages::takePage( int pagePos )
{
  if ( pagePos < 0 || pagePos >= count() ) return *nullPage;

  MFCDocumentPage *page = m_Pages.takeAt( pagePos );

  emit countChanged( count() );

  return *page;
}

const MFCDocumentPage & MFCDocumentPages::takePage( const QString & pageName )
{
  for ( int pageIdx = 0; pageIdx < count(); pageIdx++ )
    if ( m_Pages[pageIdx]->getPageName() == pageName )
    {
        MFCDocumentPage *page = m_Pages.takeAt( pageIdx );

        emit countChanged( count() );

        return *page;
    }

  return *nullPage;
}

int MFCDocumentPages::count()
{
  return m_Pages.count();
}

QString MFCDocumentPages::errorString(){
  return errStr;
}

void MFCDocumentPages::error(const QString str){
  errStr="MFCDocumentPages: "+str;
}
