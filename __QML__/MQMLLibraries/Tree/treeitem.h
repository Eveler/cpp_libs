#ifndef TREEITEM_H
#define TREEITEM_H

#include <QQuickItem>


class TreeItem : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY( TreeItem )
    Q_PROPERTY( int nestingLevel READ nestingLevel NOTIFY nestingLevelChanged )
    Q_PROPERTY( QVariant data READ data WRITE setData NOTIFY dataChanged )


  public:
    explicit TreeItem( TreeItem *parent = NULL );

    int nestingLevel() const;

    QVariant data( int column = 0 ) const;
    void setData( QVariant data, int column = 0 );


  signals:
    void nestingLevelChanged();
    void dataChanged( int column );


  public slots:


  private:
    int m__NestingLevel;
    QHash<int, QVariant> m__Data;


  private slots:
    void parentItemChanged( QQuickItem *parent );
};

#endif // TREEITEM_H
