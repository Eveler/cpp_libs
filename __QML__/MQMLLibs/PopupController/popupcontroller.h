#ifndef POPUPCONTROLLER_H
#define POPUPCONTROLLER_H

#include <QObject>


class PopupPanel;

class PopupController: public QObject
{
    Q_OBJECT


public:
    static PopupController * instance();
    void addPanel( PopupPanel *panel );
    void removePanel( PopupPanel *panel );


private:
    static PopupController *p__Instance;
    QList<PopupPanel *> m__Panels;
    PopupPanel *m__Poppedup;

    PopupController();
    ~PopupController();


private slots:
    void poppedupChanged();
    void panelDestroyed( QObject *obj );
};

#endif // POPUPCONTROLLES_H
