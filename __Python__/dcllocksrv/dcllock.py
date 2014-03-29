#!/bin/env python -O
# -*- coding: utf-8 -*-
from ConfigParser import SafeConfigParser
import logging
from logging import DEBUG, INFO, WARNING, CRITICAL, ERROR
from optparse import OptionParser

from declarlocker.objects import DeclarLock, session


__author__ = 'mike'

logging.basicConfig(level=DEBUG, format='%(asctime)s %(levelname)s: %(module)s(%(lineno)d): %(message)s')
logging.root.name = "dcllocksrv"
logging.addLevelName(DEBUG, "debug")
logging.addLevelName(INFO, "info")
logging.addLevelName(WARNING, "warn")
logging.addLevelName(WARNING, "warning")
logging.addLevelName(ERROR, "error")
logging.addLevelName(CRITICAL, "critical")

usage = """usage: %prog [options]"""
parser = OptionParser(usage)
parser.add_option("--config", help="configuration file", default="/etc/dcllocksev.ini")
options, args = parser.parse_args()
logging.debug("options = %s, args = %s", options, args)
config = options.config
logging.debug("config = %s" % config)

cfg = SafeConfigParser()
lst = cfg.read(config)
logging.debug("successfuly read: %s", lst)
logging.debug("sections: %s", cfg.sections())
[logging.debug("section [%s] options: %s", section, cfg.options(section)) for section in cfg.sections()]
for section in cfg.sections():
    for option in cfg.options(section):
        logging.debug("%s.%s = %s", section, option, cfg.get(section, option))
if "loglevel" in cfg.options("main"):
    logging.info("Set loggin level to '%s'", cfg.get("main", "loglevel"))
    logging.root.setLevel(cfg.get("main", "loglevel"))
logging.debug("debug level test")
logging.info("info level test")
logging.warning("warning level test")
logging.error("error level test")
logging.critical("critical level test")

lock = DeclarLock(1, "declars", "mike")
session.add(lock)
session.commit()
print(lock)
