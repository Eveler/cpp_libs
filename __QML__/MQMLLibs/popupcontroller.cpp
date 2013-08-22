#include "popupcontroller.h"

#include "popupcontrollers.h"


PopupController::PopupController(QQuickItem *parent) :
    QQuickItem(parent)
{
    m__Poppedup = false;

    p__Controllers = PopupControllers::instance();
    p__Controllers->addController( this );
}

PopupController::~PopupController()
{
    p__Controllers->removeController( this );
}

bool PopupController::poppedup() const
{
    return m__Poppedup;
}

void PopupController::setPoppedup( bool poppedup )
{
    m__Poppedup = poppedup;
    emit poppedupChanged();
}
