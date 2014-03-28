#!/bin/env python -O
# -*- coding: utf-8 -*-
import logging
from logging import DEBUG
from optparse import OptionParser

from declarlocker.objects import DeclarLock, session


__author__ = 'mike'

logging.basicConfig(level=DEBUG)
logging.root.name = "dcllocksrv"

usage = """usage: %prog [options]"""
parser = OptionParser(usage)
parser.add_option("--config", help="configuration file", default="/etc/dcllocksev.ini")
options, args = parser.parse_args()
logging.debug("options = %s, args = %s", options, args)
config = options.config
logging.debug("config = %s" % config)



lock = DeclarLock(1, "declars", "mike")
session.add(lock)
session.commit()
print(lock)
