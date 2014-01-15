#!/bin/env python -O
# -*- coding: utf-8 -*-
from os import getenv, putenv
import sys

from PyQt5.QtCore import QUrl
from PyQt5.QtGui import QWindow, QIcon
from PyQt5.QtQml import QQmlEngine, QQmlComponent
from PyQt5.QtWidgets import QApplication
# from edv.scanner import MyClass


__author__ = 'Savenko Mike'


if __name__ == "__main__":
    env = getenv("QML2_IMPORT_PATH")
    if env is None:
        env = ""
    else:
        env += ";"
    env += ".\qml"
    putenv("QML2_IMPORT_PATH", env)
    env = getenv("QML2_IMPORT_PATH")

    app = QApplication(sys.argv)
    # from edv.window import EdvWindow
    # w = EdvWindow()
    # w.show()
    engine = QQmlEngine()
    component = QQmlComponent(engine)
    import PyPlugin
    component.loadUrl(QUrl("main.qml"))
    if not component.isReady():
        for error in component.errors():
            print(error.toString())

    window = component.create()
    assert isinstance(window, QWindow)
    window.setIcon(QIcon("./ElectroDocViewer.png"))
    window.show()

    app.exec()

    # # WIA_COMMAND_TAKE_PICTURE = "{AF933CAC-ACAD-11D2-A093-00C04F72DC3C}"
    #
    # # os.chdir('c:/temp')
    # items = wia.ShowSelectItems(dev)
    #
    # image = items[0].Transfer(WIA_IMG_FORMAT_PNG)
    # from os import remove
    # from os.path import exists
    #
    # if exists("test.png"):
    #     remove("test.png")
    # image.SaveFile("test.png")
