#include "docpagesviewer.h"
#include <QImageReader>
#include <QRegion>
#include <QDebug>
#include <QApplication>
#include <QScrollBar>

DocPagesViewer::DocPagesViewer(QWidget *parent) :
  QScrollArea(parent)
{
//  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

  setWidgetResizable(true);
  doc=NULL;
  scrollWgt=new QWidget(this);
  installEventFilter(scrollWgt);
  vblPages=new QVBoxLayout(this);
  vblPages->setSpacing(9);
  scrollWgt->setLayout(vblPages);
  setWidget(scrollWgt);
  scrollWgt->show();
  prevX=0;
  prevY=0;

  labels=QList< DocPageWidget* >();
  visibleLabels=QList< DocPageWidget* >();
  canUpdate=true;
  lastVisibleLabelNum=0;
  previousScaleValue=100;
  timer=new QTimer(this);
  timer->setSingleShot(true);
  connect(timer,SIGNAL(timeout()),this,SLOT(timedOut()));
}

DocPagesViewer::~DocPagesViewer(){
  clear();
  delete scrollWgt;
  delete timer;
}

int DocPagesViewer::visiblePageNum() const{
  return lastVisibleLabelNum;
}

void DocPagesViewer::paintEvent(QPaintEvent *e){
  canUpdate=false;
  int pNum=0;
  if(timer->isActive()) timer->stop();

  visibleLabels.clear();
  foreach(DocPageWidget *l,labels){
    if(!l->visibleRegion().isEmpty()){
      visibleLabels<<l;
      lastVisibleLabelNum=pNum;
      if((l->pixmap()==0 || l->pixmap()->isNull()) && l->text().isEmpty())
        l->setText(tr("<h1>Загрузка...</h1>"));
    }
    pNum++;
  }

  emit pageBecomeVisible(lastVisibleLabelNum);
  timer->start(70);

  QScrollArea::paintEvent(e);
  canUpdate=true;
}

bool DocPagesViewer::eventFilter(QObject *obj, QEvent *e){
  if(obj==scrollWgt){
    if(e->type()==QEvent::Paint){
      if(canUpdate) paintEvent(static_cast< QPaintEvent * >(e));
      return true;
    }
    if(e->type()==QEvent::MouseButtonPress){
      QMouseEvent *me=static_cast< QMouseEvent* >(e);
      if(me->button()==Qt::LeftButton)
        scrollWgt->setCursor(Qt::OpenHandCursor);
      prevX=me->globalX();
      prevY=me->globalY();
    }
    if(e->type()==QEvent::MouseButtonRelease){
      scrollWgt->setCursor(Qt::ArrowCursor);
    }
    if(e->type()==QEvent::MouseMove){
      if(doc==NULL || !doc->havePages()) return false;
      QMouseEvent *me=static_cast< QMouseEvent* >(e);
      if(me->buttons().testFlag(Qt::LeftButton)){
        horizontalScrollBar()->setValue(
              horizontalScrollBar()->value()-me->globalX()+prevX);
        verticalScrollBar()->setValue(
              verticalScrollBar()->value()-me->globalY()+prevY);
        prevX=me->globalX();
        prevY=me->globalY();
      }
    }
  }
  return false;
}

void DocPagesViewer::setPixmap(DocPageWidget *l){
  if(doc==NULL || !doc->havePages()) return;
  if(labels.count()==0) return;
  if(l->pixmap()!=0 && !l->pixmap()->isNull()) return;
  int p=labels.indexOf(l);
  if(p<0) return;
  QPixmap imgData;
  MFCDocumentPages *docPages=doc->pages();
  MFCDocumentPage* pg=docPages->getPage(p);
  imgData.loadFromData(pg->getBody());
  if(previousScaleValue!=100)
    imgData=imgData.scaled(previousScaleValue*imgData.width()/100,
                           previousScaleValue*imgData.height()/100,
                           Qt::KeepAspectRatio,Qt::SmoothTransformation);
  if(l->minimumHeight()!=imgData.height()){
    l->setMinimumSize(imgData.size());
    l->setMaximumSize(imgData.size());
  }
  l->clear();
  l->setPixmap(imgData);
}

void DocPagesViewer::clear(){
  foreach(DocPageWidget *l,labels) delete l;
  labels.clear();
}

void DocPagesViewer::timedOut(){
  if(!canUpdate) return;
  if(visibleLabels.count()==0) return;
  int p=0;
  foreach(DocPageWidget *l,labels){
    if(visibleLabels.contains(l) ||
       (p>=labels.indexOf(visibleLabels.first())-2 &&
        p<=labels.indexOf(visibleLabels.last())+2)){
      if(l->pixmap()==0 || l->pixmap()->isNull()){
        l->clear();
        setPixmap(l);
      }
    }else if(l->pixmap()!=0) l->setPixmap(0);
    p++;
  }
}

void DocPagesViewer::documentChanged(MFCDocument *document){
  if(document==NULL) return;
  doc=document;
  clear();
  if(doc->havePages()){
    MFCDocumentPages *docPages=doc->pages();
    for(int p=0;p<docPages->count();p++){
      MFCDocumentPage* pg=docPages->getPage(p);
      DocPageWidget *l=new DocPageWidget(this);
      l->setAlignment(Qt::AlignTop);
      l->setStyleSheet("border: 3px solid gray; border-radius: 4px");
      pg->device()->seek(0);
      QImageReader reader(pg->device());
      if(reader.canRead()){
        l->setMinimumSize(QSize(previousScaleValue*reader.size().width()/100,
                                previousScaleValue*reader.size().height()/100));
        l->setMaximumSize(QSize(previousScaleValue*reader.size().width()/100,
                                previousScaleValue*reader.size().height()/100));
      }
      vblPages->addWidget(l,0,Qt::AlignHCenter);
      labels<<l;
    }
  }
}

void DocPagesViewer::scale(int percent){
  if(previousScaleValue==percent) return;
  previousScaleValue = percent;
  emit scaled(previousScaleValue);
  documentChanged(doc);
}

void DocPagesViewer::scaleToViewWith(){
  MFCDocumentPages *docPages=doc->pages();
  MFCDocumentPage* pg=docPages->getPage(lastVisibleLabelNum);
  pg->device()->seek(0);
  QImageReader reader(pg->device());
  int factor=100.0/(((qreal)reader.size().width()+3*reader.size().width()/100)/
                    (qreal)this->visibleRegion().boundingRect().width());
  scale(factor);
}

void DocPagesViewer::setVisiblePage(int pageNum){
  if(pageNum<0 || labels.count()==0 || pageNum>labels.count() ||
     pageNum==lastVisibleLabelNum)
    return;
  ensureVisible(labels.value(pageNum)->geometry().x(),
                labels.value(pageNum)->geometry().y()+
                visibleRegion().boundingRect().height()-
                10*visibleRegion().boundingRect().height()/100,1,1);
}

void DocPagesViewer::print(QPrinter *printer){
  if(!doc->havePages()) return;
  QPainter painter;
  int count=doc->pages()->count();

  // если на какой либо странице есть выделение - печатаем его
  // находим коэф масштабирования из размеров DocPageWidget
  int selectionCount=0;
  foreach(DocPageWidget *l,labels)
    if(l->hasSelection()) selectionCount++;
  painter.begin(printer);
  int s=0;
  for(int p=0;p<count;p++){
    DocPageWidget *l=labels.value(p);
    if(l==NULL){
      painter.end();
      return;
    }
    if(l->hasSelection()){
      qreal factor=(qreal)100/previousScaleValue;
      QRect selection(factor*l->selectionRect().x(),
                      factor*l->selectionRect().y(),
                      factor*l->selectionRect().width(),
                      factor*l->selectionRect().height());
      QPixmap pix1=QPixmap();
      pix1.loadFromData(doc->pages()->getPage(p)->getBody());
      QPixmap pix=QPixmap();
      pix=pix1.copy(selection);
      pix=pix.scaled(printer->pageRect().size(),Qt::KeepAspectRatio,
                     Qt::SmoothTransformation);
      painter.drawPixmap(0,0,pix);
      if(s<selectionCount-1) printer->newPage();
      s++;
      emit progress(s,selectionCount);
      qApp->processEvents();
    }
  }
  painter.end();

  if(selectionCount==0){
    painter.begin(printer);
    for(int p=0;p<count;p++){
      QPixmap pix=QPixmap();
      pix.loadFromData(doc->pages()->getPage(p)->getBody());
      pix=pix.scaled(printer->pageRect().size(),Qt::KeepAspectRatio,
                     Qt::SmoothTransformation);
      painter.drawPixmap(0,0,pix);
      if(p<count-1) printer->newPage();
      emit progress(p,count);
      qApp->processEvents();
    }
    painter.end();
  }
}
