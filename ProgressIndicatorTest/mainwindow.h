#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QProgressIndicator/QProgressIndicator.h"
#include <QResizeEvent>
#include <QPainter>
#include <QBitmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected:
  void resizeEvent(QResizeEvent *event);

private:
  Ui::MainWindow *ui;

  QProgressIndicator *indicator;
};

#endif // MAINWINDOW_H
