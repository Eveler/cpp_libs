#ifndef ABSTRACTHTMLREPORTPLUGIN_H
#define ABSTRACTHTMLREPORTPLUGIN_H

#include "htmlreport.h"
#include "mfcdocumentinfo.h"
#include <QObject>
#include <QtPlugin>

#define setError(str) set_error(__FILE__,__LINE__,str)

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
} DeclarInfo;

class AbstractHtmlReportPlugin: public QObject
{
  Q_OBJECT
public:
  explicit AbstractHtmlReportPlugin(QObject * parent=0):
    QObject(parent),rep(new HtmlReport(this))
  {
    connect(rep,SIGNAL(error(QString)),this,SIGNAL(error(QString)));
  }
  ~AbstractHtmlReportPlugin(){delete rep;}

  /// Возвращает имя отчёта
  virtual QStringList names() const=0;
  bool select(const QString &name){
    if(!names().contains(name)) return false;
    selected = name;
    return true;
  }
  /** Возвращает полное имя файла отчёта, которое сможет обработать
   *\a HtmlReport::load(). См. также \a name()
   */
  virtual QString fullName() const {return "://"+selected+".html";}
  virtual bool load(){
    if(!rep->load(fullName())){
      setError(tr("Ошибка загрузки шаблона: %1").arg(rep->errorString()));
      return false;
    }
    return true;
  }
  virtual HtmlReport *report(){return rep;}
//  virtual bool setData(const QString &reportName,
//                       const QList<ClientInfo> &clientList,
//                       const DeclarInfo &declar,
//                       const QList<MFCDocumentInfo*> docs=QList<MFCDocumentInfo*>())
//  {
//    Q_UNUSED(reportName)
//    Q_UNUSED(clientList)
//    Q_UNUSED(declar)
//    Q_UNUSED(docs)
//    setError(tr("%1::setData(const QString &, const QList<ClientInfo> &, "
//                "const DeclarInfo &, const QList<MFCDocumentInfo*> &) "
//                "не реализовано")
//             .arg(metaObject()->className()));
//    return false;
//  }
  virtual bool setData(const QList<ClientInfo> &clientList,
                       const DeclarInfo &declar,
                       const QList<MFCDocumentInfo*> docs=QList<MFCDocumentInfo*>())
  {
    Q_UNUSED(clientList)
    Q_UNUSED(declar)
    Q_UNUSED(docs)
    setError(tr("%1::setData(const QList<ClientInfo> &, const DeclarInfo &, "
                "const QList<MFCDocumentInfo*> &) не реализовано")
             .arg(metaObject()->className()));
    return false;
  }
  // для расписки ************************************************************//
  virtual bool setData(
      const QList<ClientInfo> &clientList,
      const DeclarInfo &declar,
      const QList<MFCDocumentInfo*> &docs,
      const QList<MFCDocumentInfo*> docsNProvided=QList<MFCDocumentInfo*>(),
      const QList<MFCDocumentInfo*> outdocs=QList<MFCDocumentInfo*>())
  {
    Q_UNUSED(clientList)
    Q_UNUSED(declar)
    Q_UNUSED(docs)
    Q_UNUSED(docsNProvided)
    Q_UNUSED(outdocs)
    setError(tr("%1::setData(const QList<ClientInfo> &, const DeclarInfo &, "
                "const QList<MFCDocumentInfo*> &, "
                "const QList<MFCDocumentInfo*>, "
                "const QList<MFCDocumentInfo*>) не реализовано")
             .arg(metaObject()->className()));
    return false;
  }
  //************************************************************ для расписки //
  // для согласия ПДн ********************************************************//
  virtual bool setData(const ClientInfo &client,
                           const DeclarInfo &declar)
  {
    Q_UNUSED(client)
    Q_UNUSED(declar)
    setError(tr("%1::setData(const ClientInfo &, const DeclarInfo &) "
                "не реализовано")
             .arg(metaObject()->className()));
    return false;
  }
  //******************************************************** для согласия ПДн //
  virtual QString lastError() const{return errStr;}

signals:
  void error(QString str);

protected:
  HtmlReport *rep;
  QString selected;
  QString errStr;

  void set_error(const QString file,const int line,const QString str){
    errStr=tr("%1 (%2 [%3])").arg(str).arg(file).arg(line);
    emit error(errStr);
  }
};

#define HtmlReportInterface_iid "org.m.htmlreports.plugins"

Q_DECLARE_INTERFACE(AbstractHtmlReportPlugin, HtmlReportInterface_iid)

#endif // ABSTRACTHTMLREPORTPLUGIN_H
