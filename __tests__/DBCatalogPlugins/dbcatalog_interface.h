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
    m__MainWidget = NULL;
  }

  ~DBCatalog_Interface()
  {
    disconnect( m__MainWidget, SIGNAL(destroyed()), this, SLOT(mainWidgetDestroyed()) );
    delete m__MainWidget;
    m__MainWidget = NULL;

    disconnect( m__ConfWidget, SIGNAL(destroyed()), this, SLOT(confWidgetDestroyed()) );
    delete m__ConfWidget;
    m__ConfWidget = NULL;
  }

  virtual QStringList categories() const = 0;

  QWidget * mainWidget( QWidget *parentWidget = 0 )
  {
    if ( m__MainWidget == NULL )
    {
      m__MainWidget = createMainWidget( parentWidget );
      connect( m__MainWidget, SIGNAL(destroyed()), SLOT(mainWidgetDestroyed()) );
    }

    return m__MainWidget;
  }

  QWidget * configurationWidget( QWidget *parentWidget = 0 )
  {
    if ( m__ConfWidget == NULL )
    {
      m__ConfWidget = createMainWidget( parentWidget );
      connect( m__ConfWidget, SIGNAL(destroyed()), SLOT(confWidgetDestroyed()) );
    }

    return m__ConfWidget;
  }


public slots:


private:
  QWidget *m__MainWidget;
  QWidget *m__ConfWidget;

  virtual QWidget * createMainWidget( QWidget *parentWidget ) = 0;
  virtual QWidget * createConfWidget( QWidget *parentWidget ) = 0;


private slots:
  void mainWidgetDestroyed()
  {
    m__MainWidget = NULL;
  }

  void confWidgetDestroyed()
  {
    m__ConfWidget = NULL;
  }
};

#define DBCatalog_Interface_iid "m.dbcatalog.plugins"

Q_DECLARE_INTERFACE(DBCatalog_Interface, DBCatalog_Interface_iid)

#endif // DBCATALOG_INTERFACE_H
