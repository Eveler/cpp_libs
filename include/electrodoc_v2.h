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

namespace Ui {
class ElectroDoc_v2;
}

class DOCWIDGETSSHARED_EXPORT ElectroDoc_v2 : public MFCWidget
{
  Q_OBJECT
  Q_PROPERTY(bool m_modified READ isModified WRITE setModified)
  Q_ENUMS(Details)
public:
  enum Details{Type,Name,Series,Number,Date,ExpiresDate,Agency,CreateDate,Url};
  explicit ElectroDoc_v2(QWidget *parent = 0);
  ~ElectroDoc_v2();
  /// Наполнение справочников
  void setGuides(const QHash<QString,QStringList> &guides);
  /// Заполнение реквизитов
  bool setDetails(const QHash<QString,QVariant> &details);
  bool setDetails(const Details details,const QVariant val=QVariant());

  void setReadOnly(const bool readOnly=true);
  void setCanEditBody(const bool enabled=true);
  void setCanEditDetails(const bool enabled=true);
  void setCanEditAttachments(const bool enabled=true);
  void setCanJustClose(const bool can=true);
  bool setDocument(MFCDocument *document);
  MFCDocument *document() const;
  QString errorString();
  QString transliter(const QString &str);
  void setRestrictQuality(const bool r=true);
  void clear();
  bool isModified();
  void setModified(const bool m);
  QString detailsName(const Details details) const;
  QToolButton *tBt_RejectDocument();
  QToolButton *tBt_SaveDocument();

signals:
  void error(QString);
  void closed();
  void saveCompleted(bool,MFCDocument *);
  void rejected();

protected:
  void closeEvent(QCloseEvent *e);

private:
  enum ScanPageState {Scan_NULL=0,Scan_NewPage,Scan_ReplacePage};
  Ui::ElectroDoc_v2 *ui;
  QVBoxLayout *vblPages;
#ifdef Q_OS_WIN
  QProcess *scanProcess;
#endif
  ScanPageState scanState;
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

  void addPage(const QString &pName,const QPixmap &pixmap);
  void addAttachment(const QString fileName,const QString mimeType,
                     const QByteArray& fileData);
  bool replacePage(const int pageNum,const QPixmap &pixmap);
  void loadExtFile(const QString fName);
  void setScanState(ElectroDoc_v2::ScanPageState state);

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
  void readyReadScanProcessOutput();
#endif
  void loadImage();
  void loadAttachment();
  void doScan(ScanPageState state=Scan_NewPage);
  void scanNew();
  void scanReplace();
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

signals:
  void scaled(int);
};

#endif // ELECTRODOC_V2_H
