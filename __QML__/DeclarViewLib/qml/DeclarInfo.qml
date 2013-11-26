import QtQuick 2.0
import com.mihail.clientsystem 1.0


Item {
    property int declarId: 0
    onDeclarIdChanged: {
        if ( !DeclarLoader.load( "id="+declarId ) ||
                DeclarLoader.source.count == 0 ) return;
        obj_Information.declar = DeclarLoader.source.declar( 0 )

    }
    readonly property int serviceId: ( obj_Information.declar ?
                                          obj_Information.declar.serviceIdentifier : 0 )

    QtObject {
        id: obj_Information
        property Declar declar: null
    }
}
