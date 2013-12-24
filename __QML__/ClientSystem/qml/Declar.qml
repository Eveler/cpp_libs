import QtQuick 2.2


Item {
    id: declar

    property var identifier: undefined
    property var serviceIdentifier: undefined
    property int number: 0
    property date createDate: undefined
    property date controlDate: undefined
    property date respiteDate: undefined
    property date closeDate: undefined
    property string firstLandmark: ""
    property string lastLandmark: ""
    property var directionIdentifier: undefined
    property var responsibleIdentifier: undefined
    property var ownerIdentifier: undefined
    property bool isnew: false
    property bool deleted: false
    property var resultIdentifier: undefined
    property var assessmentTypeIdentifier: undefined
    property var assessmentIdentifier: undefined
    property var resultWayIdentifier: undefined

//    Component.onCompleted: {
//        console.trace()
//    }
}
