#ifndef DECLAR_H
#define DECLAR_H

#include <QObject>

#include "declarinfo.h"

#include <QtQml>


class Declar_P;
class DeclarList;

class Declar : public QObject, public DeclarInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Declar)
    friend class DeclarList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QVariant serviceIdentifier READ serviceIdentifier
               WRITE setServiceIdentifier NOTIFY serviceIdentifierChanged)
    Q_PROPERTY(int number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QDateTime createDate READ createDate WRITE setCreateDate NOTIFY createDateChanged)
    Q_PROPERTY(QDateTime controlDate READ controlDate WRITE setControlDate NOTIFY controlDateChanged)
    Q_PROPERTY(QDateTime respiteDate READ respiteDate WRITE setRespiteDate NOTIFY respiteDateChanged)
    Q_PROPERTY(QDateTime closeDate READ closeDate WRITE setCloseDate NOTIFY closeDateChanged)
    Q_PROPERTY(QString firstLandmark READ firstLandmark
               WRITE setFirstLandmark NOTIFY firstLandmarkChanged)
    Q_PROPERTY(QString lastLandmark READ lastLandmark
               WRITE setLastLandmark NOTIFY lastLandmarkChanged)
    Q_PROPERTY(QVariant directionIdentifier READ directionIdentifier
               WRITE setDirectionIdentifier NOTIFY directionIdentifierChanged)
    Q_PROPERTY(QVariant responsibleIdentifier READ responsibleIdentifier
               WRITE setResponsibleIdentifier NOTIFY responsibleIdentifierChanged)
    Q_PROPERTY(QVariant ownerIdentifier READ ownerIdentifier
               WRITE setOwnerIdentifier NOTIFY ownerIdentifierChanged)
    Q_PROPERTY(bool isnew READ isnew WRITE setIsnew NOTIFY isnewChanged)
    Q_PROPERTY(bool deleted READ deleted WRITE setDeleted NOTIFY deletedChanged)
    Q_PROPERTY(QVariant resultIdentifier READ resultIdentifier
               WRITE setResultIdentifier NOTIFY resultIdentifierChanged)
    Q_PROPERTY(QVariant assessmentTypeIdentifier READ assessmentTypeIdentifier
               WRITE setAssessmentTypeIdentifier NOTIFY assessmentTypeIdentifierChanged)
    Q_PROPERTY(QVariant assessmentIdentifier READ assessmentIdentifier
               WRITE setAssessmentIdentifier NOTIFY assessmentIdentifierChanged)
    Q_PROPERTY(QVariant resultWayIdentifier READ resultWayIdentifier
               WRITE setResultWayIdentifier NOTIFY resultWayIdentifierChanged)


  public:
    Declar( DeclarList *parent = 0 );
    Declar( DeclarList *parent, const DeclarInfo &info );
    Declar( DeclarList *parent, Declar *link );
    ~Declar();

    Q_INVOKABLE DeclarList * declarList() const;

    int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    QVariant serviceIdentifier() const;
    void setServiceIdentifier( QVariant serviceIdentifier );

    int number() const;
    void setNumber( int number );

    QDateTime createDate() const;
    void setCreateDate( QDateTime createDate );

    QDateTime controlDate() const;
    void setControlDate( QDateTime controlDate );

    QDateTime respiteDate() const;
    void setRespiteDate( QDateTime respiteDate );

    QDateTime closeDate() const;
    void setCloseDate( QDateTime closeDate );

    const QString & firstLandmark() const;
    void setFirstLandmark( const QString &firstLandmark );

    const QString & lastLandmark() const;
    void setLastLandmark( const QString &lastLandmark );

    QVariant directionIdentifier() const;
    void setDirectionIdentifier( QVariant directionIdentifier );

    QVariant responsibleIdentifier() const;
    void setResponsibleIdentifier( QVariant responsibleIdentifier );

    QVariant ownerIdentifier() const;
    void setOwnerIdentifier( QVariant ownerIdentifier );

    bool isnew() const;
    void setIsnew( bool isnew );

    bool deleted() const;
    void setDeleted( bool deleted );

    QVariant resultIdentifier() const;
    void setResultIdentifier( QVariant resultIdentifier );

    QVariant assessmentTypeIdentifier() const;
    void setAssessmentTypeIdentifier( QVariant assessmentTypeIdentifier );

    QVariant assessmentIdentifier() const;
    void setAssessmentIdentifier( QVariant assessmentIdentifier );

    QVariant resultWayIdentifier() const;
    void setResultWayIdentifier( QVariant resultWayIdentifier );


  signals:
    void indexChanged();
    void identifierChanged();
    void serviceIdentifierChanged();
    void numberChanged();
    void createDateChanged();
    void controlDateChanged();
    void respiteDateChanged();
    void closeDateChanged();
    void firstLandmarkChanged();
    void lastLandmarkChanged();
    void directionIdentifierChanged();
    void responsibleIdentifierChanged();
    void ownerIdentifierChanged();
    void isnewChanged();
    void deletedChanged();
    void resultIdentifierChanged();
    void assessmentTypeIdentifierChanged();
    void assessmentIdentifierChanged();
    void resultWayIdentifierChanged();


  public slots:


  private:
    Declar_P *p;
};

QML_DECLARE_TYPE(Declar)

#endif // DECLAR_H
