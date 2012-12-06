#ifndef MFCMAINWONDOW_H
#define MFCMAINWONDOW_H

#include <QMainWindow>

class MFCMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MFCMainWindow(QWidget *parent = 0);

signals:
  void windowStateChanged( Qt::WindowState wState );

public slots:
  void changeWindowState( Qt::WindowState wState );

protected:
  void changeEvent( QEvent *e );

};

#endif // MFCMAINWONDOW_H
