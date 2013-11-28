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
    Q_PROPERTY( bool selected READ selected WRITE setSelected NOTIFY selectedChanged )
    Q_PROPERTY( bool childSelected READ childSelected NOTIFY childSelectedChanged )
    Q_PROPERTY( bool opened READ opened WRITE setOpened NOTIFY openedChanged )
    Q_PROPERTY(QList<QObject*> childItems READ childItemsAsQObject NOTIFY childItemsChanged)


  public:
    explicit TreeItem( QQuickItem *parent = NULL );

    int nestingLevel() const;

    QVariant data() const;
    void setData( QVariant data );
    QFont font() const;
    void setFont( const QFont &font );
    Q_INVOKABLE QVariant columnData( int column ) const;
    Q_INVOKABLE void setColumnData( QVariant data,  int column  );

    bool hasChild() const;

    bool selected() const;
    void setSelected( bool selected );

    bool childSelected() const;

    bool opened() const;
    void setOpened( bool opened );

    const QList<TreeItem *> &childItems() const;
    const QList<QObject *> childItemsAsQObject() const;
    Q_INVOKABLE void addChildItem(TreeItem * childItem);
    Q_INVOKABLE void removeChildItem(TreeItem * childItem);

    Q_INVOKABLE TreeItem * parentItem() const;


  signals:
    void nestingLevelChanged();
    void dataChanged( int column );
    void fontChanged( int column );
    void selectedChanged( TreeItem *item );
    void childSelectedChanged();
    void openedChanged();
    void childItemsChanged();
    void hasChildChanged();


  public slots:


  private:
    int m__NestingLevel;
    QHash<int, QVariant> m__Data;
    QHash<int, QFont> m__Font;
    bool m__Selected;
    bool m__Opened;
    TreeItem *m__ParentItem;
    QList<TreeItem *> m__ChildItems;
    QList<TreeItem *> m__SelectedItems;

    void parentItemChanged( TreeItem *parent );


  private slots:
    void childSelected( TreeItem *item );
};

QML_DECLARE_TYPE(TreeItem)

#endif // TREEITEM_H
