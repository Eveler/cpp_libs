#ifndef DOCPAGESVIEWER_H
#define DOCPAGESVIEWER_H

#include <QWidget>
#include <QPixmap>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QLabel>
#include <QList>
//#if QT_VERSION >= 0x050000
//#include <QtPrintSupport/QPrinter>
//#else
#include <QPrinter>
//#endif
#include <QPainter>
#include <QTimer>
#include "mfcdocument.h"
#include "docpagewidget.h"
//#include "macros.h"

class DocPagesViewer : public QScrollArea
{
  Q_OBJECT
public:
  explicit DocPagesViewer(QWidget *parent = 0);
  ~DocPagesViewer();
  int visiblePageNum() const;
//  void addPage();
//  void addPage(const QPixmap &pixmap);
//  void setPixmap(const int pageNum,const QPixmap &pixmap);
//  void removePage(const int pageNum);

protected:
  void paintEvent(QPaintEvent *e);
  bool eventFilter(QObject *obj, QEvent *e);

private:
  MFCDocument *doc;
  QWidget *scrollWgt;
  QVBoxLayout *vblPages;
  QList< DocPageWidget* > labels;
  QList< DocPageWidget* > visibleLabels;
  bool canUpdate;
  int lastVisibleLabelNum;
  int previousScaleValue;
//  qreal zoomFactor;
  QTimer *timer;
  int prevX;
  int prevY;
  void setPixmap(DocPageWidget *l);

signals:
  void pageBecomeVisible(int);
  void scaled(int);
  void progress(int,int);

private slots:
  void clear();

public slots:
  void timedOut();
  void documentChanged(MFCDocument *document);
  void scale(int percent);
  void scaleToViewWith();
  void setVisiblePage(int pageNum);
  void print(QPrinter* printer);
};

#endif // DOCPAGESVIEWER_H
