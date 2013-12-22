import QtQuick 2.2


Item {
    id: callstatus

    property var identifier: undefined
    property string name: ""

    Component.onCompleted: {
        console.profile()
        console.trace()
        console.profileEnd()
    }
}
