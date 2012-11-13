#ifndef PROPERTIESVIEW_H
#define PROPERTIESVIEW_H

#include <QObject>
#include "propertieslink.h"

class PropertiesView: public QObject
{
  Q_OBJECT
public:
  static PropertiesView * addPropertiesView( const QString &alias, Properties *root );
  static PropertiesView * getPropertiesView( const QString &alias );
  static bool exists( const QString &alias );
  static bool release( const QString &alias );
  static void releaseAll();

  bool isNull();

  const QString & alias() const;

  Properties * root() const;

//  bool addLink( Properties *parent, Properties *child,
//                const QString &parent_PropertyName, const QString &child_PropertyName,
//                const QStringList visible_PropertyNames );
//  bool removeLink( Properties *parent, Properties *child );
//  bool hasLink( const PropertiesLink &propertiesLink );
//  const QList<PropertiesLink *> & availableLinks();
//  PropertiesLink * findPropertiesLink( Properties *parent );
  bool addLink( PropertiesView *parent, PropertiesView *child,
                const QString &parent_PropertyName, const QString &child_PropertyName,
                const QStringList visible_PropertyNames );
  bool removeLink( PropertiesView *parent, PropertiesView *child );
  PropertiesLink * propertiesLink() const;
  PropertiesLink * findPropertiesLink( PropertiesView *parent ) const;
  QList<PropertiesLink *> availableLinks() const;

signals:
  void destroyedProperties( QString propertiesName );

private:
  static QList<PropertiesView *> m_PropertiesView;
  static PropertiesView nullPropertiesView;

  QString * m_Alias;
  QString m_RootName;
  Properties *m_Root;
//  QHash<QString, Properties *> m_UsedProperties;
//  QHash<QString, QList<QString> > m_Links;
//  QList<PropertiesLink *> m_PropertiesLinks;
  PropertiesLink *m_PropertiesLink;

  PropertiesView();
  PropertiesView( const QString &alias, Properties *root );
  ~PropertiesView();

//  void addLink( Properties *parent );

private slots:
  void propertiesDestroyed( QString propertiesName );
};

#endif // PROPERTIESVIEW_H
