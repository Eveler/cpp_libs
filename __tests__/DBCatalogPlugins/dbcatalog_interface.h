#ifndef DBCATALOG_INTERFACE_H
#define DBCATALOG_INTERFACE_H

#include <QObject>

#include <QtPlugin>
#include <QWidget>


class DBCatalog_Interface: public QObject
{
  Q_OBJECT

public:
  explicit DBCatalog_Interface()
  {
    m__Widget = NULL;
  }

  ~DBCatalog_Interface()
  {
    delete m__Widget;
    disconnect( m__Widget, SIGNAL(destroyed()), this, SLOT(widgetDestroyed()) );
    m__Widget = NULL;
  }

  virtual QStringList categories() const = 0;

  QWidget * widget( QWidget *parentWidget = 0 )
  {
    if ( m__Widget == NULL )
    {
      m__Widget = createWidget( parentWidget );
      connect( m__Widget, SIGNAL(destroyed(QObject*)), SLOT(widgetDestroyed(QObject*)) );
    }

    return m__Widget;
  }


public slots:


private:
  QWidget *m__Widget;

  virtual QWidget * createWidget( QWidget *parentWidget ) = 0;


private slots:
  void widgetDestroyed()
  {
    m__Widget = NULL;
  }
};

#define DBCatalog_Interface_iid "m.dbcatalog.plugins"

Q_DECLARE_INTERFACE(DBCatalog_Interface, DBCatalog_Interface_iid)

#endif // DBCATALOG_INTERFACE_H
