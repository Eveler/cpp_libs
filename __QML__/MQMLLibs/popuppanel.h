#ifndef POPUPPANEL_H
#define POPUPPANEL_H

#include <QQuickItem>


class PopupController;

class PopupPanel : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool poppedup READ poppedup WRITE setPoppedup NOTIFY poppedupChanged)

public:
    explicit PopupPanel(QQuickItem *parent = 0);
    ~PopupPanel();

    bool poppedup() const;
    void setPoppedup( bool poppedup );

    QSGNode * updatePaintNode( QSGNode *, UpdatePaintNodeData * );


signals:
    void poppedupChanged();

public slots:


private:
    PopupController *p__Controller;

    bool m__Poppedup;
};

#endif // POPUPPANEL_H
