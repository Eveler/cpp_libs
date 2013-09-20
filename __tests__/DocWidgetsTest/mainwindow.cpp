#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "electrodoc_v2.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ElectroDoc_v2 *ed = new ElectroDoc_v2( this );
//    ed->setDocument( MFCDocument::instance( "Расписка МФЦ" ) );
    ed->setWindowFlags( Qt::Dialog );
    ed->setWindowModality( Qt::WindowModal );
    ed->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}
