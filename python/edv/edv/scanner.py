from PyQt5.QtCore import QObject, pyqtSlot

__author__ = 'Savenko Mike'


class MyClass(QObject):
    def __init__(self, parent=None):
        super().__init__(parent)

    @pyqtSlot()
    def p(self):
        print("Hello")


from .imagescanner import ImageScanner
s = ImageScanner()
scanners = s.list_scanners()
print("Scanners found: %s" % scanners)
