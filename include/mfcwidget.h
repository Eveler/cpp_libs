#ifndef MFCWIDGET_H
#define MFCWIDGET_H

#include <QWidget>
#include "export/docwidgets_export.h"

class DOCWIDGETSSHARED_EXPORT MFCWidget : public QWidget
{
  Q_OBJECT
public:
  explicit MFCWidget(QWidget *parent = 0);
  bool canClose() const;

signals:
  void windowStateChanged( Qt::WindowState wState );

public slots:
  void changeWindowState( Qt::WindowState wState );
  void setCanClose( bool can = true );

protected:
  void changeEvent( QEvent *e );
  void closeEvent( QCloseEvent *e );

private:
  bool m__CanClose;
};

#endif // MFCWIDGET_H
