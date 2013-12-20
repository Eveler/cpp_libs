import QtQuick 2.2

import com.mihail.clientsystem 1.0


Item {
    id: assessmentList
    readonly property var model: obj_Information.model

    QtObject {
        id: obj_Information

        property list<Assessment> model: [
            Assessment{}
        ]
    }

    function add( assessment )
    {
        console.debug( model.length )
        model.add( assessment )
        console.debug( model.length )
    }
}
