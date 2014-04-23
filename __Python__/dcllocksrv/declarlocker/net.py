# -*- coding: utf-8 -*-
from datetime import datetime
import random
from sys import path

from twisted.web import resource, server

# path.insert(0, path[0]+"/jsonrpc")
# from jsonrpc.server import ServerEvents, JSON_RPC


try:
    import json
except ImportError:
    import simplejson as json

from twisted.internet import reactor, task


__author__ = 'mike'

PORT = 9166


def page(arg1, arg2):
    return '''
<!doctype html>
<title>Using server-sent events</title>
<ol id="eventlist">nothing sent yet.</ol>
<script>
if (!!window.EventSource) {
  var eventList = document.getElementById("eventlist");
  var source = new EventSource('/my_event_source');
  source.onmessage = function(e) {
    var newElement = document.createElement("li");

    newElement.innerHTML = "message: " + e.data;
    eventList.appendChild(newElement);
  }
  source.addEventListener("ping", function(e) {
    var newElement = document.createElement("li");

    var obj = JSON.parse(e.data);
    newElement.innerHTML = "ping at " + obj.time;
    eventList.appendChild(newElement);
  }, false);
  source.onerror = function(e) {
    alert("EventSource failed.");
    source.close();
  };
}
</script>
'''


def cycle(echo):
    # Every second, sent a "ping" event.
    timestr = datetime.utcnow().isoformat() + "Z"
    echo("event: ping\n")
    echo('data: ' + json.dumps(dict(time=timestr)))
    echo("\n\n")

    # Send a simple message at random intervals.
    if random.random() < 0.1:
        echo("data: This is a message at time {}\n\n".format(timestr))


class SSEResource(resource.Resource):
    def render_GET(self, request):
        request.setHeader("Content-Type", "text/event-stream")
        lc = task.LoopingCall(cycle, request.write)
        lc.start(1)  # repeat every second
        request.notifyFinish().addBoth(lambda _: lc.stop())
        return server.NOT_DONE_YET


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

path.insert(0, path[0] + "/txjson-rpc")
from txjsonrpc.web import jsonrpc


class Example(jsonrpc.JSONRPC):
    """An example object to be published."""

    def jsonrpc_echo(self, x):
        """Return all passed args."""
        return x

    def jsonrpc_add(self, a, b):
        """Return sum of arguments."""
        return a + b


root = Example()
site = server.Site(root)

print('Listening on port %d...' % PORT)
reactor.listenTCP(PORT, site)
reactor.run()
