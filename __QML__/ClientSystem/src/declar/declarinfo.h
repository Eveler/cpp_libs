#ifndef DECLARINFO_H
#define DECLARINFO_H

#include <QObject>

#include <QtQml>


class DeclarInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarInfo)


  public:
    DeclarInfo();
    ~DeclarInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QVariant serviceIdentifier() const;
    Q_INVOKABLE void setServiceIdentifier( QVariant serviceIdentifier );

    Q_INVOKABLE int number() const;
    Q_INVOKABLE void setNumber( int number );

    Q_INVOKABLE QDateTime createDate() const;
    Q_INVOKABLE void setCreateDate( QDateTime createDate );

    Q_INVOKABLE QDateTime controlDate() const;
    Q_INVOKABLE void setControlDate( QDateTime controlDate );

    Q_INVOKABLE QDateTime respiteDate() const;
    Q_INVOKABLE void setRespiteDate( QDateTime respiteDate );

    Q_INVOKABLE QDateTime closeDate() const;
    Q_INVOKABLE void setCloseDate( QDateTime closeDate );

    Q_INVOKABLE const QString & firstLandmark() const;
    Q_INVOKABLE void setFirstLandmark( const QString &firstLandmark );

    Q_INVOKABLE const QString & lastLandmark() const;
    Q_INVOKABLE void setLastLandmark( const QString &lastLandmark );

    Q_INVOKABLE QVariant directionIdentifier() const;
    Q_INVOKABLE void setDirectionIdentifier( QVariant directionIdentifier );

    Q_INVOKABLE QVariant responsibleIdentifier() const;
    Q_INVOKABLE void setResponsibleIdentifier( QVariant responsibleIdentifier );

    Q_INVOKABLE QVariant ownerIdentifier() const;
    Q_INVOKABLE void setOwnerIdentifier( QVariant ownerIdentifier );

    Q_INVOKABLE bool isnew() const;
    Q_INVOKABLE void setIsnew( bool isnew );

    Q_INVOKABLE bool deleted() const;
    Q_INVOKABLE void setDeleted( bool deleted );

    Q_INVOKABLE QVariant resultIdentifier() const;
    Q_INVOKABLE void setResultIdentifier( QVariant resultIdentifier );

    Q_INVOKABLE QVariant assessmentTypeIdentifier() const;
    Q_INVOKABLE void setAssessmentTypeIdentifier( QVariant assessmentTypeIdentifier );

    Q_INVOKABLE QVariant assessmentIdentifier() const;
    Q_INVOKABLE void setAssessmentIdentifier( QVariant assessmentIdentifier );

    Q_INVOKABLE QVariant resultWayIdentifier() const;
    Q_INVOKABLE void setResultWayIdentifier( QVariant resultWayIdentifier );


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

QML_DECLARE_TYPE(DeclarInfo)

#endif // DECLARINFO_H
