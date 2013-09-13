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

//        onCountChanged: {
//            if ( count > 0 )
//                console.debug(
//                            procedure( count-1 ).index+" : ["+
//                            procedure( count-1 ).identifier+", "+
//                            procedure( count-1 ).name+"]" )
//        }
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
    }

    CallstatusLoader {
        id: callstatusLoader

        source: callstatusList

        onErrorAdded: {
            console.debug( error( errorId ) )
        }
    }

    CallstatusList {
        id: callstatusList
    }

    HumanLoader {
        id: humanLoader

        source: humanList

        onErrorAdded: {
            console.debug( error( errorId ) )
        }
    }

    HumanList {
        id: humanList
    }


    Item {
        anchors.fill: parent

        Button {
            anchors.centerIn: parent

            text: "Загрузка"

            onClicked: {
                progress.value = 0
                progress.max = 7
                progress.animated = true

                nextStatus( "Пользователи", userLoader )
                nextStatus( "Наименования действий/процедур", procedureLoader )
                nextStatus( "Наименования адресатов", recipientLoader )
                nextStatus( "Наименования местонахождений", departmentLoader )
                nextStatus( "Наименования документов", doctypeLoader )
                nextStatus( "Наименования статусов звонка", callstatusLoader )
                nextStatus( "Граждане", humanLoader )
                progress.animated = false
            }

            function nextStatus( statusText, guideLoader ) {
                loadstatuses.append( {"statusText": statusText} )
                guideLoader.load()
                console.debug( statusText+": "+guideLoader.source.count )
                loadstatuses.remove( 0 )
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
            }

            add: Transition {
                ParallelAnimation {
                    NumberAnimation { properties: "x"; from: width; duration: 200 }
                    NumberAnimation { properties: "opacity"; from: 0.0; to: 1.0; duration: 200 }
                }
            }
            remove: Transition {
                ParallelAnimation {
                    NumberAnimation { properties: "x"; duration: 200 }
                    NumberAnimation { properties: "opacity"; from: 1.0; to: 0.0; duration: 1000 }
                }
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
