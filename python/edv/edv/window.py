from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QMainWindow

__author__ = 'Savenko Mike'


class EdvWindow(QMainWindow):
    def __init__(self, title=u"Электронный документ"):
        super().__init__()
        self.setWindowTitle(title)
        # self.setWindowModality(Qt.ApplicationModal)

    def scan(self):
        from edv import scanner
