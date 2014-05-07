#!/bin/env python
# -*- coding: utf-8 -*-
from logging.handlers import TimedRotatingFileHandler
from twisted.application.service import Application

from twisted.internet import reactor
from twisted.python import log

from declarlocker.base import connect_db


try:
    from ConfigParser import SafeConfigParser, NoSectionError, NoOptionError
except ImportError:
    from configparser import SafeConfigParser, NoSectionError
import logging
from logging import DEBUG, INFO, WARNING, CRITICAL, ERROR, Formatter
from optparse import OptionParser


__author__ = 'Mike'


def parse_args():
    """Parsing command line arguments"""
    usage = """usage: %prog [options]"""
    parser = OptionParser(usage)
    parser.add_option("--config", help="configuration file", default="/etc/dcllocksrv.ini")
    options, args = parser.parse_args()
    return options.config


def set_config(config):
    cfg = SafeConfigParser()
    try:
        lst = cfg.read(config)
        if len(lst) == 0:
            raise Exception("Cannot read config file: %s" % config)

        observer = log.PythonLoggingObserver()
        observer.start()

        if "main" in cfg.sections():
            if "logfile" in cfg.options("main"):
                # log.startLogging(DailyLogFile.fromFullPath(cfg.get("main", "logfile")))
                handler = TimedRotatingFileHandler(cfg.get("main", "logfile"), when='D', backupCount=5)
                handler.setFormatter(Formatter('%(asctime)s %(module)s(%(lineno)d): %(levelname)s: %(message)s'))
                logging.root.addHandler(handler)
            logging.info("config = %s" % config)
            if "loglevel" in cfg.options("main"):
                logging.info("Set logging level to '%s'", cfg.get("main", "loglevel"))
                logging.root.setLevel(cfg.get("main", "loglevel"))
        else:
            logging.info("config = %s" % config)

        dbstr = cfg.get("db", "type") + "://"
        if "table" in cfg.options("db"):
            dbstr += cfg.get("db", "table")
        connect_db(dbstr)

        addr = ''
        port = 9166
        if "net" in cfg.sections():
            if "addr" in cfg.options("net"):
                addr = cfg.get("net", "addr")
            if "port" in cfg.options("net"):
                port = int(cfg.get("net", "port"))
        from declarlocker.net import site, CheckConnectionFactory

        reactor.listenTCP(port, site, interface=addr)
        reactor.listenTCP(port + 1, CheckConnectionFactory(), interface=addr)
    except NoSectionError as e:
        logging.critical("Wrong config file: %s", e.message)
        quit()
    except NoOptionError as e:
        logging.critical(e.message)
        quit()


logging.basicConfig(level=INFO, format='%(asctime)s %(module)s(%(lineno)d): %(levelname)s: %(message)s')
logging.root.name = "dcllocksrv"
logging.addLevelName(DEBUG, "debug")
logging.addLevelName(INFO, "info")
logging.addLevelName(WARNING, "warn")
logging.addLevelName(WARNING, "warning")
logging.addLevelName(ERROR, "error")
logging.addLevelName(CRITICAL, "critical")

set_config(parse_args())

application = Application("DeclarLock JSON-RPC Server")
