#ifndef MELECTRODOC_H
#define MELECTRODOC_H

#include <QQuickItem>

class MElectroDoc : public QQuickItem
{
    Q_OBJECT
    Q_ENUMS(ElectrodocStates)

public:
    enum ElectrodocStates { Read = 0, Write, Check };
    explicit MElectroDoc(QQuickItem *parent = 0);

signals:

public slots:

};

#endif // MELECTRODOC_H
