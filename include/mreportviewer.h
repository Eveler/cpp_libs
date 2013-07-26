#ifndef MREPORTVIEWER_H
#define MREPORTVIEWER_H

#include <QWidget>

#include "export/mwidgets_export_lib.h"
#include "mreportdocument.h"


namespace Ui {
class MReportViewer;
}

class MReportViewer_P;

class EXPORT_MWIDGETS MReportViewer : public QWidget
{
  Q_OBJECT
  friend class MReportViewer_P;


public:
  explicit MReportViewer(QWidget *parent = 0);
  ~MReportViewer();

  void exec( const QString &filePath );
  bool exec( MReportDocument *reportDocument );

  QString html() const;


signals:
  void progress( int current, int overall );


private:
  Ui::MReportViewer *ui;

  MReportViewer_P *p;


private slots:
  void reportProgress( int current, int overall );
};

#endif // MREPORTVIEWER_H
