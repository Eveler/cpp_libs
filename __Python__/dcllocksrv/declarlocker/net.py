# -*- coding: utf-8 -*-
from datetime import datetime
import random

from twisted.web import resource, server, wsgi


try:
    import json
except ImportError:
    import simplejson as json

from twisted.internet import reactor, task


__author__ = 'mike'


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

root = resource.Resource()
root.putChild('', wsgi.WSGIResource(reactor, reactor.getThreadPool(), page))
# root.putChild('/', static.File("./static"))
root.putChild('my_event_source', SSEResource())
factory = server.Site(root)
reactor.listenTCP(9166, factory)
reactor.run()
