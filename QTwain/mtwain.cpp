#include "mtwain.h"

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
