#include "propertiesview.h"
#include <QDebug>

QList<PropertiesView *> PropertiesView::m_PropertiesView = QList<PropertiesView *>();
PropertiesView PropertiesView::nullPropertiesView;

PropertiesView * PropertiesView::addPropertiesView( const QString &alias, Properties *root )
{
  if ( alias.isEmpty() )
  {
    qDebug() <<QObject::tr( "PropertiesView alias is empty!" );
    return &nullPropertiesView;
  }
  if ( root == 0 || root->isNull() )
  {
    qDebug() <<QObject::tr( "PropertiesView root properties is null!" );
    return &nullPropertiesView;
  }
  PropertiesView *pv = getPropertiesView( alias );
  if ( pv->isNull() )
  {
    pv = new PropertiesView( alias, root );
    m_PropertiesView << pv;
//    qDebug() <<QObject::tr( "PropertiesView: '" )+alias+
//                   QObject::tr( "' has been added." );
  }
  else qDebug() <<QObject::tr( "PropertiesView: '" )+alias+
               QObject::tr( "' already exists! Nothing to add." );

  return pv;
}

PropertiesView * PropertiesView::getPropertiesView( const QString &alias )
{
  if ( alias.isEmpty() ) return &nullPropertiesView;

  foreach( PropertiesView *pv, m_PropertiesView )
    if ( pv->alias() == alias ) return pv;

  return &nullPropertiesView;
}

bool PropertiesView::exists( const QString &alias )
{
  foreach( PropertiesView *pv, m_PropertiesView )
    if ( pv->alias() == alias ) return true;

  return false;
}

bool PropertiesView::release( const QString &alias )
{
  PropertiesView *pv = getPropertiesView( alias );
  if ( pv->isNull() ) return false;

  m_PropertiesView.removeOne( pv );
  delete pv;

  return true;
}

void PropertiesView::releaseAll()
{
  foreach ( PropertiesView *pv, m_PropertiesView )
  {
    m_PropertiesView.removeOne( pv );
    delete pv;
  }
}

bool PropertiesView::isNull()
{
  return m_Alias->isEmpty();
}

const QString & PropertiesView::alias() const
{
  return *m_Alias;
}

Properties * PropertiesView::root() const
{
  return m_Root;
}

//bool PropertiesView::addLink( Properties *parent, Properties *child,
//                              const QString &parent_PropertyName, const QString &child_PropertyName,
//                              const QStringList visible_PropertyNames )
//{
//  PropertiesLink *pLink = findPropertiesLink( parent );
//  if ( isNull() || !m_UsedProperties.contains( parent->name() ) ||
//       !parent->propertyNames().contains( parent_PropertyName ) ||
//       child == 0 || !child->propertyNames().contains( child_PropertyName ) ||
//       pLink == 0 || pLink->hasLinkOption( parent_PropertyName, child ) )
//  {
//    qDebug() <<isNull() << !m_UsedProperties.contains( parent->name() ) <<
//            ( parent != 0 ? !parent->propertyNames().contains( parent_PropertyName ) : true ) <<
//            ( child == 0 ) <<
//            ( child != 0 ? !child->propertyNames().contains( child_PropertyName ) : true ) <<
//            ( pLink == 0 ) <<
//            ( pLink != 0 ? pLink->hasLinkOption( parent_PropertyName, child ) : true );
//    qDebug() <<tr( "Error: [%1]:[%2] - (%3:%4)" ).arg(
//              ( parent != 0 ? parent->name() : "" ), ( child != 0 ? child->name() : "" ),
//              parent_PropertyName, child_PropertyName );
//    return false;
//  }

//  pLink->addLink( child, parent_PropertyName, child_PropertyName, visible_PropertyNames );
//  if ( !m_UsedProperties.contains( child->name() ) )
//  {
//    m_UsedProperties[child->name()] = child;
//    addLink( child );
//  }

////  qDebug() <<tr( "Added link: [%1]:[%2] - (%3:%4)" ).arg(
////            parent->name(), child->name(), parent_PropertyName, child_PropertyName );

//  return true;
//}

//bool PropertiesView::removeLink( Properties *parent, Properties *child )
//{
//  PropertiesLink *pLink = findPropertiesLink( parent );
//  if ( isNull() || !m_UsedProperties.contains( parent->name() ) ||
//       child == 0 || pLink == 0 || pLink->links( child ).count() == 0 )
//    return false;

//  foreach( PropertiesLink *propertiesLink, m_PropertiesLinks )
//    if ( propertiesLink->parent() == parent )
//    {
//      QList<QPair<QString, LinkOptions *> > links = propertiesLink->links( child );
//      for ( int linkIdx = 0; linkIdx < links.count(); linkIdx++ )
//        propertiesLink->removeLink( links[linkIdx].first, links[linkIdx].second );
//    }
//    else if ( propertiesLink->parent() == child && propertiesLink->availableLinks().count() == 0 )
//    {
//      m_PropertiesLinks.removeOne( propertiesLink );
//      delete propertiesLink;
//    }

//  return true;
//}

//bool PropertiesView::hasLink( const PropertiesLink &propertiesLink )
//{
//  foreach( PropertiesLink *pLink, m_PropertiesLinks )
//    if ( pLink->propertiesViewAlias() == propertiesLink.propertiesViewAlias() &&
//         pLink->parent() == propertiesLink.parent() &&
//         pLink->availableLinks().count() == propertiesLink.availableLinks().count() )
//      for ( int linkIdx = 0; linkIdx < pLink->availableLinks().count(); linkIdx++ )
//         if ( pLink->availableLinks().at( linkIdx ).first ==
//              propertiesLink.availableLinks().at( linkIdx ).first &&
//              pLink->availableLinks().at( linkIdx ).second ==
//              propertiesLink.availableLinks().at( linkIdx ).second )
//           return true;
//    return true;

//  return false;
//}

//const QList<PropertiesLink *> & PropertiesView::availableLinks()
//{
//  return m_PropertiesLinks;
//}

//PropertiesLink * PropertiesView::findPropertiesLink( Properties *parent )
//{
//  foreach ( PropertiesLink *pLink, m_PropertiesLinks )
//    if ( pLink->parent() == parent ) return pLink;
////    else qDebug() <<pLink->parent();

//  return 0;
//}

bool PropertiesView::addLink( PropertiesView *parent, PropertiesView *child,
                              const QString &parent_PropertyName, const QString &child_PropertyName,
                              const QStringList visible_PropertyNames )
{
  PropertiesLink *pLink = findPropertiesLink( parent );
  if ( isNull() ||
       !parent->root()->propertyNames().contains( parent_PropertyName ) ||
       child == 0 || !child->root()->propertyNames().contains( child_PropertyName ) ||
       pLink == 0 || pLink->hasLinkOption( parent_PropertyName, child->alias() ) )
  {
    qDebug() <<isNull() <<
            ( parent != 0 ? !parent->root()->propertyNames().contains( parent_PropertyName ) : true ) <<
            ( child == 0 ) <<
            ( child != 0 ? !child->root()->propertyNames().contains( child_PropertyName ) : true ) <<
            ( pLink == 0 ) <<
            ( pLink != 0 ? pLink->hasLinkOption( parent_PropertyName, child->alias() ) : true );
    qDebug() <<tr( "Error: [%1]:[%2] - (%3:%4)" ).arg(
              ( parent != 0 ? parent->root()->name() : "" ), ( child != 0 ? child->root()->name() : "" ),
              parent_PropertyName, child_PropertyName );
    return false;
  }
//  qDebug() <<tr( "Added link: [%1]:[%2] - (%3:%4)" ).arg(
//            parent->name(), child->name(), parent_PropertyName, child_PropertyName );

  return pLink->addLink( child->alias(), parent_PropertyName, child_PropertyName, visible_PropertyNames );
}

bool PropertiesView::removeLink( PropertiesView *parent, PropertiesView *child )
{
  PropertiesLink *pLink = findPropertiesLink( parent );
  if ( isNull() || child == 0 || pLink == 0 )
    return false;

  QList<QPair<QString, LinkOptions *> > links = pLink->links( child->alias() );
  if ( links.count() == 0 ) return false;
  for ( int linkIdx = 0; linkIdx < links.count(); linkIdx++ )
    pLink->removeLink( links[linkIdx].first, links[linkIdx].second );

  return true;
}

PropertiesLink * PropertiesView::propertiesLink() const
{
  return m_PropertiesLink;
}

PropertiesLink * PropertiesView::findPropertiesLink( PropertiesView *parent ) const
{
  if ( parent != 0 )
  {
    if ( this == parent )
      return m_PropertiesLink;
    else
      for ( int pairIdx = 0; pairIdx < m_PropertiesLink->availableLinks().count(); pairIdx++ )
      {
        PropertiesView *childPV = PropertiesView::getPropertiesView(
              m_PropertiesLink->availableLinks()[pairIdx].second->propertiesViewAlias() );
        PropertiesLink *resultPLink = childPV->findPropertiesLink( parent );
        if ( resultPLink != 0 ) return resultPLink;
      }
  }

  return 0;
}

QList<PropertiesLink *> PropertiesView::availableLinks() const
{
  QList<PropertiesLink *> result = QList<PropertiesLink *>();
  result << m_PropertiesLink;

  for ( int pairIdx = 0; pairIdx < m_PropertiesLink->availableLinks().count(); pairIdx++ )
  {
    PropertiesView *childPV = PropertiesView::getPropertiesView(
          m_PropertiesLink->availableLinks()[pairIdx].second->propertiesViewAlias() );
    result << childPV->availableLinks();
  }

  return result;
}

//PropertiesView::PropertiesView() :
//  QObject( 0 )
//{
//  m_Alias = new QString();
//  m_RootName = QString();
//  m_Root = 0;
//  m_UsedProperties = QHash<QString, Properties *>();
//  m_PropertiesLinks = QList<PropertiesLink *>();
//}

//PropertiesView::PropertiesView( const QString &alias, Properties *root ) :
//  QObject( 0 )
//{
//  m_Alias = new QString( alias );
//  m_RootName = root->name();
//  m_Root = root;
//  m_UsedProperties = QHash<QString, Properties *>();
//  m_UsedProperties[m_RootName] = root;
//  m_PropertiesLinks = QList<PropertiesLink *>();
//  if ( !isNull() ) addLink( root );
//}

//PropertiesView::~PropertiesView()
//{
//  QString alias = *m_Alias;
//  delete m_Alias;
//  foreach( PropertiesLink *propertiesLink, m_PropertiesLinks )
//  {
//    m_PropertiesLinks.removeOne( propertiesLink );
//    delete propertiesLink;
//  }
////  if ( !alias.isEmpty() )
////    qDebug() <<QObject::tr( "PropertiesView: '" )+alias+
////            QObject::tr( "' has been removed." );
//}

PropertiesView::PropertiesView() :
  QObject( 0 )
{
  m_Alias = new QString();
  m_RootName = QString();
  m_Root = 0;
  m_PropertiesLink = 0;
}

PropertiesView::PropertiesView( const QString &alias, Properties *root ) :
  QObject( 0 )
{
  m_Alias = new QString( alias );
  m_RootName = root->name();
  m_Root = root;
  m_PropertiesLink = new PropertiesLink( *m_Alias );
}

PropertiesView::~PropertiesView()
{
  delete m_Alias;
  delete m_PropertiesLink;
//  if ( !alias.isEmpty() )
//    qDebug() <<QObject::tr( "PropertiesView: '" )+alias+
//            QObject::tr( "' has been removed." );
}

//void PropertiesView::addLink( Properties *parent )
//{
//  m_PropertiesLinks << new PropertiesLink( *m_Alias, parent );
////  qDebug() <<tr( "Link created: [%1]" ).arg( parent->name() );
//}

void PropertiesView::propertiesDestroyed( QString propertiesName )
{
//  foreach( QString parentName, m_UsedProperties.keys() )
//    if ( m_Links[parentName].contains( propertiesName ) )
//    {
//      Properties *parent = m_UsedProperties[parentName];
//      Properties *child = m_UsedProperties[propertiesName];
//      m_Links[parentName].removeOne( propertiesName );
//      foreach( PropertiesLink *propertiesLink, m_PropertiesLinks )
//        if ( propertiesLink->parent() == parent )
//        {
//          QList<QPair<QString, LinkOptions> > links = propertiesLink->links( child );
//          for ( int linkIdx = 0; linkIdx < links.count(); linkIdx++ )
//            propertiesLink->removeLink( links[linkIdx].first, links[linkIdx].second );
//          if ( propertiesLink->availableLinks().count() == 0 )
//          {
//            m_PropertiesLinks.removeOne( propertiesLink );
//            delete propertiesLink;
//          }
//        }
//    }

//  foreach( QString childName, m_Links[propertiesName] )
//  {
//    Properties *parent = m_UsedProperties[propertiesName];
//    Properties *child = m_UsedProperties[childName];
//    foreach( PropertiesLink *propertiesLink, m_PropertiesLinks )
//      if ( propertiesLink->parent() == parent )
//      {
//        QList<QPair<QString, LinkOptions> > links = propertiesLink->links( child );
//        for ( int linkIdx = 0; linkIdx < links.count(); linkIdx++ )
//          propertiesLink->removeLink( links[linkIdx].first, links[linkIdx].second );
//        if ( propertiesLink->availableLinks().count() == 0 )
//        {
//          m_PropertiesLinks.removeOne( propertiesLink );
//          delete propertiesLink;
//        }
//      }
//    cascadeRemove( childName );
//    m_Links[propertiesName].removeOne( childName );
//  }
//  m_UsedProperties.remove( propertiesName );
//  m_Links.remove( propertiesName );
  emit destroyedProperties( propertiesName );
}
