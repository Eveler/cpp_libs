#include "QProgressIndicator.h"

#include <QPainter>
#include <qmath.h>

#include "macros.h"

QProgressIndicator::QProgressIndicator(QWidget* parent)
  : QWidget(parent),
  m_angle(0),
  m_timerId(-1),
  m_delay(40),
  m_displayedWhenStopped(false),
  m_color(Qt::black),
  m_Parts( 72 ),
  m_AnglePerLine( 360/m_Parts )
{
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  setFocusPolicy(Qt::NoFocus);
}

bool QProgressIndicator::isAnimated () const
{
  return (m_timerId != -1);
}

void QProgressIndicator::setDisplayedWhenStopped(bool state)
{
  m_displayedWhenStopped = state;

  update();
}

bool QProgressIndicator::isDisplayedWhenStopped() const
{
  return m_displayedWhenStopped;
}

void QProgressIndicator::startAnimation()
{
  m_angle = 0;

  if (m_timerId == -1)
    m_timerId = startTimer(m_delay);
}

void QProgressIndicator::stopAnimation()
{
  if (m_timerId != -1)
    killTimer(m_timerId);

  m_timerId = -1;

  update();
}

void QProgressIndicator::setAnimationDelay(int delay)
{
  if (m_timerId != -1)
    killTimer(m_timerId);

  m_delay = delay;

  if (m_timerId != -1)
    m_timerId = startTimer(m_delay);
}

void QProgressIndicator::setColor(const QColor & color)
{
  m_color = color;

  update();
}

QSize QProgressIndicator::sizeHint() const
{
  return QSize(20,20);
}

int QProgressIndicator::heightForWidth(int w) const
{
  return w;
}

void QProgressIndicator::timerEvent(QTimerEvent * /*event*/)
{
  m_angle = (m_angle+m_AnglePerLine)%360;

  update();
}

void QProgressIndicator::paintEvent(QPaintEvent * /*event*/)
{
  int width = qMin(this->width(), this->height());
  int outerRadius = (width-1)*0.5;
  int innerRadius = (width-1)*0.5*0.38;

  if ( path.isEmpty() )
  {

    DPRINT( "innerRadius" << innerRadius << "outerRadius" << outerRadius, qApp );

    path.moveTo( innerRadius, 0 );
    path.lineTo( outerRadius, 0 );

    qreal angle = (360.0f/(qreal)m_Parts)*(3.14f/180.0f);
    qreal l2_x1 = ((qreal)innerRadius*qCos(angle));
    qreal l2_y1 = (qreal)innerRadius*qSin(angle);
    qreal l2_x2 = ((qreal)outerRadius*qCos(angle));
    qreal l2_y2 = (qreal)outerRadius*qSin(angle);

    path.lineTo( l2_x2, l2_y2 );
    path.lineTo( l2_x1, l2_y1 );
    path.lineTo( innerRadius, 0 );
    path.closeSubpath();
  }

  if (!m_displayedWhenStopped && !isAnimated())
    return;

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  qreal t_pos = (qreal)outerRadius*.5-(qreal)innerRadius*.5;

  QRectF rf = QRectF( outerRadius-innerRadius*qCos(135*(3.14f/180.0f))+1,
                      outerRadius-innerRadius*qSin(135*(3.14f/180.0f)),
                      -innerRadius*qCos(-45*(3.14f/180.0f))*2,
                      -innerRadius*qSin(-45*(3.14f/180.0f))*2 );
  p.drawText( rf, "100%", QTextOption( Qt::AlignHCenter | Qt::AlignVCenter ) );

  for (int i=0; i<m_Parts; i++)
  {
    QColor color = m_color;
    qreal alpha = 1.0f - ((qreal)i/(qreal)m_Parts);
    if ( alpha < 0.3 ) alpha = .3;
    color.setAlphaF( alpha );
    QColor subColor = color;
    subColor.setRed( subColor.red()+150 );
    subColor.setGreen( subColor.green()+150 );
    subColor.setBlue( subColor.blue()+150 );
    subColor.setAlphaF( alpha-0.2 );
    p.setPen(subColor);
//    p.setPen(Qt::NoPen);
    QLinearGradient g;
    g.setStart( innerRadius, 0 );
    g.setFinalStop( outerRadius, 0 );
    subColor = color;
    subColor.setAlpha( alpha-0.3 );
    g.setColorAt( 0.0, subColor );
    subColor = color;
    g.setColorAt( 0.33, subColor );
    g.setColorAt( 0.6, subColor );
    subColor.setAlpha( alpha-0.3 );
    g.setColorAt( 1.0, subColor );
    p.setBrush( QBrush( g ) );
    p.save();
    QPoint translation = rect().center();
    translation.setX( translation.x()+1 );
    translation.setY( translation.y()+1 );
    p.translate(translation);
    p.rotate(m_angle - i*m_AnglePerLine);
    p.drawPath( path );
    p.restore();
  }
}
