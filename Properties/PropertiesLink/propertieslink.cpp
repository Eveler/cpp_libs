#include "propertieslink.h"
#include "propertiesview.h"
#include <QDebug>

//LinkOptions::LinkOptions( Properties *child, QString c_PropertyName,
//                          QStringList visible_PropertyNames )
//{
//  m_ChildName = child->name();
//  m_Child = child;
//  m_PropertyName = c_PropertyName;
//  m_VisiblePropertyNames = visible_PropertyNames;

//  if ( !isValid() )
//  {
//    m_ChildName = QString();
//    m_Child = 0;
//    m_PropertyName = QString();
//    m_VisiblePropertyNames = QStringList();
//  }
//}

LinkOptions::LinkOptions( const QString &propertiesView_Alias,
                          QString c_PropertyName, QStringList visible_PropertyNames ) :
  m_PropViewAlias( propertiesView_Alias ),
  m_PropertyName( c_PropertyName ),
  m_VisiblePropertyNames( visible_PropertyNames )
{
  if ( !isValid() )
  {
    m_PropViewAlias = QString();
    m_PropertyName = QString();
    m_VisiblePropertyNames = QStringList();
  }
}

LinkOptions::~LinkOptions()
{
}

//const QString & LinkOptions::childName() const
//{
//  return m_ChildName;
//}

//Properties * LinkOptions::child() const
//{
//  return m_Child;
//}

const QString & LinkOptions::propertiesViewAlias() const
{
  return m_PropViewAlias;
}

const QString & LinkOptions::propertyName() const
{
  return m_PropertyName;
}

const QStringList & LinkOptions::visiblePropertyNames() const
{
  return m_VisiblePropertyNames;
}

//bool LinkOptions::isValid()
//{
//  return ( !m_ChildName.isEmpty() && m_Child != 0 && m_Child->propertyNames().contains( m_PropertyName ) );
//}

bool LinkOptions::isValid()
{
  Properties *parentPs = PropertiesView::getPropertiesView( m_PropViewAlias )->root();
  return ( parentPs != 0 && parentPs->propertyNames().contains( m_PropertyName ) );
}

//bool LinkOptions::operator ==( LinkOptions &otherLink )
//{
//  return ( childName() == otherLink.childName() && child() == otherLink.child() &&
//           visiblePropertyNames() == otherLink.visiblePropertyNames() );
//}

bool LinkOptions::operator ==( LinkOptions &otherLink )
{
  return ( propertiesViewAlias() == otherLink.propertiesViewAlias() &&
           propertyName() == otherLink.propertyName() &&
           visiblePropertyNames() == otherLink.visiblePropertyNames() );
}


//PropertiesLink::PropertiesLink( const QString &propertiesView_Alias, Properties *parent ) :
//  m_PropViewAlias( propertiesView_Alias ),
//  m_ParentName()
//{
//  if ( parent != 0 )
//  {
//    m_ParentName = parent->name();
//    m_Parent = parent;
//  }
//  else m_Parent = 0;
//  m_LinkOptions = QList<QPair<QString, LinkOptions *> >();
////  m_Children = QHash<QString, Properties *>();
////  m_LinkedProperty = QHash<QString, QPair<QPair<QString, QString>, QStringList> >();
//}

PropertiesLink::PropertiesLink( const QString &propertiesView_Alias ) :
  m_PropViewAlias( propertiesView_Alias )
{
  m_LinkOptions = QList<QPair<QString, LinkOptions *> >();
}

PropertiesLink::~PropertiesLink()
{
  while( !m_LinkOptions.isEmpty() )
  {
    QPair<QString, LinkOptions *> link = m_LinkOptions.takeFirst();
    delete link.second;
  }

//  m_Children.clear();
//  m_LinkedProperty.clear();
}

const QString & PropertiesLink::propertiesViewAlias() const
{
  return m_PropViewAlias;
}

//const QString & PropertiesLink::parentName() const
//{
//  return m_ParentName;
//}

//Properties * PropertiesLink::parent() const
//{
//  return m_Parent;
//}

//bool PropertiesLink::isValid()
//{
//  bool result = ( !PropertiesView::getPropertiesView( m_PropViewAlias )->isNull() &&
//                  PropertiesView::getPropertiesView( m_PropViewAlias )->hasLink( *this ) &&
//                  !m_ParentName.isEmpty() && m_Parent != 0 );
//  if ( result )
//    for ( int linkIdx = 0; linkIdx < m_LinkOptions.count(); linkIdx++ )
//      if ( !m_Parent->propertyNames().contains( m_LinkOptions[linkIdx].first ) ||
//           !m_LinkOptions[linkIdx].second->isValid() )
//      {
//        result = false;
//        break;
//      }
//  return result;
//}

bool PropertiesLink::isValid()
{
  bool result = ( !PropertiesView::getPropertiesView( m_PropViewAlias )->isNull() &&
                  PropertiesView::getPropertiesView( m_PropViewAlias )->propertiesLink() == this );
  if ( result )
  {
    Properties *parentPs = PropertiesView::getPropertiesView( m_PropViewAlias )->root();
    for ( int linkIdx = 0; linkIdx < m_LinkOptions.count(); linkIdx++ )
      if ( !parentPs->propertyNames().contains( m_LinkOptions[linkIdx].first ) ||
           !m_LinkOptions[linkIdx].second->isValid() )
      {
        result = false;
        break;
      }
  }
  return result;
}

//bool PropertiesLink::addLink( Properties *child,
//                              QString p_PropertyName, QString c_PropertyName,
//                              QStringList visible_PropertyNames )
//{
//  if ( !isValid() || child == 0 ||
//       !m_Parent->propertyNames().contains( p_PropertyName ) ||
//       hasLinkOption( p_PropertyName, child ) ||
//       !child->propertyNames().contains( c_PropertyName ) )
//  {
//    return false;
//  }

//  m_LinkOptions << qMakePair( p_PropertyName,
//                              new LinkOptions( child, c_PropertyName, visible_PropertyNames ) );
////  m_Children[child->name()] = child;
////  m_LinkedProperty[child->name()] = qMakePair(
////        qMakePair( p_PropertyName, c_PropertyName ), visible_PropertyNames );

//  return true;
//}

bool PropertiesLink::addLink( const QString &propertiesView_Alias,
                              QString p_PropertyName, QString c_PropertyName,
                              QStringList visible_PropertyNames )
{
  Properties *parentPs = PropertiesView::getPropertiesView( m_PropViewAlias )->root();
  Properties *child = PropertiesView::getPropertiesView( propertiesView_Alias )->root();
  if ( !isValid() || child == 0 || parentPs == child ||
       !parentPs->propertyNames().contains( p_PropertyName ) ||
       hasLinkOption( p_PropertyName, propertiesView_Alias ) ||
       !child->propertyNames().contains( c_PropertyName ) )
  {
    return false;
  }

  m_LinkOptions << qMakePair( p_PropertyName,
                              new LinkOptions( propertiesView_Alias, c_PropertyName, visible_PropertyNames ) );
//  m_Children[child->name()] = child;
//  m_LinkedProperty[child->name()] = qMakePair(
//        qMakePair( p_PropertyName, c_PropertyName ), visible_PropertyNames );

  return true;
}

bool PropertiesLink::removeLink( QString p_PropertyName, LinkOptions *link )
{
  for ( int linkIdx = 0; linkIdx < m_LinkOptions.count(); linkIdx++ )
  {
    if ( m_LinkOptions[linkIdx].first == p_PropertyName &&
         m_LinkOptions[linkIdx].second == link )
    {
      delete m_LinkOptions[linkIdx].second;
      m_LinkOptions.removeAt( linkIdx );
      return true;
    }
  }
  return false;
}

const QList<QPair<QString, LinkOptions *> > & PropertiesLink::availableLinks() const
{
  return m_LinkOptions;
}

//bool PropertiesLink::hasLinkOption( QString p_PropertyName, QString childName )
//{
//  for ( int linkIdx = 0; linkIdx < m_LinkOptions.count(); linkIdx++ )
//    if ( m_LinkOptions[linkIdx].first == p_PropertyName &&
//         m_LinkOptions[linkIdx].second->childName() == childName )
//      return true;
//  return false;
//}

//bool PropertiesLink::hasLinkOption( QString p_PropertyName, Properties *child )
//{
//  if ( child != 0 ) return hasLinkOption( p_PropertyName, child->name() );
//  return false;
//}

bool PropertiesLink::hasLinkOption( QString p_PropertyName, const QString &propertiesView_Alias )
{
  if ( PropertiesView::getPropertiesView( propertiesView_Alias )->isNull() ) return false;

  for ( int linkIdx = 0; linkIdx < m_LinkOptions.count(); linkIdx++ )
    if ( m_LinkOptions[linkIdx].first == p_PropertyName &&
         m_LinkOptions[linkIdx].second->propertiesViewAlias() == propertiesView_Alias )
      return true;
  return false;
}

//QList<QPair<QString, LinkOptions *> > PropertiesLink::links( Properties *child )
//{
//  QList<QPair<QString, LinkOptions *> > result = QList<QPair<QString, LinkOptions *> >();

//  for ( int linkIdx = 0; linkIdx < m_LinkOptions.count(); linkIdx++ )
//    if ( m_LinkOptions[linkIdx].second->childName() == child->name() )
//      result << qMakePair( m_LinkOptions[linkIdx].first, m_LinkOptions[linkIdx].second );

//  return result;
//}

QList<QPair<QString, LinkOptions *> > PropertiesLink::links( const QString &propertiesView_Alias )
{
  QList<QPair<QString, LinkOptions *> > result = QList<QPair<QString, LinkOptions *> >();
  if ( PropertiesView::getPropertiesView( propertiesView_Alias )->isNull() ) return result;

  for ( int linkIdx = 0; linkIdx < m_LinkOptions.count(); linkIdx++ )
    if ( m_LinkOptions[linkIdx].second->propertiesViewAlias() == propertiesView_Alias )
      result << qMakePair( m_LinkOptions[linkIdx].first, m_LinkOptions[linkIdx].second );

  return result;
}

QList<LinkOptions *> PropertiesLink::linksByParentProperty( QString p_PropertyName )
{
  QList<LinkOptions *> result = QList<LinkOptions *>();

  for ( int linkIdx = 0; linkIdx < m_LinkOptions.count(); linkIdx++ )
    if ( m_LinkOptions[linkIdx].first == p_PropertyName )
      result << m_LinkOptions[linkIdx].second;

  return result;
}

bool PropertiesLink::validPropertiesLink( Properties *parent, Properties *child,
                                          QString p_PropertyName, QString c_PropertyName )
{
  return ( parent != 0 && parent->propertyNames().contains( p_PropertyName ) &&
           child != 0 && child->propertyNames().contains( c_PropertyName ) &&
           parent->propertyType( p_PropertyName ) == child->propertyType( c_PropertyName ) );
}

