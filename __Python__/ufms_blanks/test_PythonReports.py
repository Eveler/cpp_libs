#!/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'Savenko'


def run():
    # make some dummy data

    _data = [{

                 "item": _ii,

                 "sub": [{"item": _jj} for _jj in xrange(_ii * 10, _ii * 10 + 10)]

             } for _ii in xrange(10)]

    # create report builder
    from PythonReports.builder import Builder

    _builder = Builder("submain.prt")

    # build printout

    _printout = _builder.run(_data)

    # write printout file

    _out = file("submain.prp", "w")

    _printout.write(_out)
    _printout.validate()
    from PythonReports.pdf import write

    write(_printout, "result.pdf")

    _out.close()


run()
from PythonReports.editor import editor

editor.main()
