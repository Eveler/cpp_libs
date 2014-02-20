#include "qwia.h"
#include "amslogger.h"
#include <QAxObject>
//#include <QImage>
//#include <QTemporaryFile>
//#include "cdatacallback.h"

QWia::QWia(QObject *parent): QObject(parent)
{
  setFileName();
  commonDlg = new QAxObject("WIA.CommonDialog");
  connect(commonDlg, SIGNAL(exception(int,QString,QString,QString)),
          SLOT(comError(int,QString,QString,QString)));
  dev = commonDlg->querySubObject("ShowSelectDevice(DeviceType,AlwaysSelectDevice)",
                                  0, true);
  if(!dev){
    delete commonDlg;
    commonDlg = NULL;
  }else
    connect(dev, SIGNAL(exception(int,QString,QString,QString)),
            SLOT(comError(int,QString,QString,QString)));
//  devMgr = NULL;
//  devID = NULL;
//  HRESULT hr = createWiaDeviceManager(&devMgr);
//  if(0>hr){
//    LogWarning()<<errorString(hr);
//    devMgr = NULL;
//  }
}

QWia::~QWia(){
  if(dev) delete dev;
  if(commonDlg) delete commonDlg;
//  if(devMgr){
//    devMgr->Release();
//  }
}

void QWia::setFileName(const QString &fn)
{
  fName = fn;
}

bool QWia::scan()
{
  if(!commonDlg || !dev) return false;

  int fileNumber = 0;
  QAxObject *items = commonDlg->querySubObject("ShowSelectItems(Device)",
                                            dev->asVariant());
  if(!items){
    return false;
  }
  connect(items, SIGNAL(exception(int,QString,QString,QString)),
          SLOT(comError(int,QString,QString,QString)));

  int itemsCount = items->property("Count").toInt();
  QAxObject *properties = dev->querySubObject(
        "Properties(\"Document Handling Select\")");
  if(!properties){
    delete items;
    return false;
  }
  connect(properties, SIGNAL(exception(int,QString,QString,QString)),
          SLOT(comError(int,QString,QString,QString)));
  bool isFeeder = properties->property("Value").toInt()==1;
  delete properties;

  for(int i=1;i<=itemsCount;i++){
    QAxObject *item = items->querySubObject("Item(pos)", i);
    if(item){
      QAxObject *image = commonDlg->querySubObject("ShowTransfer(Item, FormatID)",
                                              item->asVariant(),
                                              WIA_IMG_FORMAT_PNG);
      if(image){
        image->dynamicCall("SaveFile(Filename)", tr("scan%1.png").arg(fileNumber++));
        delete image;
      }
      while(isFeeder && image){
        QAxObject *image = commonDlg->querySubObject("ShowTransfer(Item, FormatID)",
                                                item->asVariant(),
                                                WIA_IMG_FORMAT_PNG);
        if(image){
          image->dynamicCall("SaveFile(Filename)", tr("scan%1.png").arg(fileNumber++));
          delete image;
        }
      }
      delete item;
    }
  }
  delete items;

//  HRESULT hr = 0;
//  IWiaItem *rootItem = NULL;

//  hr = devMgr->SelectDeviceDlg(GetTopWindow(0), 0, 0, NULL, &rootItem);
//  LogDebug()<<"hr ="<<(int)hr<<"Top wnd ="<<GetTopWindow(0)<<errorString(hr);
//  if(!rootItem){
//    return false;
//  }

//  long itemCount = 0;
//  IWiaItem **items = NULL;
//  hr = rootItem->DeviceDlg(GetTopWindow(0), 0, WIA_INTENT_NONE, &itemCount,
//                           (IWiaItem***)&items);
//  LogDebug()<<"hr ="<<(int)hr<<"itemCount ="<<(int)itemCount<<errorString(hr);
//  if(itemCount == 0){
//    rootItem->Release();
//    return false;
//  }

//  bool doContinue = isAcquiredFromFeeder(rootItem);

//  if(S_OK == hr){
//    for(int i=0;i<itemCount;i++){
//      hr = transferWiaItem(items[i]);
//      LogDebug()<<"hr ="<<(int)hr<<errorString(hr);
//      while(doContinue && S_OK == hr){
//        hr = transferWiaItem(items[i]);
//        LogDebug()<<"hr ="<<(int)hr<<errorString(hr);
//      }
//    }
//  }
//  CoTaskMemFree(items);

//  if(rootItem) rootItem->Release();
  return true;
}

void QWia::comError(int code, QString source, QString descr, QString help)
{
  LogWarning()<<"code ="<<code<<"\nsource ="<<source<<"\ndescr ="<<descr
                <<"\nhelp ="<<help;
}

//QString QWia::errorString(HRESULT hr) const
//{
//  QString errStr;
//  if(S_OK != hr && S_FALSE != hr){
//    switch(hr){
//    case WIA_ERROR_BUSY:
//      errStr = "WIA_ERROR_BUSY";
//      break;
//    case WIA_ERROR_DEVICE_COMMUNICATION:
//      errStr = "WIA_ERROR_DEVICE_COMMUNICATION";
//      break;
//    case WIA_ERROR_DEVICE_LOCKED:
//      errStr = "WIA_ERROR_DEVICE_LOCKED";
//      break;
//    case WIA_ERROR_EXCEPTION_IN_DRIVER:
//      errStr = "WIA_ERROR_EXCEPTION_IN_DRIVER";
//      break;
//    case WIA_ERROR_GENERAL_ERROR:
//      errStr = "WIA_ERROR_GENERAL_ERROR";
//      break;
//    case WIA_ERROR_INCORRECT_HARDWARE_SETTING:
//      errStr = "WIA_ERROR_INCORRECT_HARDWARE_SETTING";
//      break;
//    case WIA_ERROR_INVALID_COMMAND:
//      errStr = "WIA_ERROR_INVALID_COMMAND";
//      break;
//    case WIA_ERROR_INVALID_DRIVER_RESPONSE:
//      errStr = "WIA_ERROR_INVALID_DRIVER_RESPONSE";
//      break;
//    case WIA_ERROR_ITEM_DELETED:
//      errStr = "WIA_ERROR_ITEM_DELETED";
//      break;
//    case WIA_ERROR_OFFLINE:
//      errStr = "WIA_ERROR_OFFLINE";
//      break;
//    case WIA_ERROR_PAPER_EMPTY:
//      errStr = "WIA_ERROR_PAPER_EMPTY";
//      break;
//    case WIA_ERROR_PAPER_JAM:
//      errStr = "WIA_ERROR_PAPER_JAM";
//      break;
//    case WIA_ERROR_PAPER_PROBLEM:
//      errStr = "WIA_ERROR_PAPER_PROBLEM";
//      break;
//    case WIA_ERROR_USER_INTERVENTION:
//      errStr = "WIA_ERROR_USER_INTERVENTION";
//      break;
//    case WIA_ERROR_WARMING_UP:
//      errStr = "WIA_ERROR_WARMING_UP";
//      break;
//    case E_NOTIMPL:
//      errStr = "E_NOTIMPL";
//      break;
//    case E_OUTOFMEMORY:
//      errStr = "E_OUTOFMEMORY";
//      break;
//    case E_INVALIDARG:
//      errStr = "E_INVALIDARG";
//      break;
//    case E_NOINTERFACE:
//      errStr = "E_NOINTERFACE";
//      break;
//    case E_FAIL:
//      errStr = "E_FAIL";
//      break;
//    default:
//      errStr = "unknown error";
//      break;
//    }
//    errStr = tr("%1, code = 0x%2").arg(errStr).arg(hr&0xffffffff, 0, 16);
//  }

//  return errStr;
//}

//HRESULT QWia::createWiaDeviceManager(IWiaDevMgr **ppWiaDevMgr)
//{
//  // Validate arguments
//  if (NULL == ppWiaDevMgr)
//  {
//    return E_INVALIDARG;
//  }

//  // Initialize out variables
//  *ppWiaDevMgr = NULL;

//  // Create an instance of the device manager
//  HRESULT hr = CoCreateInstance( CLSID_WiaDevMgr, NULL, CLSCTX_LOCAL_SERVER,
//                                 IID_IWiaDevMgr, (void**)ppWiaDevMgr );

//  // Return the result of creating the device manager
//  return hr;
//}

//HRESULT QWia::enumerateWiaDevices(IWiaDevMgr *pWiaDevMgr)
//{
//  // Validate arguments
//  if (NULL == pWiaDevMgr)
//  {
//    return E_INVALIDARG;
//  }

//  // Get a device enumerator interface
//  IEnumWIA_DEV_INFO *pWiaEnumDevInfo = NULL;
//  HRESULT hr = pWiaDevMgr->EnumDeviceInfo( WIA_DEVINFO_ENUM_LOCAL,
//                                           &pWiaEnumDevInfo );
//  if (SUCCEEDED(hr))
//  {
//    // Loop until you get an error or pWiaEnumDevInfo->Next returns
//    // S_FALSE to signal the end of the list.
//    while (S_OK == hr)
//    {
//      // Get the next device's property storage interface pointer
//      IWiaPropertyStorage *pWiaPropertyStorage = NULL;
//      hr = pWiaEnumDevInfo->Next( 1, &pWiaPropertyStorage, NULL );

//      // pWiaEnumDevInfo->Next will return S_FALSE when the list is
//      // exhausted, so check for S_OK before using the returned
//      // value.
//      if (hr == S_OK)
//      {
//        // Do something with the device's IWiaPropertyStorage*
//        hr = readSomeWiaProperties(pWiaPropertyStorage);
//        LogDebug()<<"hr ="<<(int)hr<<errorString(hr);

//        // Release the device's IWiaPropertyStorage*
//        pWiaPropertyStorage->Release();
//        pWiaPropertyStorage = NULL;
//      }
//    }

//    // If the result of the enumeration is S_FALSE (which
//    // is normal), change it to S_OK.
//    if (S_FALSE == hr)
//    {
//      hr = S_OK;
//    }

//    // Release the enumerator
//    pWiaEnumDevInfo->Release();
//    pWiaEnumDevInfo = NULL;
//  }

//  // Return the result of the enumeration
//  return hr;
//}

//HRESULT QWia::readSomeWiaProperties( IWiaPropertyStorage *pWiaPropertyStorage )
//{
//  // Validate arguments
//  if (NULL == pWiaPropertyStorage)
//  {
//    return E_INVALIDARG;
//  }

//  // Declare PROPSPECs and PROPVARIANTs, and initialize them to zero.
//  PROPSPEC PropSpec[3] = {0, 0};
//  PROPVARIANT PropVar[3] = {0, 0, 0, 0, 0};

//  // How many properties are you querying for?
//  const ULONG c_nPropertyCount = sizeof(PropSpec)/sizeof(PropSpec[0]);

//  // Define which properties you want to read:
//  // Device ID.  This is what you would use to create
//  // the device.
//  PropSpec[0].ulKind = PRSPEC_PROPID;
//  PropSpec[0].propid = WIA_DIP_DEV_ID;

//  // Device Name
//  PropSpec[1].ulKind = PRSPEC_PROPID;
//  PropSpec[1].propid = WIA_DIP_DEV_NAME;

//  // Device description
//  PropSpec[2].ulKind = PRSPEC_PROPID;
//  PropSpec[2].propid = WIA_DIP_DEV_DESC;

//  // Ask for the property values
//  HRESULT hr = pWiaPropertyStorage->ReadMultiple( c_nPropertyCount, PropSpec,
//                                                  PropVar );
//  if (SUCCEEDED(hr))
//  {
//    // IWiaPropertyStorage::ReadMultiple will return S_FALSE if some
//    // properties could not be read, so you have to check the return
//    // types for each requested item.

//    // Check the return type for the device ID
//    if (VT_BSTR == PropVar[0].vt)
//    {
//      // Do something with the device ID
//      LogDebug()<<"WIA_DIP_DEV_ID: "<<QString::fromWCharArray(PropVar[0].bstrVal);
//      devID = PropVar[0].bstrVal;
//    }

//    // Check the return type for the device name
//    if (VT_BSTR == PropVar[1].vt)
//    {
//      // Do something with the device name
//      LogDebug()<<"WIA_DIP_DEV_NAME: "<<QString::fromWCharArray(PropVar[1].bstrVal);
//    }

//    // Check the return type for the device description
//    if (VT_BSTR == PropVar[2].vt)
//    {
//      // Do something with the device description
//      LogDebug()<<"WIA_DIP_DEV_DESC: "<<QString::fromWCharArray(PropVar[2].bstrVal);
//    }

//    // Free the returned PROPVARIANTs
//    FreePropVariantArray( c_nPropertyCount, PropVar );
//  }

//  // Return the result of reading the properties
//  return hr;
//}

//HRESULT QWia::getWiaItemProperties(IWiaItem *rootItem, ULONG c_nPropCount,
//                                   PROPSPEC propSpec[],
//                                   PROPVARIANT propRet[]) const
//{
//  IWiaPropertyStorage *pWiaPropertyStorage = NULL;
//  HRESULT hr = rootItem->QueryInterface(IID_IWiaPropertyStorage,
//                           (void**)&pWiaPropertyStorage);
//  if(SUCCEEDED(hr)){
//    if(c_nPropCount==0){
//      pWiaPropertyStorage->Release();
//      return E_INVALIDARG;
//    }

//    hr = pWiaPropertyStorage->ReadMultiple(c_nPropCount, propSpec, propRet);
//    pWiaPropertyStorage->Release();
//  }
//  return hr;
//}

//HRESULT QWia::createWiaDevice( IWiaDevMgr *pWiaDevMgr, BSTR bstrDeviceID,
//                               IWiaItem **ppWiaDevice )
//{
//  // Validate arguments
//  if (NULL == pWiaDevMgr || NULL == bstrDeviceID || NULL == ppWiaDevice)
//  {
//    return E_INVALIDARG;
//  }

//  // Initialize out variables
//  *ppWiaDevice = NULL;

//  // Create the WIA Device
//  HRESULT hr = pWiaDevMgr->CreateDevice( bstrDeviceID, ppWiaDevice );

//  // Return the result of creating the device
//  return hr;
//}

//HRESULT QWia::enumerateItems(IWiaItem *pWiaItem)
//{
//  // Validate arguments
//  if (NULL == pWiaItem)
//  {
//    return E_INVALIDARG;
//  }

//  // Get the item type for this item.
//  LONG lItemType = 0;
//  HRESULT hr = pWiaItem->GetItemType( &lItemType );
//  if (SUCCEEDED(hr))
//  {
//    // If it is a folder, or it has attachments, enumerate its children.
//    if (lItemType & WiaItemTypeFolder || lItemType & WiaItemTypeHasAttachments)
//    {
//      // Get the child item enumerator for this item.
//      IEnumWiaItem *pEnumWiaItem = NULL;
//      hr = pWiaItem->EnumChildItems( &pEnumWiaItem );
//      if (SUCCEEDED(hr))
//      {
//        // Loop until you get an error or pEnumWiaItem->Next returns
//        // S_FALSE to signal the end of the list.
//        while (S_OK == hr)
//        {
//          // Get the next child item.
//          IWiaItem *pChildWiaItem = NULL;
//          hr = pEnumWiaItem->Next( 1, &pChildWiaItem, NULL );

//          // pEnumWiaItem->Next will return S_FALSE when the list is
//          // exhausted, so check for S_OK before using the returned
//          // value.
//          if (S_OK == hr)
//          {
//            // Recurse into this item.
//            hr = enumerateItems( pChildWiaItem );

//            // Release this item.
//            pChildWiaItem->Release();
//            pChildWiaItem = NULL;
//          }
//        }

//        // If the result of the enumeration is S_FALSE (which
//        // is normal), change it to S_OK.
//        if (S_FALSE == hr)
//        {
//          hr = S_OK;
//        }

//        // Release the enumerator.
//        pEnumWiaItem->Release();
//        pEnumWiaItem = NULL;
//      }
//    }
//  }
//  return  hr;
//}

//HRESULT QWia::transferWiaItem(IWiaItem *pWiaItem)
//{
//  // Validate arguments
//  if (NULL == pWiaItem)
//  {
//    return E_INVALIDARG;
//  }

//  // Get the IWiaPropertyStorage interface so you can set required properties.
//  IWiaPropertyStorage *pWiaPropertyStorage = NULL;
//  HRESULT hr = pWiaItem->QueryInterface( IID_IWiaPropertyStorage,
//                                         (void**)&pWiaPropertyStorage );
//  if (SUCCEEDED(hr))
//  {
//    // Prepare PROPSPECs and PROPVARIANTs for setting the
//    // media type and format
//    PROPSPEC PropSpec[2] = {0, 0};
//    PROPVARIANT PropVariant[2] = {0, 0, 0, 0, 0};
//    const ULONG c_nPropCount = sizeof(PropVariant)/sizeof(PropVariant[0]);

//    // Use BMP as the output format
//    GUID guidOutputFormat = WiaImgFmt_BMP;

//    // Initialize the PROPSPECs
//    PropSpec[0].ulKind = PRSPEC_PROPID;
//    PropSpec[0].propid = WIA_IPA_FORMAT;
//    PropSpec[1].ulKind = PRSPEC_PROPID;
//    PropSpec[1].propid = WIA_IPA_TYMED;

//    // Initialize the PROPVARIANTs
//    PropVariant[0].vt = VT_CLSID;
//    PropVariant[0].puuid = &guidOutputFormat;
//    PropVariant[1].vt = VT_I4;
//    PropVariant[1].lVal = TYMED_FILE;

//    // Set the properties
//    hr = pWiaPropertyStorage->WriteMultiple( c_nPropCount, PropSpec,
//                                             PropVariant, WIA_IPA_FIRST );
//    if (SUCCEEDED(hr))
//    {
//      // Get the IWiaDataTransfer interface
//      IWiaDataTransfer *pWiaDataTransfer = NULL;
//      hr = pWiaItem->QueryInterface( IID_IWiaDataTransfer,
//                                     (void**)&pWiaDataTransfer );
//      if (SUCCEEDED(hr))
//      {
//        // Create our callback class
//        CDataCallback *pCallback = new CDataCallback;
//        if (pCallback)
//        {
//          // Get the IWiaDataCallback interface from our callback class.
//          IWiaDataCallback *pWiaDataCallback = NULL;
//          hr = pCallback->QueryInterface( IID_IWiaDataCallback,
//                                          (void**)&pWiaDataCallback );
//          if (SUCCEEDED(hr))
//          {
//            // Perform the transfer using default settings
//            STGMEDIUM stgMedium = {0, 0, NULL};
//            stgMedium.tymed = TYMED_FILE;
//            hr = pWiaDataTransfer->idtGetData( &stgMedium, pWiaDataCallback );
//            if (S_OK == hr)
//            {
//              // Print the filename (note that this filename is always
//              // a WCHAR string, not TCHAR).
//              QString fileName = QString::fromWCharArray(stgMedium.lpszFileName);
//              LogDebug()<<"Transferred filename: "<<fileName;
//              QImage img(fileName);
//              QTemporaryFile file(qApp->applicationDirPath()+"/scanXXXXXX.png");
//              file.setAutoRemove(false);
//              img.save(&file, "PNG");

//              // Release any memory associated with the stgmedium
//              // This will delete the file stgMedium.lpszFileName.
//              ReleaseStgMedium( &stgMedium );
//            }

//            // Release the callback interface
//            pWiaDataCallback->Release();
//            pWiaDataCallback = NULL;
//          }

//          // Release our callback.  It should now delete itself.
//          pCallback->Release();
//          pCallback = NULL;
//        }

//        // Release the IWiaDataTransfer
//        pWiaDataTransfer->Release();
//        pWiaDataTransfer = NULL;
//      }
//    }

//    // Release the IWiaPropertyStorage
//    pWiaPropertyStorage->Release();
//    pWiaPropertyStorage = NULL;
//  }

//  return hr;
//}

//bool QWia::isAcquiredFromFeeder(IWiaItem *rootItem) const
//{
//  bool doContinue = false;
//  PROPSPEC PropSpec[1] = {0, 0};
//  PROPVARIANT PropVariant[1] = {0, 0, 0, 0, 0};
//  PropSpec[0].ulKind = PRSPEC_PROPID;
//  PropSpec[0].propid = WIA_DPS_DOCUMENT_HANDLING_SELECT;
//  const ULONG c_nPropCount = sizeof(PropVariant)/sizeof(PropVariant[0]);

//  HRESULT hr = getWiaItemProperties(rootItem, c_nPropCount, PropSpec,
//                                    PropVariant);
//  if(SUCCEEDED(hr)){
//    doContinue = PropVariant[0].lVal & FEEDER;
//    for(uint i=0;i<c_nPropCount;i++)
//      LogDebug()<<"doContinue ="<<doContinue<<"lVal ="
//               <<(int)PropVariant[i].lVal<<"FEEDER ="<<FEEDER;
//  }

//  return doContinue;
//}
