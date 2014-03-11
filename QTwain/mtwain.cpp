#include "mtwain.h"
#include <QMessageBox>
#include <QFileInfo>
#include "gdiplus.h"

struct TwProtocol
{
  static const short Major = 1;
  static const short Minor = 9;
};

MTwain::MTwain(QObject *parent) :
  QObject(parent),
  libTWAIN(new QLibrary("twain_32", this))
{
  appid.Id = 0;
  appid.Version.MajorNum = 1;
  appid.Version.MinorNum = 1;
  appid.Version.Language = LanguageUSA;
  appid.Version.Country = CountryUSA;
  QByteArray str = "Version.Info";
  strncpy(appid.Version.Info, str.constData(), str.length());
  appid.ProtocolMajor = /*TWON_PROTOCOLMAJOR*/TwProtocol::Major;
  appid.ProtocolMinor = /*TWON_PROTOCOLMINOR*/TwProtocol::Minor;
  appid.SupportedGroups = (int)(DG_IMAGE | DG_CONTROL);
  str = "Manufacturer";
  strncpy(appid.Manufacturer, str.constData(), str.length());
  str = "Freeware";
  strncpy(appid.ProductFamily, str.constData(), str.length());
  str= "ProductName";
  strncpy(appid.ProductName, str.constData(), str.length());

  srcds.Id = 0;

  dsmParent = (DSMparent)libTWAIN->resolve("DSMparent");
  dsmIdent = (DSMident)libTWAIN->resolve("DSMident");
  dsUserif = (DSuserif)libTWAIN->resolve("DSuserif");
}

MTwain::~MTwain()
{
  finish();
  if(libTWAIN->isLoaded()) libTWAIN->unload();
  delete libTWAIN;
}

bool MTwain::init(HWND wnd)
{
  if(!dsmParent || !dsmIdent) return false;

  finish();

  int rc = dsmParent(appid, 0, DG_CONTROL, DAT_PARENT, MSG_OPENDSM, wnd);
  if(rc == TWRC_SUCCESS){
    {
      rc = dsmIdent(appid, 0, DG_CONTROL, DAT_IDENTITY, MSG_GETDEFAULT, &srcds);
      if(rc == TWRC_SUCCESS)
        hwnd = wnd;
      else{
        rc = dsmParent(appid, 0, DG_CONTROL, DAT_PARENT, MSG_CLOSEDSM, wnd);
        return false;
      }
    }
    return true;
  }

  return false;
}

void MTwain::finish()
{
  closeSrc();
  if(appid.Id != 0)
    /*int rc = */dsmParent(appid, 0, DG_CONTROL, DAT_PARENT, MSG_CLOSEDSM, hwnd);
  appid.Id = 0;
}

void MTwain::closeSrc()
{
  if(srcds.Id != 0){
    TW_USERINTERFACE guif;
    /*int rc = */dsUserif(appid, srcds, DG_CONTROL, DAT_USERINTERFACE, MSG_DISABLEDS, &guif);
    /*rc = */dsmIdent(appid, 0, DG_CONTROL, DAT_IDENTITY, MSG_CLOSEDS, &srcds);
  }
}

void MTwain::select()
{
  closeSrc();
  if(appid.Id == 0){
    init(hwnd);
    if(appid.Id == 0) return;
  }
  /*int rc = */dsmIdent(appid, 0, DG_CONTROL, DAT_IDENTITY, MSG_USERSELECT, &srcds);
}

bool MTwain::acquire()
{
  closeSrc();
  if(appid.Id == 0){
    init(hwnd);
    if(appid.Id == 0) return false;
  }
  int rc = dsmIdent(appid, 0, DG_CONTROL, DAT_IDENTITY, MSG_OPENDS, &srcds);
  if(rc != TWRC_SUCCESS){
    return false;
  }

  //TwCapability cap = new TwCapability(TwCap.XferCount, 1);
  TW_CAPABILITY cap;
  cap.Cap = CAP_XFERCOUNT;
  cap.ConType = TWON_ONEVALUE;
  cap.hContainer = GlobalAlloc(GHND,sizeof(TW_ONEVALUE))/*GlobalAlloc(0x42, 6)*/;
  pTW_ONEVALUE pv = (pTW_ONEVALUE)GlobalLock(cap.hContainer);
  pv->ItemType = TWTY_INT16;
  pv->Item = -1;
  rc = dsCap(appid, srcds, DG_CONTROL, DAT_CAPABILITY, MSG_SET, &cap);
  if(rc != TWRC_SUCCESS){
    closeSrc();
    return false;
  }

  TW_USERINTERFACE guif;
  guif.ShowUI = 1;
  guif.ModalUI = 1;
  guif.hParent = hwnd;
  rc = dsUserif(appid, srcds, DG_CONTROL, DAT_USERINTERFACE, MSG_ENABLEDS, &guif);
  if(rc != TWRC_SUCCESS){
    closeSrc();
    return false;
  }

  return true;
}

QList<HBITMAP> MTwain::transfer()
{
  QList<HBITMAP> pics;
  if (srcds.Id == 0) return pics;

  int rc = 0;
  HBITMAP hbitmap = 0;
  TW_PENDINGXFERS pxfr;

  do
  {
    pxfr.Count = 0;
    hbitmap = 0;

    TW_IMAGEINFO iinf;
    rc = dsIinf(appid, srcds, DG_IMAGE, DAT_IMAGEINFO, MSG_GET, &iinf);
    if(rc != TWRC_SUCCESS){
      closeSrc();
      return pics;
    }

    rc = dsIxfer(appid, srcds, DG_IMAGE, DAT_IMAGENATIVEXFER, MSG_GET, hbitmap);
    if(rc != TWRC_XFERDONE){
      closeSrc();
      return pics;
    }

    rc = dsPxfer(appid, srcds, DG_CONTROL, DAT_PENDINGXFERS, MSG_ENDXFER, &pxfr);
    if(rc != TWRC_SUCCESS){
      closeSrc();
      return pics;
    }

    pics<<hbitmap;
  }while(pxfr.Count != 0);

  rc = dsPxfer(appid, srcds, DG_CONTROL, DAT_PENDINGXFERS, MSG_RESET, &pxfr);
  return pics;
}

using namespace Gdiplus;
bool MTwain::saveImg(void *dibhandp, QString &fileName)
{
  void *dibhand = dibhandp;
  BITMAPINFO *bmpptr = (BITMAPINFO *)GlobalLock(dibhand);
  void *pixptr = getPixelInfo(bmpptr);

  CLSID clsid;
  if(!getCodecClsid(fileName, &clsid)){
    QMessageBox::warning(NULL, "Error", tr("Unknown picture format for %1").arg(fileName));
    return false;
  }

  Bitmap *bitmap = Bitmap::FromBITMAPINFO(bmpptr, pixptr);
  if(!bitmap){
    GlobalFree(dibhand);
    return false;
  }

  wchar_t *filename = new wchar_t[fileName.length()+1];
  fileName.toWCharArray(filename);
  Status st = bitmap->Save(filename, &clsid, NULL);
  if(st != Ok){
  }

  delete bitmap;

  GlobalFree(dibhand);
  dibhand = 0;
  return true;
}

void *MTwain::getPixelInfo(void *bmpptr)
{
  PBITMAPINFOHEADER bmi = (PBITMAPINFOHEADER)bmpptr;

  if(bmi->biSizeImage == 0)
      bmi->biSizeImage = ((((bmi->biWidth * bmi->biBitCount) + 31) & ~31) >> 3) * bmi->biHeight;

  int p = bmi->biClrUsed;
  if ((p == 0) && (bmi->biBitCount <= 8))
      p = 1 << bmi->biBitCount;
  p = (p * 4) + bmi->biSize + (int)bmpptr;
  return (void*)p;
}

bool MTwain::getCodecClsid(QString &filename, LPCLSID clsid)
{
  QFileInfo fi(filename);
  QString ext = fi.suffix();
  if(ext.isEmpty()) return false;
  ext = "*" + ext.toUpper();
  // Initialize GDI+.
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR           gdiplusToken;
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

  UINT  num;        // number of image encoders
  UINT  size;       // size, in bytes, of the image encoder array

  ImageCodecInfo* pImageCodecInfo;

  // How many encoders are there?
  // How big (in bytes) is the array of all ImageCodecInfo objects?
  GetImageEncodersSize(&num, &size);

  // Create a buffer large enough to hold the array of ImageCodecInfo
  // objects that will be returned by GetImageEncoders.
  pImageCodecInfo = (ImageCodecInfo*)(malloc(size));

  // GetImageEncoders creates an array of ImageCodecInfo objects
  // and copies that array into a previously allocated buffer.
  // The third argument, imageCodecInfos, is a pointer to that buffer.
  GetImageEncoders(num, size, pImageCodecInfo);

  // Display the graphics file format (MimeType)
  // for each ImageCodecInfo object.
  for(UINT j = 0; j < num; ++j)
  {
    ImageCodecInfo codec = pImageCodecInfo[j];
    QString fe;
    fe.fromWCharArray(codec.FilenameExtension);
    if(fe.indexOf(ext) >= 0){
      *clsid = codec.Clsid;
      return true;
    }
  }

  free(pImageCodecInfo);
  GdiplusShutdown(gdiplusToken);
  return false;
}
