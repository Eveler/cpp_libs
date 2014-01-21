"""WIA backend.

$Id$"""

import logging
import win32com.client as Com
from win32com.universal import com_error
from ....imagescanner.backends import base


class ScannerManager(base.ScannerManager):
    def __init__(self):
        super().__init__()

    def _refresh(self):
        self._devices = []
        wia = Com.Dispatch("WIA.CommonDialog")
        scanner_id = 'wia-%s' % len(self._devices)
        try:
            dev = wia.ShowSelectDevice()
            scanner = Scanner(scanner_id, wia, dev)
            self._devices.append(scanner)
        except Exception as exc:
            logging.warning(exc)


class Scanner(base.Scanner):
    WIA_IMG_FORMAT_PNG = "{B96B3CAF-0728-11D3-9D7B-0000F81EF32E}"
    WIA_IMG_FORMAT_BMP = "{B96B3CAB-0728-11D3-9D7B-0000F81EF32E}"
    WIA_IMG_FORMAT_GIF = "{B96B3CB0-0728-11D3-9D7B-0000F81EF32E}"
    WIA_IMG_FORMAT_JPG = "{B96B3CAE-0728-11D3-9D7B-0000F81EF32E}"
    WIA_IMG_FORMAT_TIFF = "{B96B3CB1-0728-11D3-9D7B-0000F81EF32E}"
    wiaEventItemCreated = "{4C8F4EF5-E14F-11D2-B326-00C04F68CE61}"

    def __init__(self, scanner_id, source_name, device):
        self.id = scanner_id
        self._source_name = source_name
        self._device = device

        # for p in device.Properties:
        #     print(p.Name, " (", p.PropertyID, ") = ", p.Value)
        self.name = device.Properties["Name"]
        self.manufacturer = device.Properties["Manufacturer"]
        self.description = device.Properties["Description"]
        # self._src_manager = None
        # self._scanner = None
        self._img_format = self.WIA_IMG_FORMAT_PNG
        self.images = []
        self._device_manager = Com.Dispatch("WIA.DeviceManager")

    def __repr__(self):
        return '<%s: %s - %s>' % (self.id, self.manufacturer, self.name)

    def scan(self, dpi=200):
        try:
            self._device_manager.RegisterEvent(self.wiaEventItemCreated)
            # self._device_manager.OnEvent[0] = self.__onevent__
            items = self._source_name.ShowSelectItems(self._device, 0, 0, False)
            if items is None:
                return None
            self.images = []
            # for item in items:
            #     # image = item.Transfer(self._img_format)
            #     image = self._source_name.ShowTransfer(item, self._img_format)
            #     self.images.append(image)

            return self.images
        except com_error as e:
            logging.fatal(e.__str__())

        return None

    def status(self):
        pass

    def __onevent__(self, event_id, dev_id, item_id):
        dev = self._device_manager.DeviceInfos(dev_id).Connect
        item = dev.GetItem(item_id)
        image = self._source_name.ShowTransfer(item)
        self.images.append(image)
