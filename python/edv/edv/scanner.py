__author__ = 'Savenko Mike'


from .imagescanner import ImageScanner
s = ImageScanner()
scanners = s.list_scanners()
print("Scanners found: %s" % scanners)
