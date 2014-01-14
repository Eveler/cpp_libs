"""Twain backend.

$Id$"""

import logging
import pywintypes
from twain import excSMOpenFailed
import win32com.client, os
# from StringIO import StringIO

# import Image
from win32com.universal import com_error

try:
    import twain
except ImportError:
    logging.warning(u"Falling back to WIA")
    twain = None
from ....imagescanner.backends import base


class ScannerManager(base.ScannerManager):
    def __init__(self):
        super().__init__()
        self.WIA_IMG_FORMAT_PNG = "{B96B3CAF-0728-11D3-9D7B-0000F81EF32E}"

    def _refresh(self):
        self._devices = []
        devices = []
        try:
            if not twain is None:
                src_manager = twain.SourceManager(0)
                devices = src_manager.GetSourceList()
        except excSMOpenFailed as e:
            logging.warning(e.__str__())
            logging.debug(u"Falling back to WIA")
            src_manager = None
        if devices.__len__() == 0:
            wia = win32com.client.Dispatch("WIA.CommonDialog")
            try:
                dev = wia.ShowSelectDevice()
                devices.append(dev)
            except com_error as e:
                logging.fatal(e.__str__())
        for dev in devices:
            scanner_id = 'twain-%s' % len(self._devices)
            try:
                scanner = Scanner(scanner_id, dev)
                self._devices.append(scanner)
            except Exception as exc:
                # XXX: What should be here?
                # Debuging to try to find out
                logging.debug(exc)
        if src_manager:
            src_manager.destroy()


class Scanner(base.Scanner):
    def __init__(self, scanner_id, source_name):
        self.id = scanner_id
        self._source_name = source_name

        self.name = None
        self.manufacturer = None
        self.description = None
        self._src_manager = None
        self._scanner = None

        self._open()
        self._get_identity()
        self._close()

    def _get_identity(self):
        identity = self._scanner.GetIdentity()
        self.name = identity.get('ProductName')
        self.manufacturer = identity.get('Manufacturer')
        self.description = None

    def _open(self):
        self._src_manager = twain.SourceManager(0)
        self._scanner = self._src_manager.OpenSource(self._source_name)
        self._scanner.SetCapability(twain.ICAP_YRESOLUTION,
                                    twain.TWTY_FIX32, 200.0)

    def __repr__(self):
        return '<%s: %s - %s>' % (self.id, self.manufacturer, self.name)

    def scan(self, dpi=200):
        self._open()
        self._scanner.RequestAcquire(0, 0)
        info = self._scanner.GetImageInfo()
        if info:
            (handle, more_to_come) = self._scanner.XferImageNatively()
            str_image = twain.DIBToBMFile(handle)
            twain.GlobalHandleFree(handle)
            self._close()
            return Image.open(StringIO(str_image))

        self._close()
        return None

    def _close(self):
        self._scanner.destroy()
        self._src_manager.destroy()

    def status(self):
        pass
