#ifndef ABSTRACTHTMLREPORTPLUGIN_H
#define ABSTRACTHTMLREPORTPLUGIN_H

//#include "export/htmlreport_export.h"
#include "htmlreport.h"
#include "mfcdocumentinfo.h"
#include <QObject>
#include <QtPlugin>

#define setError(str) set_error(__FILE__,__LINE__,str)

typedef struct/*class TInfo*/
{
  QString surname;
  QString firstname;
  QString lastname;
  QString addr;
  QString phone;
  QString email;
  MFCDocumentInfo *passport;
  MFCDocumentInfo *trustee;
//  TInfo():passport(NULL),trustee(NULL){}
} TrusteeInfo;

typedef struct
{
  QString fullname;
  QString surname;
  QString firstname;
  QString lastname;
  QString addr;
  QString phone;
  QString email;
  TrusteeInfo *trustee;
  MFCDocumentInfo *passport;
} ClientInfo;

typedef struct
{
  QString number;
  QString srvnum;
  QString srvname;
  QString orientir;
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
  virtual QString name() const=0;
  /** Возвращает полное имя файла отчёта, которое сможет обработать
   *\a HtmlReport::load(). См. также \a name()
   */
  virtual QString fullName() const {return "://"+name()+".html";}
  virtual bool load(){
    if(!rep->load(fullName())){
      setError(tr("Ошибка загрузки шаблона: %1").arg(rep->errorString()));
      return false;
    }
    return true;
  }
  virtual HtmlReport *report(){return rep;}
  virtual bool setData(const QList<ClientInfo> &clientList,
                           const DeclarInfo &declar,
                           const QList<MFCDocumentInfo*> &docs)
  {
    Q_UNUSED(clientList)
    Q_UNUSED(declar)
    Q_UNUSED(docs)
    setError(tr("%1::setData(const QList<ClientInfo> &, const DeclarInfo &, "
                "const QList<MFCDocumentInfo*> &) не реализовано")
             .arg(metaObject()->className()));
    return false;
  }
  virtual bool setData(
      const QList<ClientInfo> &clientList,
      const DeclarInfo &declar,
      const QList<MFCDocumentInfo*> &docs,
      const QList<MFCDocumentInfo*> docsNProvided=QList<MFCDocumentInfo*>(),
      const QList<MFCDocumentInfo*> outdocs=QList<MFCDocumentInfo*>()) // для расписки
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
  virtual bool setData(const ClientInfo &client,
                           const DeclarInfo &declar) // для согласия ПДн
  {
    Q_UNUSED(client)
    Q_UNUSED(declar)
    setError(tr("%1::setData(const ClientInfo &, const DeclarInfo &) "
                "не реализовано")
             .arg(metaObject()->className()));
    return false;
  }
  virtual QString lastError() const{return errStr;}

signals:
  void error(QString str);

protected:
  HtmlReport *rep;
  QString errStr;

  void set_error(const QString file,const int line,const QString str){
    errStr=tr("%1 (%2 [%3])").arg(str).arg(file).arg(line);
    emit error(errStr);
  }
};

#define HtmlReportInterface_iid "org.m.htmlreports.plugins"

Q_DECLARE_INTERFACE(AbstractHtmlReportPlugin, HtmlReportInterface_iid)

#endif // ABSTRACTHTMLREPORTPLUGIN_H
