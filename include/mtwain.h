#ifndef MTWAIN_H
#define MTWAIN_H

#ifndef Q_OS_WIN
//#error Windows platforms only
#endif

#include <QObject>
#include <QLibrary>
#include "export/qtwain_export_lib.h"
#include "twain.h"
#include <windows.h>

typedef int (*DSMparent)(TW_IDENTITY, int, int, int, int, HWND);
typedef int (*DSMident)(TW_IDENTITY, int, int, int, int, pTW_IDENTITY);
typedef int (*DSuserif)(TW_IDENTITY, TW_IDENTITY, int, int, int, pTW_USERINTERFACE);
typedef int (*DScap)(TW_IDENTITY, TW_IDENTITY, int, int, int, pTW_CAPABILITY);

class EXPORT_QTWAIN MTwain : public QObject
{
  Q_OBJECT
public:
  explicit MTwain(QObject *parent = 0);
  ~MTwain();

  bool init(HWND wnd);
  void finish();
  void closeSrc();
  void select();
  bool acquire();
  QList<HBITMAP> transfer();

signals:

public slots:

private:
  HWND hwnd;
  TW_IDENTITY appid;
  TW_IDENTITY srcds;
//  TW_EVENT evtmsg;

  static const short LanguageUSA = 13;
  static const short CountryUSA = 1;

  QLibrary *libTWAIN;
  DSMparent dsmParent;
  DSMident dsmIdent;
  DSuserif dsUserif;
  DScap dsCap;
};


#endif // MTWAIN_H
