#include "popupcontroller.h"

#include "popuppanel.h"


PopupController * PopupController::p__Instance = NULL;

PopupController * PopupController::instance()
{
    if ( p__Instance == NULL ) p__Instance = new PopupController;

    return p__Instance;
}

void PopupController::addPanel( PopupPanel *panel )
{
    if ( m__Panels.contains( panel ) ) return;

    connect( panel, SIGNAL(poppedupChanged()), SLOT(poppedupChanged()) );
    connect( panel, SIGNAL(destroyed(QObject*)), SLOT(panelDestroyed(QObject*)) );
    m__Panels << panel;
}

void PopupController::removePanel( PopupPanel *panel )
{
    if ( !m__Panels.contains( panel ) ) return;

    disconnect( panel, SIGNAL(poppedupChanged()), this, SLOT(poppedupChanged()) );
    disconnect( panel, SIGNAL(destroyed(QObject*)), this, SLOT(panelDestroyed(QObject*)) );
    m__Panels.removeOne( panel );
}

PopupController::PopupController() :
    QObject(NULL),
    m__Panels(QList<PopupPanel *>()),
    m__Poppedup(NULL)
{
}

PopupController::~PopupController() {}

void PopupController::poppedupChanged()
{
    PopupPanel *panel = qobject_cast<PopupPanel *>( sender() );
    if ( !panel->poppedup() )
    {
        if ( m__Poppedup == panel ) m__Poppedup = NULL;
    }
    else
    {
        PopupPanel *oldPanel = m__Poppedup;
        m__Poppedup = panel;
        if ( oldPanel != NULL ) oldPanel->setPoppedup( false );
    }
}

void PopupController::panelDestroyed( QObject *obj )
{
    PopupPanel *panel = ((PopupPanel *)obj);

    disconnect( panel, SIGNAL(poppedupChanged()), this, SLOT(poppedupChanged()) );
    disconnect( panel, SIGNAL(destroyed(QObject*)), this, SLOT(panelDestroyed(QObject*)) );
    m__Panels.removeOne( panel );
}
