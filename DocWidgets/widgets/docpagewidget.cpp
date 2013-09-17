#include "docpagewidget.h"
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

DocPageWidget::DocPageWidget(QWidget *parent) :
  QLabel(parent),selection(QRect()),isOriginalPixmap(false),isSelected(false),prevX(0),prevY(0)
{
}

bool DocPageWidget::hasSelection() const{
  return selection.width()>0 && selection.height()>0;
}

QRect DocPageWidget::selectionRect() const{
  return selection;
}

void DocPageWidget::setPixmap(const QPixmap &p){
  pixm=p;
  isOriginalPixmap=true;
  QLabel::setPixmap(p);
}

void DocPageWidget::paintEvent(QPaintEvent *pe){
  if(pixmap()==0 || pixmap()->isNull()){
    pixm=QPixmap();
    QLabel::paintEvent(pe);
    return;
  }

  if(selection.width()>0 && selection.height()>0 && !isSelected){
    QPixmap pix=pixm;
    QPainter painter(&pix);
    QPen pen(Qt::red);
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawRect(selection);
    QLabel::setPixmap(pix);
    isSelected=true;
    emit selectionChanged(selection);
    pe->ignore();
  }else if(!isOriginalPixmap){
    setPixmap(pixm);
  }

  QLabel::paintEvent(pe);
}

void DocPageWidget::mouseMoveEvent(QMouseEvent *ev){
  if(ev->buttons().testFlag(Qt::MiddleButton)){
    if(selection.width()+ev->x()-prevX>0)
      selection.setWidth(selection.width()+ev->x()-prevX);
    else{
      selection.setLeft(ev->x());
      selection.setWidth(selection.width()+prevX-ev->x());
    }
    if(selection.height()+ev->y()-prevY>0)
      selection.setHeight(selection.height()+ev->y()-prevY);
    else{
      selection.setTop(ev->y());
      selection.setHeight(selection.height()+prevY-ev->y());
    }
    prevX=ev->x();
    prevY=ev->y();
    isSelected=false;
    ev->accept();
    paintEvent(new QPaintEvent(visibleRegion()));
  }else ev->ignore();
}

void DocPageWidget::mousePressEvent(QMouseEvent *ev){
  if(ev->button()==Qt::MiddleButton){
    prevX=ev->x();
    prevY=ev->y();
    setCursor(Qt::CrossCursor);
    selection=QRect(ev->x(),ev->y(),0,0);
    ev->accept();
    paintEvent(new QPaintEvent(visibleRegion()));
  }else if(ev->button()==Qt::LeftButton){
    setCursor(Qt::OpenHandCursor);
    ev->ignore();
  }else ev->ignore();
}

void DocPageWidget::mouseReleaseEvent(QMouseEvent *ev){
  setCursor(Qt::ArrowCursor);
  if(selection.width()==0 || selection.height()==0){
    selection=QRect();
    isOriginalPixmap=false;
    paintEvent(new QPaintEvent(visibleRegion()));
  }
  ev->ignore();
}
