#!/bin/env python
# -*- coding: utf-8 -*-
from logging.handlers import TimedRotatingFileHandler
import sys

from twisted.internet import reactor
from twisted.python import log, usage

from declarlocker.base import lockmanager


try:
    from ConfigParser import SafeConfigParser, NoSectionError, NoOptionError
except ImportError:
    from configparser import SafeConfigParser, NoSectionError
import logging
from logging import DEBUG, INFO, WARNING, CRITICAL, ERROR, Formatter
from optparse import OptionParser


__author__ = 'Mike'


class Options(usage.Options):

    optParameters = [["config", "c", "/etc/dcllocksrv.ini", "configuration file"]]


def parse_args():
    """Parsing command line arguments"""
    # usage = """usage: %prog [options]"""
    # parser = OptionParser(usage)
    # parser.add_option("--config", help="configuration file", default="/etc/dcllocksrv.ini")
    # options, args = parser.parse_args()
    # return options.config
    config = Options()
    try:
        config.parseOptions()  # When given no argument, parses sys.argv[1:]
    except usage.UsageError, errortext:
        print '%s: %s' % (sys.argv[0], errortext)
        print '%s: Try --help for usage details.' % (sys.argv[0])
        sys.exit(1)
    return config['config']


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
                handler = TimedRotatingFileHandler(cfg.get("main", "logfile"), when='D', backupCount=7)
                handler.setFormatter(Formatter('%(asctime)s %(module)s(%(lineno)d): %(levelname)s: %(message)s'))
                logging.root.addHandler(handler)
            logging.info("config = %s" % config)
            if "loglevel" in cfg.options("main"):
                logging.info("Set logging level to '%s'", cfg.get("main", "loglevel"))
                logging.root.setLevel(cfg.get("main", "loglevel"))
        else:
            logging.info("config = %s" % config)

        dbstr = cfg.get("db", "type") + "://"
        if dbstr == "://":
            raise Exception("Wrong or not set db.type in config file")
        if "db" in cfg.options("db"):
            dbstr += cfg.get("db", "db")
        lockmanager.connect_db(dbstr)
        
        if "auth" in cfg.sections():
            if "db_type" in cfg.options("auth"):
                is_db = cfg.get("auth", "db_type")+"://"
                if is_db == "://":
                    raise Exception("Wrong or not set auth.db_type in config file")
                if "db_user" in cfg.options("auth"):
                    is_db += cfg.get("auth", "db_user")
                if "db_pass" in cfg.options("auth"):
                    is_db += ":"+cfg.get("auth", "db_pass")
                if "db_host" in cfg.options("auth"):
                    if "db_user" in cfg.options("auth"):
                        is_db += "@"
                    is_db += cfg.get("auth", "db_host")
                if "db_db" in cfg.options("auth"):
                    is_db += "/"+cfg.get("auth", "db_db")

        addr = ''
        port = 9166
        if "net" in cfg.sections():
            if "addr" in cfg.options("net"):
                addr = cfg.get("net", "addr")
            if "port" in cfg.options("net"):
                port = int(cfg.get("net", "port"))
        from declarlocker.net import site, CheckConnectionFactory

        reactor.listenTCP(port, site(is_db), interface=addr)
        reactor.listenTCP(port + 1, CheckConnectionFactory(), interface=addr)
    except NoSectionError as e:
        logging.critical("Wrong config file: %s", e.message)
        quit()
    except NoOptionError as e:
        logging.critical(e.message)
        quit()


if __name__ == "__main__":
    logging.basicConfig(level=INFO, format='%(asctime)s %(module)s(%(lineno)d): %(levelname)s: %(message)s')
    logging.root.name = "dcllocksrv"
    logging.addLevelName(DEBUG, "debug")
    logging.addLevelName(INFO, "info")
    logging.addLevelName(WARNING, "warn")
    logging.addLevelName(WARNING, "warning")
    logging.addLevelName(ERROR, "error")
    logging.addLevelName(CRITICAL, "critical")

    set_config(parse_args())

    reactor.run()
