#ifndef DBCATALOG_INTERFACE_H
#define DBCATALOG_INTERFACE_H

#include <QObject>

#include <QtPlugin>
#include <QWidget>


class DBCatalog_Interface: public QObject
{
  Q_OBJECT

public:
  explicit DBCatalog_Interface() {}
  ~DBCatalog_Interface()
  {
    while ( !m__Widgets.isEmpty() )
    {
      QWidget *widget = m__Widgets.takeFirst();
      disconnect( widget, SIGNAL(destroyed(QObject*)), this, SLOT(widgetDestroyed(QObject*)) );
      delete widget;
      widget = NULL;
    }
  }

  virtual QStringList categories() const = 0;

  const QList<QWidget *> & widgets() const {return m__Widgets;}


public slots:
  virtual QWidget * createWidget( QWidget *parentWidget = 0 ) = 0;


signals:
  void widgetCreated( QWidget *widget );


protected:
  void addWidget( QWidget *widget )
  {
    connect( widget, SIGNAL(destroyed(QObject*)), SLOT(widgetDestroyed(QObject*)) );
    m__Widgets << widget;
    emit widgetCreated( widget );
  }


private:
  QList<QWidget *> m__Widgets;


private slots:
  void widgetDestroyed( QObject *object )
  {
    QWidget *widget = (QWidget *)object;
    m__Widgets.removeOne( widget );
  }
};

#define DBCatalog_Interface_iid "m.dbcatalog.plugins"

Q_DECLARE_INTERFACE(DBCatalog_Interface, DBCatalog_Interface_iid)

#endif // DBCATALOG_INTERFACE_H
