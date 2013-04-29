#ifndef MREPORTVIEWER_P_H
#define MREPORTVIEWER_P_H

#include <QObject>

#include "mreportviewer.h"


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
};

#endif // MREPORTVIEWER_P_H
