#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MDclLock;
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_tBt_Echo_clicked();
  void on_tBt_Add_clicked();
  void showError(const QString &str);

private:
  Ui::MainWindow *ui;

  MDclLock *lock;
};

#endif // MAINWINDOW_H
