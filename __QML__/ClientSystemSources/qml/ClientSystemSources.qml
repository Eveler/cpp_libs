pragma Singleton
import QtQuick 2.2

import extensions.mihail.mqmllibraries 1.0
import com.mihail.clientsystem 1.0


Item {
    id: clientSystemSources

    readonly property bool started: obj_Information.queueStarted

    readonly property List assessmentList: obj_Information.assessmentList
    readonly property AssessmentLoader assessmentLoader: obj_Information.assessmentLoader

    readonly property List assessmenttypeList: obj_Information.assessmenttypeList
    readonly property AssessmenttypeLoader assessmenttypeLoader: obj_Information.assessmenttypeLoader

    readonly property List callstatusList: obj_Information.callstatusList
    readonly property CallstatusLoader callstatusLoader: obj_Information.callstatusLoader

    readonly property List clientList: obj_Information.clientList
    readonly property ClientLoader clientLoader: obj_Information.clientLoader

    QtObject {
        id: obj_Information

        property List queue: List{}
        property bool queueStarted: false
        //======================================================================

        //======================================================================
        property Component assessment: Component{ Assessment{} }
        property List assessmentList: List{}
        property AssessmentLoader assessmentLoader: AssessmentLoader {
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
            onNewInfo: {
                var component = obj_Information.assessment
                if ( component.status === Component.Ready )
                {
                    var curItem = component.createObject(
                                obj_Information.assessmentList, {"identifier": info.identifier(),
                                "name": info.name()} )
                    if ( obj_Information.assessmentList.specialObjects.length === 0 )
                    {
                        obj_Information.assessmentList.specialObjects =
                                obj_Information.className( curItem )
                    }
                    obj_Information.assessmentList.append( curItem )
                    receivedCount++
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component assessmenttype: Component{ Assessmenttype{} }
        property List assessmenttypeList: List{}
        property AssessmenttypeLoader assessmenttypeLoader: AssessmenttypeLoader {
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
            onNewInfo: {
                var component = obj_Information.assessmenttype
                if ( component.status === Component.Ready )
                {
                    var curItem = component.createObject(
                                obj_Information.assessmenttypeList, {"identifier": info.identifier(),
                                "name": info.name()} )
                    if ( obj_Information.assessmenttypeList.specialObjects.length === 0 )
                    {
                        obj_Information.assessmenttypeList.specialObjects =
                                obj_Information.className( curItem )
                    }
                    obj_Information.assessmenttypeList.append( curItem )
                    receivedCount++
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component callstatus: Component{ Callstatus{} }
        property List callstatusList: List{}
        property CallstatusLoader callstatusLoader: CallstatusLoader{
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
            onNewInfo: {
                var component = obj_Information.callstatus
                if ( component.status === Component.Ready )
                {
                    var curItem = component.createObject(
                                obj_Information.callstatusList, {"identifier": info.identifier(),
                                "name": info.name()} )
                    if ( obj_Information.callstatusList.specialObjects.length === 0 )
                    {
                        obj_Information.callstatusList.specialObjects =
                                obj_Information.className( curItem )
                    }
                    obj_Information.callstatusList.append( curItem )
                    receivedCount++
                }
                else console.debug( component.errorString() )
            }
        }
        //----------------------------------------------------------------------
        property Component client: Component{ Client{} }
        property List clientList: List{}
        property ClientLoader clientLoader: ClientLoader{
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
            onNewInfo: {
                var component = obj_Information.client
                if ( component.status === Component.Ready )
                {
                    var curItem = component.incubateObject(
                                obj_Information.clientList, {"identifier": info.identifier(),
                            "organisationIdentifier": info.organisationIdentifier(),
                            "humanIdentifier": info.humanIdentifier()} )
                    if (curItem.status !== Component.Ready) {
                        console.count()
                        curItem.onStatusChanged = function(status) {
                            if (status === Component.Ready) {
                                console.debug( curItem.object )
                                if ( obj_Information.clientList.specialObjects.length === 0 )
                                {
                                    obj_Information.clientList.specialObjects =
                                            obj_Information.className( curItem.object )
                                }
                                obj_Information.clientList.append( curItem.object )
                                receivedCount++
                            }
                        }
                    } else {
                        if ( obj_Information.clientList.specialObjects.length === 0 )
                        {
                            obj_Information.clientList.specialObjects =
                                    obj_Information.className( curItem.object )
                        }
                        obj_Information.clientList.append( curItem.object )
                        receivedCount++
                    }
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
                clientSystemSources.dequeue().load()
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
