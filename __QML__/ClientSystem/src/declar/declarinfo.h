#ifndef DECLARINFO_H
#define DECLARINFO_H

#include <QtCore>


class DeclarInfo
{
  public:
    DeclarInfo();
    DeclarInfo( const DeclarInfo &other );
    ~DeclarInfo();

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


  private:
    QVariant m__Identifier;
    QVariant m__ServiceIdentifier;
    int m__Number;
    QDateTime m__CreateDate;
    QDateTime m__ControlDate;
    QDateTime m__RespiteDate;
    QDateTime m__CloseDate;
    QString m__FirstLandmark;
    QString m__LastLandmark;
    QVariant m__DirectionIdentifier;
    QVariant m__ResponsibleIdentifier;
    QVariant m__OwnerIdentifier;
    bool m__Isnew;
    bool m__Deleted;
    QVariant m__ResultIdentifier;
    QVariant m__AssessmentTypeIdentifier;
    QVariant m__AssessmentIdentifier;
    QVariant m__ResultWayIdentifier;
};

#endif // DECLARINFO_H
