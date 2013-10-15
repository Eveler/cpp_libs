#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "docmanager.h"
#include "clientinfoloader.h"
#include "docpathsinfoloader.h"

#include <QProgressBar>


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
    QProgressBar *pBar;

    Docmanager *docmanager;
    ClientInfoLoader *clientInfoLoader;
    DocpathsInfoLoader *docpathsInfoLoader;


  private slots:
    void error( QString text );
    void declarChanged();
    void progress( qint64 cur, qint64 all );
    void clientInfoLoaded( QString fio, QString phone, QString address, QVariant id );
    void docpathInfoLoaded( QVariant id );

    void on_toolButton_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_tBt_AddDeclarDoc_clicked();
    void on_tBt_CheckDeclarDoc_clicked();
    void on_lWgt_Steps_currentRowChanged( int currentRow);
};

#endif // MAINWINDOW_H
