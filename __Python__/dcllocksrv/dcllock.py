#!/bin/env python -O
# -*- coding: utf-8 -*-
from optparse import OptionParser

from declarlocker.objects import DeclarLock, session


__author__ = 'mike'

usage = """usage: %prog [options]"""
parser = OptionParser(usage)
parser.add_option("--config", help="configuration file", default="/etc/dcllocksev.ini")
options, args = parser.parse_args()
print(options)
print(args)
# if len(args)==1:
config = options.config
# else:
#     config = "/etc/dcllocksev.ini"
print("config = %s" % config)

lock = DeclarLock(1, "declars", "mike")
session.add(lock)
session.commit()
print(lock)
