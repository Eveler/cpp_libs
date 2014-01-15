from PyQt5.QtCore import pyqtSlot, QObject
from PyQt5.QtQml import qmlRegisterType
from PyQt5.QtWidgets import QMessageBox

__author__ = 'mike'


class MyClass(QObject):
    def __init__(self, parent=None):
        super().__init__(parent)

    @pyqtSlot()
    def p(self):
        QMessageBox.information(self.parent(), u"Опа", u"Батончик нажали o_O")

qmlRegisterType(MyClass, "PyPlugin", 1, 0, "MyClass")
