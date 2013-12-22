import QtQuick 2.2

import extensions.mihail.mqmllibraries 1.0
import com.mihail.clientsystem 1.0


List {
    id: assessmenttypeList

    function create( info )
    {
        var component = Qt.createComponent( "Assessmenttype.qml" )
        if ( component.status === Component.Ready )
        {
            var curItem = component.createObject(
                        assessmenttypeList, {"identifier": info.identifier(),
                        "name": info.name()} )
            append( curItem )
        }
        else console.debug( component.errorString() )
    }
}
