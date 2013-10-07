#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "docmanager.h"


namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;

    Docmanager *docmanager;

  private slots:
    void loadedDocument( MFCDocumentInfo *doc );
    void storageError( QString text );
    void declarChanged();

    void on_toolButton_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
