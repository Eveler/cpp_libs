#!/bin/env python
# -*- coding: utf-8 -*-

__author__ = 'Savenko'

from sys import path
from os import getcwd

path.insert(0, getcwd() + "/appy2")
path.insert(0, "C:\\Program Files (x86)\\LibreOffice 4\\program")
from appy.pod.renderer import Renderer

field = u"Поле 1"
field_n = u"Поле 2"
do_show = True
i = 0

renderer = Renderer("SimpleTest.odt", globals(), "result.pdf", "C:/PROGRA~2/LIBREO~2/program/PYTHON~1.3/bin/python.exe",
                    overwriteExisting=True)
print("******************* renderer created *************************")
# renderer = Renderer("SimpleTest.odt", globals(), "result.odt")
renderer.run()
