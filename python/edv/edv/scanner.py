__author__ = 'Savenko Mike'


from .imagescanner import ImageScanner
s = ImageScanner()
scanners = s.list_scanners()
# images = s.get_scanner('wia-0').scan()
images = scanners[0].scan()
if not images is None:
    i = 0
    for image in images:
        from os import remove
        from os.path import exists

        if exists("test%s.png" % i):
            remove("test%s.png" % i)
        image.SaveFile("test%s.png" % i)
        i += 1