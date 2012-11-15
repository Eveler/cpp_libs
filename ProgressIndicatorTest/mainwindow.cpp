#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  indicator = new QProgressIndicator( this );
  indicator->setMinimumSize( 100, 100 );
  ui->gridLayout->addWidget( indicator );
  indicator->setAnimationDelay( 15 );
  indicator->startAnimation();

//  this->setWindowOpacity( 0.8 );
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  QWidget::resizeEvent(event);

  QRect r = this->geometry();

  // делаем маску с закругленными краями под размер окна
  QPixmap pix(r.size());
  pix.fill(Qt::transparent);

  QPainter p(&pix);
  p.setBrush( Qt::black );

//  p.drawRoundedRect( r, 9, 9 );
  p.drawEllipse( QPointF(this->width()/2-0.5, this->height()/2-0.5), indicator->width()*0.5-1, indicator->height()*0.5-1 );

  setMask(pix.mask());
}
