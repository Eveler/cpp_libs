#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>


class TreeItem;

class TreeModel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( TreeModel )
    Q_PROPERTY( QList<QObject *> tree READ treeAsQObjects NOTIFY treeChanged )

  public:
    explicit TreeModel(QObject *parent = 0);

    const QList<TreeItem *> & tree() const;
    QList<QObject *> treeAsQObjects() const;


  signals:
    void treeChanged();


  public slots:


  private:
    QList<TreeItem *> m__Tree;
};

#endif // TREEMODEL_H
