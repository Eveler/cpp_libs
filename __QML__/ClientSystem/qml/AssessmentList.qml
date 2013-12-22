import QtQuick 2.2

import extensions.mihail.mqmllibraries 1.0
import com.mihail.clientsystem 1.0


List {
    id: assessmentList
    readonly property var model: obj_Information.model

    QtObject {
        id: obj_Information

    }

    function create( info )
    {
        var component = Qt.createComponent( "Assessment.qml" )
        if ( component.status === Component.Ready )
        {
            var curItem = component.createObject(
                        assessmentList, {"identifier": info.identifier(),
                        "name": info.name()} )
            append( curItem )
//            console.debug( curItem )
//            assessmentList.add( curItem )
        }
        else console.debug( component.errorString() )
    }
}
