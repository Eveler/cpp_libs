# -*- coding: utf-8 -*-
import logging
from traceback import print_exc
from os.path import expanduser
from os import mkdir

try:
    from ConfigParser import ConfigParser
except ImportError:
    from configparser import ConfigParser

__author__ = 'Savenko'


class UfmsConfig:
    def __init__(self):
        self.options = {
            "main": {
                "logfile": u"~/.ufms_blanks/logs/ufms_blanks.log",
                "log_count": 7,
                "log_encoding": 'utf-8'
            },
            "db": {
                "data_dir": "~/.ufms_blanks",
                "type": "sqlite",
                "db": "ufms.db"
            }
        }
        self.file_name = u"~/.ufms_blanks/ufms_blanks.ini"
        try:
            mkdir(expanduser(u"~/.ufms_blanks"))
        except:
            pass
        try:
            mkdir(expanduser(u"~/.ufms_blanks/logs"))
        except:
            pass
        self.cfg = ConfigParser()
        self._read()

        if "main" in self.options:
            backupcount = int(self.options["main"]["log_count"]) if "log_count" in self.options["main"] else 7
            logfile = self.options["main"]["logfile"]
            log_encoding = self.options["main"]["log_encoding"]
            from logging.handlers import TimedRotatingFileHandler

            handler = TimedRotatingFileHandler(expanduser(logfile), when='D', backupCount=backupcount,
                                               encoding=log_encoding)
            from logging import Formatter

            handler.setFormatter(Formatter('%(asctime)s %(module)s(%(lineno)d): %(levelname)s: %(message)s'))
            logging.root.addHandler(handler)

        logging.info("Config file: %s" % expanduser(self.file_name))
        if "data_dir" in self.options["db"]:
            from os.path import join

            self.options["db"]["db"] = join(expanduser(self.options["db"]["data_dir"]), self.options["db"]["db"])

        if "~" in self.options["db"]["db"]:
            self.options["db"]["db"] = expanduser(self.options["db"]["db"])

    def _read(self):
        try:
            lst = self.cfg.read(expanduser(self.file_name))
            if lst:
                self.options = {}
                for section in self.cfg.sections():
                    options = {}
                    for option in self.cfg.options(section):
                        options[option] = self.cfg.get(section, option)
                    self.options[section] = options
            else:
                self._write_new()
        except:
            print_exc()

    def _write_new(self):
        for sec_name, section in self.options.items():
            self.cfg.add_section(sec_name)
            for key, value in section.items():
                self.cfg.set(sec_name, key, str(value))

        with open(expanduser(self.file_name), 'w') as cfgfile:
            self.cfg.write(cfgfile)
            cfgfile.close()
