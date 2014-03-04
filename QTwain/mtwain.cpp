#include "mtwain.h"

struct TwProtocol
{
  static const short Major = 1;
  static const short Minor = 9;
};

MTwain::MTwain(QObject *parent) :
  QObject(parent)
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
}

MTwain::~MTwain()
{

}
