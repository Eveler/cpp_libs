#ifndef MSORTMODEL_H
#define MSORTMODEL_H

#include <QSortFilterProxyModel>
#include "export/mmodels_export_lib.h"

#include "msortproperties.h"

#include <QQuickItem>


class MObjectModel;

class EXPORT_MMODELS MSortModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(MObjectModel * sourceModel READ sourceModel WRITE setSourceModel NOTIFY sourceModelChanged)
    Q_PROPERTY(MSortProperties * sortProperties READ sortProperties NOTIFY sortPropertiesChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    explicit MSortModel( QObject *parent = NULL );
    ~MSortModel();

    MObjectModel * sourceModel() const;
    void setSourceModel( MObjectModel * sourceModel );

    MSortProperties * sortProperties() const;

    Q_INVOKABLE void sort();

    virtual int count() const;


  signals:
    void sourceModelChanged();
    void sortPropertiesChanged();
    void countChanged();


  public slots:


  protected:
    bool lessThan( const QModelIndex &left, const QModelIndex &right ) const;


  private:
    MSortProperties *m__SortProperties;

    int compare( QObject *left, QObject *right, MSortProperties *sortProperties ) const;
    int compare( const QVariant &left, const QVariant &right ) const;
};

QML_DECLARE_TYPE( MSortModel )

#endif // MSORTMODEL_H
