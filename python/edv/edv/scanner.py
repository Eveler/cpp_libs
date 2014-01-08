__author__ = 'Savenko'

from .imagescanner import ImageScanner

s = ImageScanner()
scanners = s.list_scanners()
print("Scanners found: %s" % scanners)
