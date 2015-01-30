#ifndef ABSTRACTHTMLREPORTPLUGIN_H
#define ABSTRACTHTMLREPORTPLUGIN_H

#include "htmlreport.h"
#include "mfcdocumentinfo.h"
#include <QObject>
#include <QtPlugin>

struct HumanInfo
{
  QString surname;
  QString firstname;
  QString lastname;
  QString addr;
  QString phone;
  QString email;
  MFCDocumentInfo *passport;
};

typedef struct: public HumanInfo
{
  MFCDocumentInfo *trustee;
} TrusteeInfo;

typedef struct: public HumanInfo
{
  QString fullname;
  TrusteeInfo *trustee;
} ClientInfo;

typedef struct
{
  QString number;
  QString srvnum;
  QString srvname;
  QString orientir;
  HumanInfo *specialist;
  QDate indate;
  QDate outdate;
  bool isRespite;
} DeclarInfo;

class AbstractHtmlReportPlugin: public QObject
{
  Q_OBJECT
public:
  explicit AbstractHtmlReportPlugin(QObject * parent=0);
  ~AbstractHtmlReportPlugin();

  /// Возвращает имя отчёта
  virtual QStringList names() const=0;
  virtual bool select(const QString &name);
  /** Возвращает полное имя файла отчёта, которое сможет обработать
   *\a HtmlReport::load(). См. также \a name()
   */
  virtual QString fullName() const;
  virtual bool load();
  virtual HtmlReport *report();
//  virtual bool setData(const QString &reportName,
//                       const QList<ClientInfo> &clientList,
//                       const DeclarInfo &declar,
//                       const QList<MFCDocumentInfo*> docs=QList<MFCDocumentInfo*>());
  virtual bool setData(const QList<ClientInfo> &clientList,
                       const DeclarInfo &declar);
  // для расписки ************************************************************//
  virtual bool setData(
      const QList<ClientInfo> &clientList,
      const DeclarInfo &declar,
      const QList<MFCDocumentInfo*> &docs,
      const QList<MFCDocumentInfo*> docsNProvided=QList<MFCDocumentInfo*>(),
      const QList<MFCDocumentInfo*> outdocs=QList<MFCDocumentInfo*>());
  //************************************************************ для расписки //
  // для согласия ПДн ********************************************************//
  virtual bool setData(const ClientInfo &client, const DeclarInfo &declar);
  //******************************************************** для согласия ПДн //
  virtual bool setData(const QList<ClientInfo> &clientList,
                       const DeclarInfo &declar,
                       const QList<MFCDocumentInfo *> &docs,
                       const QString &resultWay,
                       const QList<MFCDocumentInfo *> docsNProvided,
                       const QList<MFCDocumentInfo *> outdocs);
  virtual QString lastError() const;

signals:
  void error(QString str);

protected:
  HtmlReport *rep;
  QString selected;
  QString errStr;

  void setclient(const QString &c);
  void setaddress(const QString &a);
  void setphone(const QString &p);
  void setemail(const QString &p);
  void setorientir(const QString &a);
  void setsign(const QString &s);
  void setdate(const QDate &d);
  void setdocument(MFCDocumentInfo *a);
  void set_error(const QString file,const int line,const QString str);
};

#define HtmlReportInterface_iid "org.m.htmlreports.plugins"

Q_DECLARE_INTERFACE(AbstractHtmlReportPlugin, HtmlReportInterface_iid)

#endif // ABSTRACTHTMLREPORTPLUGIN_H
