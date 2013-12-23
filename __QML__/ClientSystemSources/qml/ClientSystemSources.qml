pragma Singleton
import QtQuick 2.2

import extensions.mihail.mqmllibraries 1.0
import com.mihail.clientsystem 1.0


Item {
    id: clientSystemSources

    readonly property bool started: obj_Information.queueStarted
    readonly property int progress: ( obj_Information.currentLoader.count === 0 ?
                                         100 : (obj_Information.currentLoader.receivedCount/obj_Information.currentLoader.count*100.0) )

    readonly property List assessmentList: obj_Information.assessmentList
    readonly property AssessmentLoader assessmentLoader: obj_Information.assessmentLoader

    readonly property List assessmenttypeList: obj_Information.assessmenttypeList
    readonly property AssessmenttypeLoader assessmenttypeLoader: obj_Information.assessmenttypeLoader

    readonly property List callstatusList: obj_Information.callstatusList
    readonly property CallstatusLoader callstatusLoader: obj_Information.callstatusLoader

    readonly property List clientList: obj_Information.clientList
    readonly property ClientLoader clientLoader: obj_Information.clientLoader

    readonly property List declarList: obj_Information.declarList
    readonly property DeclarLoader declarLoader: obj_Information.declarLoader

    QtObject {
        id: obj_Information

        property List queue: List{}
        property bool queueStarted: false
        property var currentLoader: null
        //======================================================================

        //======================================================================
        property Component assessment: Component{ Assessment{} }
        property List assessmentList: List{}
        property AssessmentLoader assessmentLoader: AssessmentLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.assessment
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.assessmentList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.assessmentList.specialObjects.length === 0 )
                        {
                            obj_Information.assessmentList.specialObjects =
                                    obj_Information.className( curItem )
                        }
                        obj_Information.assessmentList.append( curItem );
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component assessmenttype: Component{ Assessmenttype{} }
        property List assessmenttypeList: List{}
        property AssessmenttypeLoader assessmenttypeLoader: AssessmenttypeLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.assessmenttype
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.assessmenttypeList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.assessmenttypeList.specialObjects.length === 0 )
                        {
                            obj_Information.assessmenttypeList.specialObjects =
                                    obj_Information.className( curItem )
                        }
                        obj_Information.assessmenttypeList.append( curItem );
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component callstatus: Component{ Callstatus{} }
        property List callstatusList: List{}
        property CallstatusLoader callstatusLoader: CallstatusLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.callstatus
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.callstatusList, {"identifier": info.identifier(),
                                        "name": info.name()} )
                        if ( obj_Information.callstatusList.specialObjects.length === 0 )
                        {
                            obj_Information.callstatusList.specialObjects =
                                    obj_Information.className( curItem )
                        }
                        obj_Information.callstatusList.append( curItem );
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component client: Component{ Client{} }
        property List clientList: List{}
        property ClientLoader clientLoader: ClientLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.client
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.clientList, {"identifier": info.identifier(),
                                        "organisationIdentifier": info.organisationIdentifier(),
                                        "humanIdentifier": info.humanIdentifier()} )
                        if ( obj_Information.clientList.specialObjects.length === 0 )
                        {
                            obj_Information.clientList.specialObjects =
                                    obj_Information.className( curItem )
                        }
                        obj_Information.clientList.append( curItem );
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component declar: Component{ Declar{} }
        property List declarList: List{}
        property DeclarLoader declarLoader: DeclarLoader {
            property int interval: 500
            property Timer loader: Timer {
                interval: 1
                onTriggered: parent.createObject()
            }
            property bool initiated: false
            property int receivedCount: 0
            readonly property bool finished: ( !started && receivedCount === count )
            onFinishedChanged: {
                if ( !initiated )
                {
                    initiated = true
                    return
                }

                if ( finished )
                {
                    console.debug( "loaded count: "+count )
                    obj_Information.loadNext()
                }
            }
            onStartedChanged: {
                if ( started || count === 0 ) return;

                createObject()
            }

            function createObject()
            {
                var component = obj_Information.declar
                if ( component.status === Component.Ready )
                {
                    var creationStarted = new Date()
                    for ( var idx = 0; idx < interval && receivedCount < count; idx++ )
                    {
                        var info = newInfo()
                        var curItem = component.createObject(
                                    obj_Information.declarList, {"identifier": info.identifier(),
                                        "serviceIdentifier": info.serviceIdentifier(),
                                        "number": info.number(),
                                        "createDate": info.createDate(),
                                        "controlDate": info.controlDate(),
                                        "respiteDate": info.respiteDate(),
                                        "closeDate": info.closeDate(),
                                        "firstLandmark": info.firstLandmark(),
                                        "lastLandmark": info.lastLandmark(),
                                        "directionIdentifier": info.directionIdentifier(),
                                        "responsibleIdentifier": info.responsibleIdentifier(),
                                        "ownerIdentifier": info.ownerIdentifier(),
                                        "isnew": info.isnew(),
                                        "deleted": info.deleted(),
                                        "resultIdentifier": info.resultIdentifier(),
                                        "assessmentTypeIdentifier": info.assessmentTypeIdentifier(),
                                        "assessmentIdentifier": info.assessmentIdentifier(),
                                        "resultWayIdentifier": info.resultWayIdentifier()} )
                        if ( obj_Information.declarList.specialObjects.length === 0 )
                        {
                            obj_Information.declarList.specialObjects =
                                    obj_Information.className( curItem )
                        }
                        obj_Information.declarList.append( curItem );
                        receivedCount++;
                    }
                    var milliseconds = MQML.millisecondsBetween( creationStarted, new Date() )
                    interval = interval*(25.0/milliseconds)
                    if ( interval < 1 ) interval = 1
                    if ( receivedCount < count ) loader.start()
                }
                else console.debug( component.errorString() )
            }
        }
        //======================================================================

        //======================================================================
        function className( object )
        {
            return object.toString().split( "(" )[0]
        }
        function loadNext()
        {
            if ( !queueStarted ) return

            if ( obj_Information.queue.length > 0 )
            {
                console.debug( "\n\n" )
                currentLoader = clientSystemSources.dequeue()
                currentLoader.load()
            }
            else queueStarted = false
        }
    }

    function startQueue()
    {
        obj_Information.queueStarted = true
        obj_Information.loadNext()
    }
    function enqueue( loader )
    {
        obj_Information.queue.append( loader )

//        if ( obj_Information.className( loader ) ===
//                obj_Information.className( obj_Information.assessmentLoader ) )
//            obj_Information.queue.append( loader )
//        else if ( obj_Information.className( loader ) ===
//                 obj_Information.className( obj_Information.assessmenttypeLoader ) )
//             obj_Information.queue.append( loader )
//        else if ( obj_Information.className( loader ) ===
//                 obj_Information.className( obj_Information.callstatusLoader ) )
//             obj_Information.queue.append( loader )
//        else if ( obj_Information.className( loader ) ===
//                 obj_Information.className( obj_Information.clientLoader ) )
//             obj_Information.queue.append( loader )
    }
    function dequeue()
    {
        return obj_Information.queue.takeFirst();
    }
}
