#ifndef MREPORTVIEWER_P_H
#define MREPORTVIEWER_P_H

#include <QObject>

#include "mreportviewer.h"

#include <QWebElement>


class MReportViewer_P : public QObject
{
  Q_OBJECT
  friend class MReportViewer;


public:


signals:


public slots:


private:
  explicit MReportViewer_P( MReportViewer *parent );

  MReportViewer * p_dptr() const;

  bool populate( MReportDocument *reportDocument ) const;
};

#endif // MREPORTVIEWER_P_H
