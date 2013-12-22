#ifndef LIST_H
#define LIST_H

#include <QQuickItem>


class List : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(List)
    Q_PROPERTY(QString propertyName READ propertyName WRITE setPropertyName NOTIFY propertyNameChanged)
    Q_PROPERTY(int length READ length NOTIFY lengthChanged)
    Q_PROPERTY(QList<QObject *> model READ model NOTIFY modelChanged)


  public:
    explicit List(QQuickItem *parent = 0);
    ~List();

    QString propertyName() const;
    void setPropertyName( QString propertyName );

    int length() const;
    QList<QObject *> model() const;

    Q_INVOKABLE void append( QObject *obj );
    Q_INVOKABLE void remove( QObject *obj );
    Q_INVOKABLE QObject * takeFirst();


  signals:
    void propertyNameChanged();
    void lengthChanged();
    void modelChanged();


  public slots:


  private:
    QString m__PropertyName;
    QVariantList m__PropertyValues;
    QObjectList m__Objects;


  private slots:
    void objectDestroyed( QObject *obj );
};

QML_DECLARE_TYPE(List)

#endif // LIST_H
