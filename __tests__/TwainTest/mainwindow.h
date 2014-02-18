#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtwain.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();
  void pixmapAcquired(QPixmap*pix);
  void on_pushButton_2_clicked();

private:
  Ui::MainWindow *ui;
  QTwain *m_pTwain;

  bool nativeEvent( const QByteArray &eventType, void *message, long *result );
  bool winEvent( MSG *message, long */*result*/ );
  void initTWAIN();
  void releaseTWAIN();
};

#endif // MAINWINDOW_H
