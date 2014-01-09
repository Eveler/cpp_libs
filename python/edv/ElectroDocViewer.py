#!/bin/env python -O
# -*- coding: utf-8 -*-

try:
    from PyQt5.QtWidgets import QApplication
except ImportError:
    from PyQt4.QtGui import QApplication
import sys

__author__ = 'Savenko Mike'

if __name__ == "__main__":
    # app = QApplication(sys.argv)
    # from edv.window import EdvWindow
    # w = EdvWindow()
    # w.show()
    # app.exec()


    import win32com.client

    WIA_IMG_FORMAT_PNG = "{B96B3CAF-0728-11D3-9D7B-0000F81EF32E}"
    WIA_COMMAND_TAKE_PICTURE = "{AF933CAC-ACAD-11D2-A093-00C04F72DC3C}"

    # os.chdir('c:/temp')
    wia = win32com.client.Dispatch("WIA.CommonDialog")
    dev = wia.ShowSelectDevice()
    items = wia.ShowSelectItems(dev)
    # for command in dev.Commands:
    #     # if command.CommandID == WIA_COMMAND_TAKE_PICTURE:
    #     #     foo = dev.ExecuteCommand(WIA_COMMAND_TAKE_PICTURE)
    #     print(command.CommandID)
    # i = 1
    # for item in dev.Items:
    #     if i == dev.Items.Count:
    #         # image = item.Transfer(WIA_IMG_FORMAT_PNG)
    #         break
    #     i += 1

    image = items[0].Transfer(WIA_IMG_FORMAT_PNG)
    from os import remove
    from os.path import exists
    if exists("test.png"):
        remove("test.png")
    image.SaveFile("test.png")
