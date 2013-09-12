import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

import com.mihail.clientsystem 1.0


ApplicationWindow {
    width: 500
    height: 350

    UserLoader {
        id: userLoader

        source: userList

        onErrorAdded: {
            console.debug( error( errorId ) )
        }
    }

    UserList {
        id: userList

        onCountChanged: {
            if ( count > 0 )
                console.debug(
                            user( count-1 ).index+" : ["+
                            user( count-1 ).identifier+", "+
                            user( count-1 ).surname+", "+
                            user( count-1 ).firstname+", "+
                            user( count-1 ).lastname+", "+
                            user( count-1 ).post+", "+
                            user( count-1 ).department+", "+
                            user( count-1 ).isactive+", "+
                            user( count-1 ).dismissed+", "+
                            user( count-1 ).dblogin+", "+
                            user( count-1 ).direction+"]" )
        }
    }

    ProcedureLoader {
        id: procedureLoader

        source: procedureList

        onErrorAdded: {
            console.debug( error( errorId ) )
        }
    }

    ProcedureList {
        id: procedureList

        onCountChanged: {
            if ( count > 0 )
                console.debug(
                            procedure( count-1 ).index+" : ["+
                            procedure( count-1 ).identifier+", "+
                            procedure( count-1 ).name+"]" )
        }
    }

    RecipientLoader {
        id: recipientLoader

        source: recipientList

        onErrorAdded: {
            console.debug( error( errorId ) )
        }
    }

    RecipientList {
        id: recipientList

        onCountChanged: {
            if ( count > 0 )
                console.debug(
                            recipient( count-1 ).index+" : ["+
                            recipient( count-1 ).identifier+", "+
                            recipient( count-1 ).name+"]" )
        }
    }

    DepartmentLoader {
        id: departmentLoader

        source: departmentList

        onErrorAdded: {
            console.debug( error( errorId ) )
        }
    }

    DepartmentList {
        id: departmentList

        onCountChanged: {
            if ( count > 0 )
                console.debug(
                            department( count-1 ).index+" : ["+
                            department( count-1 ).identifier+", "+
                            department( count-1 ).name+"]" )
        }
    }

    DoctypeLoader {
        id: doctypeLoader

        source: doctypeList

        onErrorAdded: {
            console.debug( error( errorId ) )
        }
    }

    DoctypeList {
        id: doctypeList

        onCountChanged: {
            if ( count > 0 )
                console.debug(
                            doctype( count-1 ).index+" : ["+
                            doctype( count-1 ).identifier+", "+
                            doctype( count-1 ).name+"]" )
        }
    }


    Item {
        anchors.fill: parent

        Button {
            anchors.centerIn: parent

            text: "Загрузка"

            onClicked: {
                progress.value = 0
                progress.max = 5
                progress.animated = true

                nextStatus( "Пользователи", userLoader )
                nextStatus( "Наименования действий/процедур", procedureLoader )
                nextStatus( "Наименования адресатов", recipientLoader )
                nextStatus( "Наименования местонахождений", departmentLoader )
                nextStatus( "Наименования документов", doctypeLoader )
                progress.animated = false
            }

            function nextStatus( statusText, guideLoader ) {
                while ( loadstatuses.count > 0 ) loadstatuses.remove( 0 )
                loadstatuses.append( {"statusText": statusText} )
                console.debug( statusText+": "+guideLoader.load() )
                progress.value++
            }
        }
    }

    statusBar: Item {
        width: parent.width
        height: 30

        ListModel {
            id: loadstatuses
        }

        ListView {
            anchors.fill: parent

            clip: true
            orientation: ListView.Horizontal

            model: loadstatuses

            delegate: Text {
                width: contentWidth+6
                height: parent.height

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: statusText

                Timer {
                    id: deleter
                    interval: 2000
                    onTriggered: {
                        loadstatuses.remove( model.index )
                    }
                }

                Component.onCompleted: deleter.running = true
            }

            add: Transition {
                ParallelAnimation {
                    NumberAnimation { properties: "x"; from: width; duration: 200 }
                    NumberAnimation { properties: "opacity"; from: 0.0; to: 1.0; duration: 20 }
                }
            }
            remove: Transition {
                NumberAnimation { properties: "opacity"; from: 1.0; to: 0.0; duration: 200 }
            }
        }

        Rectangle {
            id: progress
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height
            width: ( max > 0 ? (value/max*parent.width) : 0 )
            Behavior on width {
                enabled: progress.animated
                NumberAnimation { duration: 200 }
            }

            property int value: 0
            property int max: 0
            property bool animated: false

            color: "#55000000"
        }
    }
}
