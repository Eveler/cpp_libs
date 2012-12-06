#ifndef MFCWIDGET_H
#define MFCWIDGET_H

#include <QWidget>

class MFCWidget : public QWidget
{
  Q_OBJECT
public:
  explicit MFCWidget(QWidget *parent = 0);

signals:
  void windowStateChanged( Qt::WindowState wState );

public slots:
  void changeWindowState( Qt::WindowState wState );

protected:
  void changeEvent( QEvent *e );
};

#endif // MFCWIDGET_H
