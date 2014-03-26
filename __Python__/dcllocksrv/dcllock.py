#!/bin/env python -O
# -*- coding: utf-8 -*-
from declarlocker.objects import DeclarLock

__author__ = 'mike'

lock = DeclarLock()
print(lock)
print(lock.__table__)
print(lock.metadata)
