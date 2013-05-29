#ifndef DOCPAGEWIDGET_H
#define DOCPAGEWIDGET_H

#include <QLabel>

class DocPageWidget : public QLabel
{
  Q_OBJECT
public:
  explicit DocPageWidget(QWidget *parent = 0);
  bool hasSelection() const;
  QRect selectionRect() const;
  void setPixmap(const QPixmap &p);

protected:
  void paintEvent(QPaintEvent *pe);
  void mouseMoveEvent(QMouseEvent *ev);
  void mousePressEvent(QMouseEvent *ev);
  void mouseReleaseEvent(QMouseEvent *ev);

signals:
  void selectionChanged(QRect);

protected:
  QRect selection;
  QPixmap pixm;
  bool isOriginalPixmap;
  bool isSelected;
  int prevX;
  int prevY;
};

#endif // DOCPAGEWIDGET_H
