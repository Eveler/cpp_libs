#ifndef MDEPARTMENTDBWRAPPER_H
#define MDEPARTMENTDBWRAPPER_H

#include "mabstractdbwrapper.h"


class MDepartment : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


  public:
    explicit MDepartment( QQuickItem *parent = NULL );
    ~MDepartment();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString & name );

    int externalLinksCount() const;


  signals:
    void identifierChanged();
    void nameChanged();
    void externalLinksCountChanged();


  private:
    QVariant m__Identifier;
    QString m__Name;
    int m__ExternalLinksCount;

    int incrementExternalLinks();
    int decrementExternalLinks();
};

QML_DECLARE_TYPE( MDepartment )


class MDepartmentDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT
  public:
    explicit MDepartmentDBWrapper( MAbstractDataSource *parent = NULL );
    ~MDepartmentDBWrapper();

    MDepartment *department( QVariant identifier );
    QList<MDepartment *> departments( QVariantList identifiers );


  protected:
    bool searching( const QString &queryText );
    bool initiating();
    bool saving( QObject *object );


  private:
    QHash<int, MDepartment *> m__ExistDepartments;
};

#endif // MDEPARTMENTDBWRAPPER_H
