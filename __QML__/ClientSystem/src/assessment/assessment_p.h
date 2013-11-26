#ifndef ASSESSMENT_P_H
#define ASSESSMENT_P_H

#include <QObject>

#include "assessment.h"


class Assessment_P : public QObject
{
    Q_OBJECT
    friend class Assessment;


public:


signals:


public slots:


private:
    Assessment *m__Link;
    QString m__NullString;

    explicit Assessment_P( Assessment *parent );

    Assessment *p_dptr() const;
};

#endif // ASSESSMENT_P_H
