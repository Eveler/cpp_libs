#ifndef MTWAIN_H
#define MTWAIN_H

#ifndef Q_OS_WIN
//#error Windows platforms only
#endif

#include <QObject>
#include "export/qtwain_export_lib.h"
#include "twain.h"
#include <windows.h>

class EXPORT_QTWAIN MTwain : public QObject
{
  Q_OBJECT
public:
  explicit MTwain(QObject *parent = 0);
  ~MTwain();

  bool init(HWND wnd);
  void finish();
  void select();
  bool acquire();
  QList<HBITMAP> transfer();
  void closeSrc();

signals:

public slots:

private:
//  HWND hwnd;
  TW_IDENTITY appid;
  TW_IDENTITY srcds;
//  TW_EVENT evtmsg;

  static const short LanguageUSA = 13;
  static const short CountryUSA = 1;

};


#endif // MTWAIN_H
