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
typedef int (*DSiinf)(TW_IDENTITY, TW_IDENTITY, int, int, int, pTW_IMAGEINFO);
typedef int (*DSixfer)(TW_IDENTITY, TW_IDENTITY, int, int, int, HBITMAP);
typedef int (*DSpxfer)(TW_IDENTITY, TW_IDENTITY, int, int, int, pTW_PENDINGXFERS);

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
  bool saveImg(void *dibhandp, QString &fileName);

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
  DSiinf dsIinf;
  DSixfer dsIxfer;
  DSpxfer dsPxfer;

  void *getPixelInfo(void *bmpptr);
  bool getCodecClsid(QString &filename, LPCLSID clsid);
};


#endif // MTWAIN_H
