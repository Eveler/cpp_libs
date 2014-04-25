#!/bin/env python
# -*- coding: utf-8 -*-
from logging.handlers import TimedRotatingFileHandler
from twisted.internet import reactor
from twisted.python import log
from twisted.python.logfile import DailyLogFile


try:
    from ConfigParser import SafeConfigParser, NoSectionError
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
    parser.add_option("--config", help="configuration file", default="/etc/dcllocksev.ini")
    options, args = parser.parse_args()
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
        observer = log.PythonLoggingObserver()
        observer.start()
        if "logfile" in cfg.options("main"):
            # log.startLogging(DailyLogFile.fromFullPath(cfg.get("main", "logfile")))
            handler = TimedRotatingFileHandler(cfg.get("main", "logfile"), when='D', backupCount=5)
            handler.setFormatter(Formatter('%(asctime)s %(module)s(%(lineno)d): %(levelname)s: %(message)s'))
            logging.root.addHandler(handler)
        logging.info("config = %s" % config)
        if "loglevel" in cfg.options("main"):
            logging.info("Set logging level to '%s'", cfg.get("main", "loglevel"))
            logging.root.setLevel(cfg.get("main", "loglevel"))
    except NoSectionError:
        logging.critical("Wrong config file")
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

    from declarlocker.base import session
    from declarlocker.net import site

    # tests here
    from declarlocker.objects import DeclarLock

    lock = DeclarLock(18646, "declars", "mike")
    session.add(lock)
    session.commit()
    print(lock)

    PORT = 9166

    reactor.listenTCP(PORT, site)
    reactor.run()
