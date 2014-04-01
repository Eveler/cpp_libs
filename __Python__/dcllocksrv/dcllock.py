#!/bin/env python
# -*- coding: utf-8 -*-
from calendar import calendar
from twisted.internet import protocol, reactor
from twisted.web.resource import Resource, NoResource
from twisted.web.server import Site

try:
    from ConfigParser import SafeConfigParser, NoSectionError
except ImportError:
    from configparser import SafeConfigParser
import logging
from logging import DEBUG, INFO, WARNING, CRITICAL, ERROR
from optparse import OptionParser


__author__ = 'mike'


def parse_args():
    """Parsing command line arguments"""
    usage = """usage: %prog [options]"""
    parser = OptionParser(usage)
    parser.add_option("--config", help="configuration file", default="/etc/dcllocksev.ini")
    options, args = parser.parse_args()
    logging.debug("options = %s, args = %s", options, args)
    logging.info("config = %s" % options.config)
    return options.config


def set_config(config):
    cfg = SafeConfigParser()
    try:
        lst = cfg.read(config)
        # logging.debug("successfuly read: %s", lst)
        # logging.debug("sections: %s", cfg.sections())
        # [logging.debug("section [%s] options: %s", section, cfg.options(section)) for section in cfg.sections()]
        # for section in cfg.sections():
        #     for option in cfg.options(section):
        #         logging.debug("%s.%s = %s", section, option, cfg.get(section, option))
        if "loglevel" in cfg.options("main"):
            logging.info("Set loggin level to '%s'", cfg.get("main", "loglevel"))
            logging.root.setLevel(cfg.get("main", "loglevel"))
    except NoSectionError:
        logging.critical("Wrong config file")
        quit()


class YearPage(Resource):
    def __init__(self, year):
        Resource.__init__(self)
        self.year = year

    def render_GET(self, request):
        return "<html><body><pre>%s</pre></body></html>" % (calendar(self.year),)


class Calendar(Resource):
    def getChild(self, name, request):
        try:
            return YearPage(int(name))
        except ValueError:
            return NoResource(message=u"Бананьев нема")


if __name__ == "__main__":
    logging.basicConfig(level=INFO, format='%(asctime)s %(levelname)s: %(module)s(%(lineno)d): %(message)s')
    logging.root.name = "dcllocksrv"
    logging.addLevelName(DEBUG, "debug")
    logging.addLevelName(INFO, "info")
    logging.addLevelName(WARNING, "warn")
    logging.addLevelName(WARNING, "warning")
    logging.addLevelName(ERROR, "error")
    logging.addLevelName(CRITICAL, "critical")

    set_config(parse_args())

    # tests here
    from declarlocker.objects import DeclarLock, session

    lock = DeclarLock(1, "declars", "mike")
    session.add(lock)
    session.commit()
    print(lock)

    root = Calendar()
    factory = Site(root)
    reactor.listenTCP(9166, factory)
    reactor.run()
