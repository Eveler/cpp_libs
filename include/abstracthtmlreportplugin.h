#ifndef ABSTRACTHTMLREPORTPLUGIN_H
#define ABSTRACTHTMLREPORTPLUGIN_H

#include "export/htmlreport_export.h"
#include "htmlreport.h"
#include <QObject>
#include <QtPlugin>

#define setError(str) set_error(__FILE__,__LINE__,str)

class AbstractHtmlReportPlugin: public QObject
{
  Q_OBJECT
public:
  explicit AbstractHtmlReportPlugin(QObject * parent=0):
    QObject(parent),rep(new HtmlReport(this)){}
  ~AbstractHtmlReportPlugin(){delete rep;}

  virtual bool exec()=0;
  virtual HtmlReport *report(){return rep;}
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
