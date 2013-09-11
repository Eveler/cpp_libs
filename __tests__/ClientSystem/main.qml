import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

import com.mihail.clientsystem 1.0


ApplicationWindow {
    width: 100
    height: 62

    UserList {
        id: userList

        onErrorAdded: {
            console.debug( error( errorId ) )
        }

        onCountChanged: console.debug(
                            count+" : ["+
                            user( count-1 ).identifier+", "+
                            user( count-1 ).surname+", "+
                            user( count-1 ).firstname+", "+
                            user( count-1 ).lastname+"]" )
    }

    Component.onCompleted: console.debug( userList.load() )
}
