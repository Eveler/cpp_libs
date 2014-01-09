from PyQt5.QtWidgets import QMainWindow

__author__ = 'Savenko Mike'


class EdvWindow(QMainWindow):
    def __init__(self):
        super.__init__()
        from edv import scanner
