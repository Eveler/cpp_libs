from PyQt5.QtCore import QUrl
from PyQt5.QtQml import QQmlEngine, QQmlComponent, QQmlError
from PyQt5.QtWidgets import QApplication
import sys

__author__ = 'Михаил'

app = QApplication(sys.argv)
engine = QQmlEngine()
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
