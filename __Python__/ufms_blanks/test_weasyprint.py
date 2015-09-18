#!/bin/env python
# -*- coding: utf-8 -*-

__author__ = 'Savenko'

from weasyprint import HTML

HTML(u"templates/адресный листок убытия.html").write_pdf("test.pdf")
