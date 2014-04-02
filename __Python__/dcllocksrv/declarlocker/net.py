# -*- coding: utf-8 -*-
import StringIO
from calendar import calendar
try:
    import json
except ImportError:
    import simplejson as json

from twisted.internet import reactor
from twisted.web.resource import Resource, NoResource
from twisted.web.server import Site, Request


__author__ = 'mike'


class YearPage(Resource):
    def __init__(self, year):
        Resource.__init__(self)
        self.year = year

    def render_GET(self, request):
        assert isinstance(request, Request)
        print("request = %s, str(request) = %s" % (request, request.getAllHeaders()))
        # j = StringIO.StringIO()
        j = json.dumps(self.year)
        o = json.loads(request.getAllHeaders().__str__())
        print("json = '%s', year = %s, obj = %s" % (j, self.year, o))
        return "<html><body><pre>%s</pre><p><pre>%s</pre></p></body></html>" % (calendar(self.year), j)


class Calendar(Resource):
    def getChild(self, name, request):
        try:
            return YearPage(int(name))
        except ValueError:
            return NoResource(message=u"Бананьев нема")


root = Calendar()
factory = Site(root)
reactor.listenTCP(9166, factory)
reactor.run()
