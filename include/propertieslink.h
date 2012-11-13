#ifndef PROPERTIESLINK_H
#define PROPERTIESLINK_H

#include "properties.h"

class LinkOptions
{
public:
//  LinkOptions( Properties *child, QString c_PropertyName,
//               QStringList visible_PropertyNames );
  LinkOptions( const QString &propertiesView_Alias, QString c_PropertyName,
               QStringList visible_PropertyNames );
  ~LinkOptions();

//  const QString & childName() const;
//  Properties * child() const;
  const QString & propertiesViewAlias() const;
  const QString & propertyName() const;
  const QStringList & visiblePropertyNames() const;

  bool isValid();

  bool operator ==( LinkOptions &otherLink );

private:
  QString m_PropViewAlias;
//  QString m_ChildName;
//  Properties *m_Child;
  QString m_PropertyName;
  QStringList m_VisiblePropertyNames;
};

class PropertiesLink
{
public:
//  PropertiesLink( const QString &propertiesView_Alias,
//                  Properties *parent );
  PropertiesLink( const QString &propertiesView_Alias );
  ~PropertiesLink();

  const QString & propertiesViewAlias() const;
//  const QString & parentName() const;
//  Properties * parent() const;
  bool isValid();

//  bool addLink( Properties *child,
//                QString p_PropertyName, QString c_PropertyName,
//                QStringList visible_PropertyNames );
  bool addLink( const QString &propertiesView_Alias,
                QString p_PropertyName, QString c_PropertyName,
                QStringList visible_PropertyNames );
  bool removeLink( QString p_PropertyName, LinkOptions *link );
  const QList<QPair<QString, LinkOptions *> > & availableLinks() const;

//  bool hasLinkOption( QString p_PropertyName, QString childName );
//  bool hasLinkOption( QString p_PropertyName, Properties *child );
  bool hasLinkOption( QString p_PropertyName, const QString &propertiesView_Alias );

//  QList<QPair<QString, LinkOptions *> > links( Properties *child );
  QList<QPair<QString, LinkOptions *> > links( const QString &propertiesView_Alias );
  QList<LinkOptions *> linksByParentProperty( QString p_PropertyName );

private:
  QString m_PropViewAlias;

//  QString m_ParentName;
//  Properties *m_Parent;

  QList<QPair<QString, LinkOptions *> > m_LinkOptions;
//  QHash<QString, Properties *> m_Children;
//  QHash<QString, QPair<QPair<QString, QString>, QStringList> > m_LinkedProperty;

  static bool validPropertiesLink( Properties *parent, Properties *child,
                                   QString p_PropertyName, QString c_PropertyName );

  Q_DISABLE_COPY( PropertiesLink )
};

#endif // PROPERTIESLINK_H
