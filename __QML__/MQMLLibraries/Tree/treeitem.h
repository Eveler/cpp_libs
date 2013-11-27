#ifndef TREEITEM_H
#define TREEITEM_H

#include <QQuickItem>

#include <QtQml>


class TreeItem : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY( TreeItem )
    Q_PROPERTY( int nestingLevel READ nestingLevel NOTIFY nestingLevelChanged )
    Q_PROPERTY( QVariant data READ data WRITE setData NOTIFY dataChanged )
    Q_PROPERTY( QFont font READ font WRITE setFont NOTIFY fontChanged )
    Q_PROPERTY( bool hasChild READ hasChild NOTIFY hasChildChanged )
    Q_PROPERTY(QList<QObject*> childItems READ childItemsAsQObject NOTIFY childItemsChanged)


  public:
    explicit TreeItem( QQuickItem *parent = NULL );

    int nestingLevel() const;

    QVariant data() const;
    void setData( QVariant data );
    const QFont &font() const;
    void setFont( const QFont &font );
    Q_INVOKABLE QVariant columnData( int column ) const;
    Q_INVOKABLE void setColumnData( QVariant data,  int column  );

    bool hasChild() const;

    const QList<TreeItem *> &childItems() const;
    const QList<QObject *> childItemsAsQObject() const;
    Q_INVOKABLE void addChildItem(TreeItem * childItem);
    Q_INVOKABLE void removeChildItem(TreeItem * childItem);

    Q_INVOKABLE TreeItem * parentItem() const;


  signals:
    void nestingLevelChanged();
    void dataChanged( int column );
    void fontChanged( int column );
    void childItemsChanged();
    void hasChildChanged();


  public slots:


  private:
    int m__NestingLevel;
    QHash<int, QVariant> m__Data;
    QHash<int, QFont> m__Font;
    TreeItem *m__ParentItem;
    QList<TreeItem *> m__ChildItems;

    void parentItemChanged( TreeItem *parent );
};

QML_DECLARE_TYPE(TreeItem)

#endif // TREEITEM_H
