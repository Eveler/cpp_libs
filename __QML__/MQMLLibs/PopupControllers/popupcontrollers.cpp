#include "popupcontrollers.h"

#include "popupcontroller.h"


PopupControllers *PopupControllers::p__Instance = NULL;

PopupControllers * PopupControllers::instance()
{
    if ( p__Instance == NULL ) p__Instance = new PopupControllers;

    return p__Instance;
}

void PopupControllers::addController( PopupController *controller )
{
    if ( p__Controllers.contains( controller ) ) return;

    connect( controller, SIGNAL(poppedupChanged()), SLOT(poppedupChanged()) );
    connect( controller, SIGNAL(destroyed(QObject*)), SLOT(controllerDestroyed(QObject*)) );
    p__Controllers << controller;
}

void PopupControllers::removeController( PopupController *controller )
{
    if ( !p__Controllers.contains( controller ) ) return;

    disconnect( controller, SIGNAL(poppedupChanged()), this, SLOT(poppedupChanged()) );
    disconnect( controller, SIGNAL(destroyed(QObject*)),
                this, SLOT(controllerDestroyed(QObject*)) );
    p__Controllers.removeOne( controller );
}

PopupControllers::PopupControllers() :
    QObject(NULL),
    p__Controllers(QList<PopupController *>())
{
}

PopupControllers::~PopupControllers() {}

void PopupControllers::poppedupChanged()
{
    PopupController *controller = qobject_cast<PopupController *>( sender() );
    if ( !controller->poppedup() )
    {
        if ( m__Poppedup == controller ) m__Poppedup = NULL;
    }
    else
    {
        PopupController *other = m__Poppedup;
        m__Poppedup = controller;
        if ( other != NULL ) other->setPoppedup( false );
    }
}

void PopupControllers::controllerDestroyed( QObject *obj )
{
    PopupController *controller = ((PopupController *)obj);

    disconnect( controller, SIGNAL(poppedupChanged()), this, SLOT(poppedupChanged()) );
    disconnect( controller, SIGNAL(destroyed(QObject*)),
                this, SLOT(controllerDestroyed(QObject*)) );
    p__Controllers.removeOne( controller );
}
