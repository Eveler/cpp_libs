#ifndef ELECTRODOC_V2_H
#define ELECTRODOC_V2_H

#include <QWidget>
#include <QVBoxLayout>
#include <QProcess>
//#if QT_VERSION >= 0x050000
//#include <QtPrintSupport/QPrinter>
//#include <QtPrintSupport/QPrintPreviewDialog>
//#else
#include <QPrinter>
#include <QPrintPreviewDialog>
//#endif
#include <QFileSystemWatcher>
#include <QToolButton>
#include "mfcwidget.h"
#include "mfcdocument.h"
//#include "macros.h"
#include "docpagesviewer.h"
#include "export/docwidgets_export.h"

#ifdef Q_OS_WIN
#include "qtwaininterface.h"
#include "qtwain.h"
#include "dib.h"
#endif

#include <QEventLoop>


namespace Ui {
class ElectroDoc_v2;
}

class DOCWIDGETSSHARED_EXPORT ElectroDoc_v2 : public MFCWidget
{
  Q_OBJECT
  Q_PROPERTY(bool m_modified READ isModified WRITE setModified)
  Q_ENUMS(Details)
public:
  enum Details{Type,Name,Series,Number,Date,ExpiresDate,Agency,CreateDate};
  enum State { Create = 0, Read, Check, Copy, CopyCreate };
  explicit ElectroDoc_v2(QWidget *parent = 0);
  ~ElectroDoc_v2();
  /// Заполнение реквизитов
  bool setDetails(const Details details,const QVariant val=QVariant());

  void setState( State state = Create );
  bool setDocument(MFCDocument *document);
  MFCDocument *document() const;
  QString errorString();
  QString transliter(const QString &str);
  void setRestrictQuality(const bool r=true);
  void clear();
  bool isModified();
  void setModified(const bool m);
  QString detailsName(const Details details) const;

  int exec( bool maximized = true );

signals:
  void error(QString);
  void closed();
  void saveCompleted(bool,MFCDocument *);
  void rejected();

protected:
  void closeEvent(QCloseEvent *e);
#ifdef Q_OS_WIN
  bool nativeEvent(const QByteArray &eventType, void *message, long *result);
  bool winEvent( MSG *message, long */*result*/ );
#endif

private:
  Ui::ElectroDoc_v2 *ui;
  State m__State;
  QVBoxLayout *vblPages;
#ifdef Q_OS_WIN
  QPixmap *m_pPixmap;
  QTwainInterface *m_pTwain;
#endif
  MFCDocument *m_Document;
  MFCDocument *originalDocument;
  int previousScaleValue;
  QString errStr;
  bool restrictQuality;
  DocPagesViewer *viewer;
  bool m_modified;
  bool saved;
  QString title;
  QFileSystemWatcher *fWatcher;
  bool isReadOnly;
  QString tmpFileName;
  bool canJustClose;
  int loopResult;
  QEventLoop *loop;

  void setReadOnly(const bool readOnly=true);

  void addPage(const QString &pName,const QPixmap &pixmap);
  void addAttachment(const QString fileName,const QString mimeType,
                     const QByteArray& fileData);
  bool replacePage(const int pageNum,const QPixmap &pixmap);
  void loadExtFile(const QString fName);

#ifdef Q_OS_WIN
  void initTWAIN();
  void releaseTWAIN();
#endif


public slots:
  void showProgress(qint64 done,qint64 total);

private slots:
//  void animationStoped();
  void scale(int value);
  void fitToWith();
  void scaleToOriginal();
  void zoomIn();
  void zoomOut();
#ifdef Q_OS_WIN
  void scannerConfigTriggered();
  void scannerStart();
  void pixmapAcquired( QPixmap *pix );
#endif
  void loadImage();
  void loadAttachment();
  void setVisiblePage(int pageNum);
  void movePage(const int from,const int to);
  void moveCurrentPageUp();
  void moveCurrentPageDown();
  void removeCurrentPage();
  void removeSelectedAttachments();
  void rotate(const int angle);
  void rotateLeft();
  void rotateRight();
  void saveToFile();
  void print();
  void doPrint(QPrinter *printer);
  void save();
  void confirm();
  void reject();
  void fileChanged(QString fName);
  void openAttachment();
  void setError(const QString &str);

  void on_tBt_DateTo_clicked();

  void on_tBt_ExpiresTo_clicked();

  void on_tBt_ExpiresClear_clicked();

  signals:
  void scaled(int);
};

#endif // ELECTRODOC_V2_H
