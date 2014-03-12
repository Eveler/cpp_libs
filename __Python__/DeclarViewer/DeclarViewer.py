from PyQt5.QtCore import QUrl
from PyQt5.QtQml import QQmlComponent, QQmlError, QQmlApplicationEngine
from PyQt5.QtWidgets import QApplication
import OpenGL
import sys

__author__ = 'Михаил'

OpenGL.
app = QApplication(sys.argv)
engine = QQmlApplicationEngine()
engine.rootContext()
component = QQmlComponent(engine)
component.loadUrl(QUrl.fromLocalFile("DeclarViewer.qml"))
if not component.isReady():
    for error in component.errors():
        assert isinstance(error, QQmlError)
        print(error.toString())
window = component.create()
window.show()
app.exec()
