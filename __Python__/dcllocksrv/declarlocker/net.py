# -*- coding: utf-8 -*-
import logging
from os import getcwd
from sys import path

from twisted.cred.checkers import InMemoryUsernamePasswordDatabaseDontUse
from twisted.internet.defer import Deferred
from twisted.internet.protocol import Protocol, Factory, connectionDone
from twisted.protocols.basic import LineReceiver
from twisted.python import log
from twisted.web import server


# path.insert(0, path[0]+"/jsonrpc")
# from jsonrpc.server import ServerEvents, JSON_RPC
from declarlocker.base import lockmanager


try:
    import json
except ImportError:
    import simplejson as json

__author__ = 'Mike'

# path.insert(0, path[0] + "/txjson-rpc")
print(getcwd() + "/txjson-rpc")
path.insert(0, getcwd() + "/txjson-rpc")
from txjsonrpc.web import jsonrpc


class LockJsonRPC(jsonrpc.JSONRPC):
    """Json RPC to LockManager implementation."""
    uid = None
    d = None

    def jsonrpc_register(self):
        return lockmanager.register(self)

    def jsonrpc_lock(self, table_id, table_name, user_name, priority):
        """Try to set lock. If successful, returns true"""
        if self.uid is None:
            return jsonrpc.Fault(8002, "Must register first")
        return lockmanager.set_lock(self, table_id, table_name, user_name, priority)

    def jsonrpc_locked_by(self, table_id, table_name):
        return lockmanager.locked_by(table_id, table_name)

    def jsonrpc_is_unlock_need(self, table_id, table_name, priority):
        if lockmanager.is_locked_with_high_priority(table_id, table_name, priority):
            return True

        self.d = Deferred()
        # self.d.addErrback(False)
        return self.d

    def jsonrpc_unlock(self, table_id, table_name):
        """Remove lock."""
        lockmanager.unlock(table_id, table_name)

    def notify(self, data):
        """Send event message to peer"""
        if self.d is None:
            return

        d, self.d = self.d, None
        d.callback(data)

    def set_uid(self, uid):
        if uid is None and not self.d is None:
            logging.debug("Cancel Deferred")
            d, self.d = self.d, None
            d.callback(False)

        self.uid = uid


checker = InMemoryUsernamePasswordDatabaseDontUse()
checker.addUser("user", "pass")

from txjsonrpc.auth import wrapResource

# root = Example()
root = wrapResource(LockJsonRPC(), [checker], realmName="Declar Locker")
site = server.Site(root)


class CheckConnection(LineReceiver):
    def __init__(self):
        self.uid = None

    def connectionLost(self, reason=connectionDone):
        if not self.uid is None:
            lockmanager.unregister(self.uid)
            logging.debug("uid = %s unregistered", self.uid)

    def lineReceived(self, line):
        logging.debug("Checking uid = %s", line)
        if lockmanager.is_registered(line):
            logging.debug("uid = %s is reported as registered", line)
            self.uid = line
        else:
            logging.debug("uid = %s is reported as unregistered", line)
            self.connectionLost(connectionDone)


class CheckConnectionFactory(Factory):
    protocol = CheckConnection


# def page(arg1, arg2):
#     return '''
# <!doctype html>
# <title>Using server-sent events</title>
# <ol id="eventlist">nothing sent yet.</ol>
# <script>
# if (!!window.EventSource) {
#   var eventList = document.getElementById("eventlist");
#   var source = new EventSource('/my_event_source');
#   source.onmessage = function(e) {
#     var newElement = document.createElement("li");
#
#     newElement.innerHTML = "message: " + e.data;
#     eventList.appendChild(newElement);
#   }
#   source.addEventListener("ping", function(e) {
#     var newElement = document.createElement("li");
#
#     var obj = JSON.parse(e.data);
#     newElement.innerHTML = "ping at " + obj.time;
#     eventList.appendChild(newElement);
#   }, false);
#   source.onerror = function(e) {
#     alert("EventSource failed.");
#     source.close();
#   };
# }
# </script>
# '''


# def cycle(echo):
#     # Every second, sent a "ping" event.
#     timestr = datetime.utcnow().isoformat() + "Z"
#     echo("event: ping\n")
#     echo('data: ' + json.dumps(dict(time=timestr)))
#     echo("\n\n")
#
#     # Send a simple message at random intervals.
#     if random.random() < 0.1:
#         echo("data: This is a message at time {}\n\n".format(timestr))


# class SSEResource(resource.Resource):
#     def render_GET(self, request):
#         request.setHeader("Content-Type", "text/event-stream")
#         lc = task.LoopingCall(cycle, request.write)
#         lc.start(1)  # repeat every second
#         request.notifyFinish().addBoth(lambda _: lc.stop())
#         return server.NOT_DONE_YET


# class Echoer(pb.Root):
#     b = Broker
#     def remote_echo(self, st):
#         print 'echoing:', st
#         return st
#
# factory = pb.PBServerFactory(Echoer())

# root = resource.Resource()
# root.putChild('', wsgi.WSGIResource(reactor, reactor.getThreadPool(), page))
# # root.putChild('/', static.File("./static"))
# root.putChild('my_event_source', SSEResource())
# factory = server.Site(root)

# class ExampleServer(ServerEvents):
#     # inherited hooks
#     def log(self, responses, txrequest, error):
#         print(txrequest.code)
#         if isinstance(responses, list):
#             for response in responses:
#                 msg = self._get_msg(response)
#                 print(txrequest, msg)
#         else:
#             msg = self._get_msg(responses)
#             print(txrequest, msg)
#
#     def findmethod(self, method, args=None, kwargs=None):
#         if method in self.methods:
#             return getattr(self, method)
#         else:
#             return None
#
#     # helper methods
#     methods = set(['add', 'subtract'])
#
#     def _get_msg(self, response):
#         print('response', repr(response))
#         return ' '.join(str(x) for x in [response.id, response.result or response.error])
#
#     def subtract(self, a, b):
#         return a - b
#
#     def add(self, a, b):
#         return a + b


# root = JSON_RPC().customize(ExampleServer)
# site = server.Site(root)
