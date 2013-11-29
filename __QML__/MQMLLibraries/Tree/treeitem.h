#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>

#include <QtQml>
#include <QFont>


class TreeItem : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( TreeItem )
    Q_PROPERTY( int nestingLevel READ nestingLevel NOTIFY nestingLevelChanged )
    Q_PROPERTY( QVariant data READ data WRITE setData NOTIFY dataChanged )
    Q_PROPERTY( QFont font READ font WRITE setFont NOTIFY fontChanged )
    Q_PROPERTY( bool hasChild READ hasChild NOTIFY hasChildChanged )
    Q_PROPERTY( bool itemEnabled READ itemEnabled WRITE setItemEnabled NOTIFY itemEnabledChanged )
    Q_PROPERTY( bool selectable READ isSelectable WRITE setSelectable NOTIFY selectableChanged )
    Q_PROPERTY( bool selected READ isSelected WRITE setSelected NOTIFY selectedChanged )
    Q_PROPERTY( bool childSelected READ childSelected NOTIFY childSelectedChanged )
    Q_PROPERTY( bool expandable READ isExpandable WRITE setExpandable NOTIFY expandableChanged )
    Q_PROPERTY( bool expanded READ isExpanded WRITE setExpanded NOTIFY expandedChanged )
    Q_PROPERTY(QList<QObject*> childItems READ childItemsAsQObject NOTIFY childItemsChanged)


  public:
    explicit TreeItem( QObject *parent = NULL );
    ~TreeItem();

    int nestingLevel() const;

    QVariant data() const;
    void setData( QVariant data );
    QFont font() const;
    void setFont( const QFont &font );
    Q_INVOKABLE QVariant columnData( int column ) const;
    Q_INVOKABLE void setColumnData( QVariant data,  int column  );

    bool hasChild() const;

    bool itemEnabled() const;
    void setItemEnabled( bool enabled );

    bool isSelectable() const;
    void setSelectable( bool selectable );
    bool isSelected() const;
    void setSelected( bool selected );

    bool childSelected() const;

    bool isExpandable() const;
    void setExpandable( bool expandable );
    bool isExpanded() const;
    void setExpanded( bool expanded );

    const QList<TreeItem *> &childItems() const;
    const QList<QObject *> childItemsAsQObject() const;
    Q_INVOKABLE void addChildItem( TreeItem *item );
    Q_INVOKABLE void removeChildItem( TreeItem *item );

    Q_INVOKABLE TreeItem * parentItem() const;

    Q_INVOKABLE void click();
    Q_INVOKABLE void doubleClick();


  signals:
    void nestingLevelChanged();
    void dataChanged( int column );
    void fontChanged( int column );
    void itemEnabledChanged();
    void selectableChanged();
    void selectedChanged( TreeItem *item );
    void childSelectedChanged();
    void expandableChanged();
    void expandedChanged();
    void childItemsChanged();
    void hasChildChanged();
    void clicked( TreeItem *item );
    void doubleClicked( TreeItem *item );


  public slots:


  private:
    int m__NestingLevel;
    QHash<int, QVariant> m__Data;
    QHash<int, QFont> m__Font;
    bool m__ItemEnabled;
    bool m__Selectable;
    bool m__Selected;
    bool m__Expandable;
    bool m__Expanded;
    TreeItem *m__ParentItem;
    QList<TreeItem *> m__ChildItems;
    QList<TreeItem *> m__SelectedItems;

    void parentItemChanged( TreeItem *parent );


  private slots:
    void childSelected( TreeItem *item );
    void childDestroyed( QObject *obj );
    void parentEnabledChanged();
};

QML_DECLARE_TYPE(TreeItem)

#endif // TREEITEM_H
