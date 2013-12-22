import QtQuick 2.2


Item {
    id: assessmenttype

    property var identifier: undefined
    property string name: ""

    Component.onCompleted: {
        console.profile()
        console.trace()
        console.profileEnd()
    }
}
