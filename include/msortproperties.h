#ifndef MSORTPROPERTIES_H
#define MSORTPROPERTIES_H

#include <QQuickItem>
#include "export/mmodels_export_lib.h"


class SafelyValue;

class EXPORT_MMODELS MSortProperties : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)


  public:
    explicit MSortProperties(QQuickItem *parent = 0);
    ~MSortProperties();

    Q_INVOKABLE void addSort( QString propertyName, Qt::SortOrder sort );
    Q_INVOKABLE void replaceSort( int index, QString propertyName, Qt::SortOrder sort );
    Q_INVOKABLE MSortProperties * addSort( QString propertyName );
    Q_INVOKABLE MSortProperties * replaceSort( int index, QString propertyName );
    Q_INVOKABLE void removeSort( int index );
    Q_INVOKABLE QString sortProperty( int index ) const;
    Q_INVOKABLE SafelyValue * sortOrder( int index ) const;

    int count() const;


  signals:
    void sortPropertiesChanged();
    void countChanged();


  public slots:


  private:
    QStringList m__SortProperties;
    QVariantList m__SortOrder;
};

QML_DECLARE_TYPE( MSortProperties )

#endif // MSORTPROPERTIES_H
