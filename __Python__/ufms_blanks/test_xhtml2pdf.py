#!/bin/env python
# -*- coding: utf-8 -*-

__author__ = 'Savenko'

from xhtml2pdf import pisa

res = open("test.pdf", "wb")
status = pisa.CreatePDF(open(u"templates/адресный листок убытия.html", "rb").read(-1), dest=res)
res.close()
print(status.err)
