#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>

#include <QtQml>


class TreeItem;

class TreeModel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( TreeModel )
    Q_PROPERTY( QList<QObject *> tree READ treeAsQObjects NOTIFY treeChanged )
    Q_PROPERTY( QList<QObject *> selected READ selectedAsObjects NOTIFY selectedChanged )
    Q_PROPERTY( int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged )

  public:
    explicit TreeModel(QObject *parent = 0);
    ~TreeModel();

    const QList<TreeItem *> & tree() const;
    QList<QObject *> treeAsQObjects() const;

    const QList<TreeItem *> & selected() const;
    QList<QObject *> selectedAsObjects() const;

    Q_INVOKABLE void addTopLevelItem( TreeItem *item );
    Q_INVOKABLE void removeTopLevelItem( TreeItem *item );

    int columnCount() const;
    void setColumnCount( int columnCount );


  signals:
    void treeChanged();
    void columnCountChanged();
    void selectedChanged( TreeItem *treeItem );
    void treeItemClicked( TreeItem *treeItem );
    void treeItemDoubleClicked( TreeItem *treeItem );


  public slots:


  private:
    QList<TreeItem *> m__Tree;
    QList<TreeItem *> m__Selected;
    int m__ColumnCount;


  private slots:
    void treeItemSelectedChanged( TreeItem *treeItem );
    void treeItemDestroyed( QObject *obj );
};

QML_DECLARE_TYPE(TreeModel)

#endif // TREEMODEL_H
