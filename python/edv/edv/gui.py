from PyQt5.QtWidgets import QMainWindow
from os import getenv, putenv
from PyQt5.QtQml import QQmlEngine, QQmlComponent
from PyQt5.QtCore import QUrl, Qt
from PyQt5.QtGui import QWindow, QIcon

__author__ = 'Savenko Mike'


class EdvWindow(QMainWindow):
    def __init__(self, title=u"Электронный документ"):
        super().__init__()
        self.setWindowTitle(title)
        self.setWindowModality(Qt.ApplicationModal)
        self.setIcon(QIcon("./edv/ElectroDocViewer.png"))

    def scan(self):
        from edv import scanner


class EdvQmlWindow(QMainWindow):
    def __init__(self, title=u"Электронный документ"):
        super().__init__()

        env = getenv("QML2_IMPORT_PATH")
        if env is None:
            env = ""
        else:
            env += ";"
        env += "./qml"
        putenv("QML2_IMPORT_PATH", env)

        self.engine = QQmlEngine()
        self.component = QQmlComponent(self.engine)
        import PyPlugin

        self.component.loadUrl(QUrl(u"./edv/main.qml"))
        if not self.component.isReady():
            for error in self.component.errors():
                print(error.toString())

        self.window = self.component.create()

        assert isinstance(self.window, QWindow)
        self.window.setIcon(QIcon("./edv/ElectroDocViewer.png"))
        self.window.setTitle(title)

    def show(self):
        self.window.show()
