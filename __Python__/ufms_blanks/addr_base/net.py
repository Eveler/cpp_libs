# -*- coding: utf-8 -*-
from urllib.request import urlopen

__author__ = 'Savenko'

BLOCK_SIZE = 4096


def load(url, file_name=None, progress_proc=None):
    f = urlopen(url)
    size = f.length
    res = bytes()

    if file_name is not None:
        if isinstance(file_name, file):
            fp = file_name
        else:
            fp = open(file_name, "wb")
    else:
        fp = None

    length = 0
    while True:
        data = f.read(BLOCK_SIZE)
        if not data:
            break
        if fp is None:
            res += data
        else:
            fp.write(data)

        length += len(data)
        print("Downloaded: %s of %s" % (length, size))
        if progress_proc is not None:
            progress_proc(size, length)

    if fp is None:
        return res
    else:
        return fp
