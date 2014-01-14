#!/bin/env python -O
# -*- coding: utf-8 -*-
import sys

from PyQt5.QtCore import QUrl
from PyQt5.QtQml import QQmlEngine, QQmlComponent, qmlRegisterType
from PyQt5.QtWidgets import QApplication
from edv.scanner import MyClass


__author__ = 'Savenko Mike'


if __name__ == "__main__":
    app = QApplication(sys.argv)
    # from edv.window import EdvWindow
    # w = EdvWindow()
    # w.show()
    engine = QQmlEngine()
    component = QQmlComponent(engine)
    m = MyClass()
    # engine.rootContext().setContextProperty("MyClass", m)
    qmlRegisterType(MyClass, 'PyPlugin', 1, 0, 'MyClass')

    component.loadUrl(QUrl("main.qml"))
    if not component.isReady():
        for error in component.errors():
            print(error.toString())

    window = component.create()
    window.show()

    app.exec()

    # import win32com.client
    #
    # WIA_IMG_FORMAT_PNG = "{B96B3CAF-0728-11D3-9D7B-0000F81EF32E}"
    # # WIA_COMMAND_TAKE_PICTURE = "{AF933CAC-ACAD-11D2-A093-00C04F72DC3C}"
    #
    # # os.chdir('c:/temp')
    # wia = win32com.client.Dispatch("WIA.CommonDialog")
    # dev = wia.ShowSelectDevice()
    # items = wia.ShowSelectItems(dev)
    #
    # image = items[0].Transfer(WIA_IMG_FORMAT_PNG)
    # from os import remove
    # from os.path import exists
    #
    # if exists("test.png"):
    #     remove("test.png")
    # image.SaveFile("test.png")
