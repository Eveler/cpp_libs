#ifndef QWIA_H
#define QWIA_H

#include "export/qwia_export.h"
//#include <wia.h>
#include <QObject>

#define WIA_IMG_FORMAT_PNG "{B96B3CAF-0728-11D3-9D7B-0000F81EF32E}"

class QAxObject;
class QWIASHARED_EXPORT QWia: public QObject
{
  Q_OBJECT
public:
  QWia(QObject *parent=0);
  ~QWia();
  void setFileName(const QString& fn="scan.png");

public slots:
  bool selectDevice();
  bool scan();
  void comError(int code,QString source,QString descr,QString help);

private:
//  IWiaDevMgr *devMgr;

//  QAxObject *devMgr1;
  QAxObject *commonDlg;
  QAxObject *dev;
  QString fName;

//  BSTR devID;

//  QString errorString(HRESULT hr) const;

//  HRESULT createWiaDeviceManager(IWiaDevMgr **ppWiaDevMgr);
//  HRESULT enumerateWiaDevices(IWiaDevMgr *pWiaDevMgr);
//  HRESULT readSomeWiaProperties(IWiaPropertyStorage *pWiaPropertyStorage);
//  HRESULT getWiaItemProperties(IWiaItem *rootItem, ULONG c_nPropCount, PROPSPEC propSpec[],
//                               PROPVARIANT propRet[]) const;
//  HRESULT createWiaDevice(IWiaDevMgr *pWiaDevMgr, BSTR bstrDeviceID,
//                          IWiaItem **ppWiaDevice);
//  HRESULT enumerateItems(IWiaItem *pWiaItem);
//  HRESULT transferWiaItem(IWiaItem *pWiaItem);

//  bool isAcquiredFromFeeder(IWiaItem *rootItem) const;
};

#endif // QWIA_H
