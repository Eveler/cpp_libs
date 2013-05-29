#ifndef MFCDOCUMENTPAGES_H
#define MFCDOCUMENTPAGES_H

#include "mfcdocumentpage.h"

class MFCDocumentPages
{
public:
  MFCDocumentPages();
  ~MFCDocumentPages();
  int addPage( MFCDocumentPage &page );
  bool insertPage( int intoPos, MFCDocumentPage &page );

  bool removePage( int pagePos );
  bool removePage( const QString & pageName );

  bool removePages( int fromPage, int cnt );

  MFCDocumentPage* getPage( int pagePos );
  MFCDocumentPage* getPage( const QString & pageName );

  const MFCDocumentPage & takePage( int pagePos );
  const MFCDocumentPage & takePage( const QString & pageName );

  int count();
  QString errorString();

private:
  QList<MFCDocumentPage *> m_Pages;

  MFCDocumentPage *nullPage;
  QString errStr;
  void error(const QString str);
};

#endif // MFCDOCUMENTPAGES_H
