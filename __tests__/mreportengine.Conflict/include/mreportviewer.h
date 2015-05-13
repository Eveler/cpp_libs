#ifndef MREPORTVIEWER_H
#define MREPORTVIEWER_H

#include <QWidget>

#include "mreportdocument.h"


namespace Ui {
class MReportViewer;
}

class MReportViewer_P;

class MReportViewer : public QWidget
{
  Q_OBJECT
  friend class MReportViewer_P;


public:
  explicit MReportViewer(QWidget *parent = 0);
  ~MReportViewer();

  void exec( const QString &filePath );
  bool exec( MReportDocument *reportDocument );

  const QString &html() const;


private:
  Ui::MReportViewer *ui;

  MReportViewer_P *p;
};

#endif // MREPORTVIEWER_H
