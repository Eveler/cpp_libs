import QtQuick 2.0
import com.mihail.clientsystem 1.0


Item {
    property int declarId: 0

    signal declarChanged

    onDeclarIdChanged: {
        if ( !DeclarLoader.load( "id="+declarId ) ||
                DeclarLoader.source.count == 0 )
        {
            console.debug( "DeclarLoader.source.count: "+DeclarLoader.source.count )
            return
        }
        obj_Information.declar = DeclarLoader.source.declar( 0 )
        obj_Information.serviceId = obj_Information.declar.serviceIdentifier

        if ( !TrusteeLoader.load( "declar_id="+declarId ) ) return
        if ( !DeclarClientLoader.load( "declar_id="+declarId ) ||
                DeclarClientLoader.source.count == 0 )
        {
            console.debug( "DeclarClientLoader.source.count: "+DeclarClientLoader.source.count )
            return
        }
        var clientIds = ""
        for ( var dcIdx = 0; dcIdx < DeclarClientLoader.source.count; dcIdx++ )
            clientIds += ( clientIds.length > 0 ? "," : "" )+
                    DeclarClientLoader.source.declarclient( dcIdx ).clientIdentifier
        for ( var tIdx = 0; tIdx < TrusteeLoader.source.count; tIdx++ )
            clientIds += ( clientIds.length > 0 ? "," : "" )+
                    TrusteeLoader.source.trustee( tIdx ).trusteeClientIdentifier

        if ( !ClientLoader.load( "id in ("+clientIds+")" ) ||
                ClientLoader.source.count == 0 )
        {
            console.debug( "ClientLoader.source.count: "+ClientLoader.source.count )
            return
        }
        obj_Information.clients = DeclarClientLoader.source
        obj_Information.trustees = TrusteeLoader.source
        console.debug( ClientLoader.source.count )

        declarChanged()
    }
    readonly property int serviceId: obj_Information.serviceId
    readonly property DeclarClientList clients: obj_Information.clients
    readonly property TrusteeList trustees: obj_Information.trustees

    QtObject {
        id: obj_Information
        property Declar declar: null
        property int serviceId: 0
        property DeclarClientList clients: null
        property TrusteeList trustees: null
    }
}
