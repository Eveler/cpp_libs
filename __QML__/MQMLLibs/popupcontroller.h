#ifndef POPUPCONTROLLER_H
#define POPUPCONTROLLER_H

#include <QQuickItem>


class PopupControllers;

class PopupController : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool poppedup READ poppedup WRITE setPoppedup NOTIFY poppedupChanged)

public:
    explicit PopupController(QQuickItem *parent = 0);
    ~PopupController();

    bool poppedup() const;
    void setPoppedup( bool poppedup );


signals:
    void poppedupChanged();

public slots:


private:
    PopupControllers *p__Controllers;

    bool m__Poppedup;
};

#endif // POPUPCONTROLLER_H
