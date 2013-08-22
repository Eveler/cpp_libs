#include "popuppanel.h"

#include <QSGSimpleRectNode>

#include "popupcontroller.h"


PopupPanel::PopupPanel(QQuickItem *parent) :
    QQuickItem(parent)
{
    m__Poppedup = false;

    p__Controller = PopupController::instance();
    p__Controller->addPanel( this );

    setFlag( QQuickItem::ItemHasContents, true );
}

PopupPanel::~PopupPanel()
{
    p__Controller->removePanel( this );
}

bool PopupPanel::poppedup() const
{
    return m__Poppedup;
}

void PopupPanel::setPoppedup( bool poppedup )
{
    m__Poppedup = poppedup;
    emit poppedupChanged();
}

QSGNode *PopupPanel::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node);
    if (!n) {
        n = new QSGSimpleRectNode();
        n->setColor(Qt::transparent);
    }
    n->setRect(boundingRect());
    return n;
}
