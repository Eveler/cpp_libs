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
    Q_PROPERTY( QFont font READ font WRITE setFont NOTIFY fontChanged )
    Q_PROPERTY( QVariant value READ value WRITE setValue NOTIFY valueChanged )
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

    Q_INVOKABLE QVariant propertyData( QString propertyName ) const;
    Q_INVOKABLE void setPropertyData( QString propertyName, QVariant data );

    QFont font() const;
    void setFont( const QFont &font );

    QVariant value() const;
    void setValue( QVariant value );

    Q_INVOKABLE QVariant columnValue( int column ) const;
    Q_INVOKABLE void setColumnValue( QVariant value,  int column  );

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
    void propertyDataChanged( QString propertyName );
    void fontChanged( int column );
    void valueChanged( int column );
    void itemEnabledChanged();
    void selectableChanged();
    void selectedChanged( TreeItem *item );
    void childSelectedChanged();
    void expandableChanged();
    void expandedChanged();
    void childItemsChanged();
    void childItemAdded( int index );
    void childItemRemoved( int index );
    void hasChildChanged();
    void clicked( TreeItem *item );
    void doubleClicked( TreeItem *item );


  public slots:


  private:
    int m__NestingLevel;
    QHash<QString, QVariant> m__PropertyData;
    QHash<int, QFont> m__Font;
    QHash<int, QVariant> m__Value;
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
