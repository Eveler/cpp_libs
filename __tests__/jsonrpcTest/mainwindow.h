#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
  void on_tBt_Echo_clicked();

  void on_tBt_Add_clicked();

private:
  Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
