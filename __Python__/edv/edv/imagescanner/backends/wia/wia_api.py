# -*- coding: mbcs -*-
# Created by makepy.py version 0.5.01
# By python version 3.3.2 (default, Sep 16 2013, 23:10:06) [MSC v.1600 32 bit (Intel)]
# From type library 'wiaaut.dll'
# On Thu Jan 23 19:23:23 2014
'Microsoft Windows Image Acquisition Library v2.0'
makepy_version = '0.5.01'
python_version = 0x30302f0

import win32com.client.CLSIDToClass, pythoncom, pywintypes
import win32com.client.util
# from pywintypes import IID
from win32com.client import Dispatch

# The following 3 lines may need tweaking for the particular server
# Candidates are pythoncom.Missing, .Empty and .ArgNotFound
defaultNamedOptArg=pythoncom.Empty
defaultNamedNotOptArg=pythoncom.Empty
defaultUnnamedArg=pythoncom.Empty

# CLSID = IID('{94A0E92D-43C0-494E-AC29-FD45948A5221}')
CLSID = '{94A0E92D-43C0-494E-AC29-FD45948A5221}'
MajorVersion = 1
MinorVersion = 0
LibraryFlags = 8
LCID = 0x0

class constants:
    wiaCommandChangeDocument      ='{04E725B0-ACAE-11D2-A093-00C04F72DC3C}' # from enum CommandID
    wiaCommandDeleteAllItems      ='{E208C170-ACAD-11D2-A093-00C04F72DC3C}' # from enum CommandID
    wiaCommandSynchronize         ='{9B26B7B2-ACAD-11D2-A093-00C04F72DC3C}' # from enum CommandID
    wiaCommandTakePicture         ='{AF933CAC-ACAD-11D2-A093-00C04F72DC3C}' # from enum CommandID
    wiaCommandUnloadDocument      ='{1F3B3D8E-ACAE-11D2-A093-00C04F72DC3C}' # from enum CommandID
    wiaEventDeviceConnected       ='{A28BBADE-64B6-11D2-A231-00C04FA31809}' # from enum EventID
    wiaEventDeviceDisconnected    ='{143E4E83-6497-11D2-A231-00C04FA31809}' # from enum EventID
    wiaEventItemCreated           ='{4C8F4EF5-E14F-11D2-B326-00C04F68CE61}' # from enum EventID
    wiaEventItemDeleted           ='{1D22A559-E14F-11D2-B326-00C04F68CE61}' # from enum EventID
    wiaEventScanEmailImage        ='{C686DCEE-54F2-419E-9A27-2FC7F2E98F9E}' # from enum EventID
    wiaEventScanFaxImage          ='{C00EB793-8C6E-11D2-977A-0000F87A926F}' # from enum EventID
    wiaEventScanFilmImage         ='{9B2B662C-6185-438C-B68B-E39EE25E71CB}' # from enum EventID
    wiaEventScanImage             ='{A6C5A715-8C6E-11D2-977A-0000F87A926F}' # from enum EventID
    wiaEventScanImage2            ='{FC4767C1-C8B3-48A2-9CFA-2E90CB3D3590}' # from enum EventID
    wiaEventScanImage3            ='{154E27BE-B617-4653-ACC5-0FD7BD4C65CE}' # from enum EventID
    wiaEventScanImage4            ='{A65B704A-7F3C-4447-A75D-8A26DFCA1FDF}' # from enum EventID
    wiaEventScanOCRImage          ='{9D095B89-37D6-4877-AFED-62A297DC6DBE}' # from enum EventID
    wiaEventScanPrintImage        ='{B441F425-8C6E-11D2-977A-0000F87A926F}' # from enum EventID
    wiaFormatBMP                  ='{B96B3CAB-0728-11D3-9D7B-0000F81EF32E}' # from enum FormatID
    wiaFormatGIF                  ='{B96B3CB0-0728-11D3-9D7B-0000F81EF32E}' # from enum FormatID
    wiaFormatJPEG                 ='{B96B3CAE-0728-11D3-9D7B-0000F81EF32E}' # from enum FormatID
    wiaFormatPNG                  ='{B96B3CAF-0728-11D3-9D7B-0000F81EF32E}' # from enum FormatID
    wiaFormatTIFF                 ='{B96B3CB1-0728-11D3-9D7B-0000F81EF32E}' # from enum FormatID
    wiaAnyDeviceID                ='*'        # from enum Miscellaneous
    wiaIDUnknown                  ='{00000000-0000-0000-0000-000000000000}' # from enum Miscellaneous
    CameraDeviceType              =2          # from enum WiaDeviceType
    ScannerDeviceType             =1          # from enum WiaDeviceType
    UnspecifiedDeviceType         =0          # from enum WiaDeviceType
    VideoDeviceType               =3          # from enum WiaDeviceType
    ActionEvent                   =2          # from enum WiaEventFlag
    NotificationEvent             =1          # from enum WiaEventFlag
    MaximizeQuality               =131072     # from enum WiaImageBias
    MinimizeSize                  =65536      # from enum WiaImageBias
    ColorIntent                   =1          # from enum WiaImageIntent
    GrayscaleIntent               =2          # from enum WiaImageIntent
    TextIntent                    =4          # from enum WiaImageIntent
    UnspecifiedIntent             =0          # from enum WiaImageIntent
    ByteImagePropertyType         =1001       # from enum WiaImagePropertyType
    LongImagePropertyType         =1004       # from enum WiaImagePropertyType
    RationalImagePropertyType     =1006       # from enum WiaImagePropertyType
    StringImagePropertyType       =1002       # from enum WiaImagePropertyType
    UndefinedImagePropertyType    =1000       # from enum WiaImagePropertyType
    UnsignedIntegerImagePropertyType=1003       # from enum WiaImagePropertyType
    UnsignedLongImagePropertyType =1005       # from enum WiaImagePropertyType
    UnsignedRationalImagePropertyType=1007       # from enum WiaImagePropertyType
    VectorOfBytesImagePropertyType=1101       # from enum WiaImagePropertyType
    VectorOfLongsImagePropertyType=1103       # from enum WiaImagePropertyType
    VectorOfRationalsImagePropertyType=1105       # from enum WiaImagePropertyType
    VectorOfUndefinedImagePropertyType=1100       # from enum WiaImagePropertyType
    VectorOfUnsignedIntegersImagePropertyType=1102       # from enum WiaImagePropertyType
    VectorOfUnsignedLongsImagePropertyType=1104       # from enum WiaImagePropertyType
    VectorOfUnsignedRationalsImagePropertyType=1106       # from enum WiaImagePropertyType
    AnalyzeItemFlag               =16         # from enum WiaItemFlag
    AudioItemFlag                 =32         # from enum WiaItemFlag
    BurstItemFlag                 =2048       # from enum WiaItemFlag
    DeletedItemFlag               =128        # from enum WiaItemFlag
    DeviceItemFlag                =64         # from enum WiaItemFlag
    DisconnectedItemFlag          =256        # from enum WiaItemFlag
    FileItemFlag                  =2          # from enum WiaItemFlag
    FolderItemFlag                =4          # from enum WiaItemFlag
    FreeItemFlag                  =0          # from enum WiaItemFlag
    GeneratedItemFlag             =16384      # from enum WiaItemFlag
    HPanoramaItemFlag             =512        # from enum WiaItemFlag
    HasAttachmentsItemFlag        =32768      # from enum WiaItemFlag
    ImageItemFlag                 =1          # from enum WiaItemFlag
    RemovedItemFlag               =-2147483648 # from enum WiaItemFlag
    RootItemFlag                  =8          # from enum WiaItemFlag
    StorageItemFlag               =4096       # from enum WiaItemFlag
    TransferItemFlag              =8192       # from enum WiaItemFlag
    VPanoramaItemFlag             =1024       # from enum WiaItemFlag
    VideoItemFlag                 =65536      # from enum WiaItemFlag
    BooleanPropertyType           =1          # from enum WiaPropertyType
    BytePropertyType              =2          # from enum WiaPropertyType
    ClassIDPropertyType           =15         # from enum WiaPropertyType
    CurrencyPropertyType          =12         # from enum WiaPropertyType
    DatePropertyType              =13         # from enum WiaPropertyType
    DoublePropertyType            =11         # from enum WiaPropertyType
    ErrorCodePropertyType         =7          # from enum WiaPropertyType
    FileTimePropertyType          =14         # from enum WiaPropertyType
    HandlePropertyType            =18         # from enum WiaPropertyType
    IntegerPropertyType           =3          # from enum WiaPropertyType
    LargeIntegerPropertyType      =8          # from enum WiaPropertyType
    LongPropertyType              =5          # from enum WiaPropertyType
    ObjectPropertyType            =17         # from enum WiaPropertyType
    SinglePropertyType            =10         # from enum WiaPropertyType
    StringPropertyType            =16         # from enum WiaPropertyType
    UnsignedIntegerPropertyType   =4          # from enum WiaPropertyType
    UnsignedLargeIntegerPropertyType=9          # from enum WiaPropertyType
    UnsignedLongPropertyType      =6          # from enum WiaPropertyType
    UnsupportedPropertyType       =0          # from enum WiaPropertyType
    VariantPropertyType           =19         # from enum WiaPropertyType
    VectorOfBooleansPropertyType  =101        # from enum WiaPropertyType
    VectorOfBytesPropertyType     =102        # from enum WiaPropertyType
    VectorOfClassIDsPropertyType  =115        # from enum WiaPropertyType
    VectorOfCurrenciesPropertyType=112        # from enum WiaPropertyType
    VectorOfDatesPropertyType     =113        # from enum WiaPropertyType
    VectorOfDoublesPropertyType   =111        # from enum WiaPropertyType
    VectorOfErrorCodesPropertyType=107        # from enum WiaPropertyType
    VectorOfFileTimesPropertyType =114        # from enum WiaPropertyType
    VectorOfIntegersPropertyType  =103        # from enum WiaPropertyType
    VectorOfLargeIntegersPropertyType=108        # from enum WiaPropertyType
    VectorOfLongsPropertyType     =105        # from enum WiaPropertyType
    VectorOfSinglesPropertyType   =110        # from enum WiaPropertyType
    VectorOfStringsPropertyType   =116        # from enum WiaPropertyType
    VectorOfUnsignedIntegersPropertyType=104        # from enum WiaPropertyType
    VectorOfUnsignedLargeIntegersPropertyType=109        # from enum WiaPropertyType
    VectorOfUnsignedLongsPropertyType=106        # from enum WiaPropertyType
    VectorOfVariantsPropertyType  =119        # from enum WiaPropertyType
    FlagSubType                   =3          # from enum WiaSubType
    ListSubType                   =2          # from enum WiaSubType
    RangeSubType                  =1          # from enum WiaSubType
    UnspecifiedSubType            =0          # from enum WiaSubType

from win32com.client import DispatchBaseClass


class ICommonDialog(DispatchBaseClass):
    # CLSID = IID('{B4760F13-D9F3-4DF8-94B5-D225F86EE9A1}')
    CLSID = '{B4760F13-D9F3-4DF8-94B5-D225F86EE9A1}'
    # coclass_clsid = IID('{850D1D11-70F3-4BE5-9A11-77AA6B2BB201}')
    coclass_clsid = '{850D1D11-70F3-4BE5-9A11-77AA6B2BB201}'

    # Result is of type IImageFile
    def ShowAcquireImage(self, DeviceType=0, Intent=0, Bias=131072, FormatID='{00000000-0000-0000-0000-000000000000}'
            , AlwaysSelectDevice=False, UseCommonUI=True, CancelError=False):
        'Displays one or more dialog boxes that enable the user to acquire an image from a hardware device for image acquisition and returns an ImageFile object on success, otherwise Nothing'
        return self._ApplyTypes_(2, 1, (9, 32), ((3, 49), (3, 49), (3, 49), (8, 49), (11, 49), (11, 49), (11, 49)), 'ShowAcquireImage', '{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}',DeviceType
            , Intent, Bias, FormatID, AlwaysSelectDevice, UseCommonUI
            , CancelError)

    def ShowAcquisitionWizard(self, Device=defaultNamedNotOptArg):
        'Launches the Windows Scanner and Camera Wizard and returns Nothing. Future versions may return a collection of ImageFile objects.'
        return self._ApplyTypes_(1, 1, (12, 0), ((9, 1),), 'ShowAcquisitionWizard', None,Device
            )

    def ShowDeviceProperties(self, Device=defaultNamedNotOptArg, CancelError=False):
        'Displays the properties dialog box for the specified Device'
        return self._oleobj_.InvokeTypes(5, LCID, 1, (24, 0), ((9, 1), (11, 49)),Device
            , CancelError)

    def ShowItemProperties(self, Item=defaultNamedNotOptArg, CancelError=False):
        'Displays the properties dialog box for the specified Item'
        return self._oleobj_.InvokeTypes(6, LCID, 1, (24, 0), ((9, 1), (11, 49)),Item
            , CancelError)

    def ShowPhotoPrintingWizard(self, Files=defaultNamedNotOptArg):
        'Launches the Photo Printing Wizard with the absolute path of a specific file or Vector of absolute paths to files'
        return self._oleobj_.InvokeTypes(8, LCID, 1, (24, 0), ((16396, 1),),Files
            )

    # Result is of type IDevice
    def ShowSelectDevice(self, DeviceType=0, AlwaysSelectDevice=False, CancelError=False):
        'Displays a dialog box that enables the user to select a hardware device for image acquisition. Returns the selected Device object on success, otherwise Nothing'
        ret = self._oleobj_.InvokeTypes(3, LCID, 1, (9, 0), ((3, 49), (11, 49), (11, 49)),DeviceType
            , AlwaysSelectDevice, CancelError)
        if ret is not None:
            ret = Dispatch(ret, 'ShowSelectDevice', '{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}')
        return ret

    # Result is of type IItems
    def ShowSelectItems(self, Device=defaultNamedNotOptArg, Intent=0, Bias=131072, SingleSelect=True
            , UseCommonUI=True, CancelError=False):
        'Displays a dialog box that enables the user to select an item for transfer from a hardware device for image acquisition. Returns the selection as an Items collection on success, otherwise Nothing'
        ret = self._oleobj_.InvokeTypes(4, LCID, 1, (9, 0), ((9, 1), (3, 49), (3, 49), (11, 49), (11, 49), (11, 49)),Device
            , Intent, Bias, SingleSelect, UseCommonUI, CancelError
            )
        if ret is not None:
            ret = Dispatch(ret, 'ShowSelectItems', '{46102071-60B4-4E58-8620-397D17B0BB5B}')
        return ret

    def ShowTransfer(self, Item=defaultNamedNotOptArg, FormatID='{00000000-0000-0000-0000-000000000000}', CancelError=False):
        'Displays a progress dialog box while transferring the specified Item to the local machine. See Item.Transfer for additional information.'
        return self._ApplyTypes_(7, 1, (12, 32), ((9, 1), (8, 49), (11, 49)), 'ShowTransfer', None,Item
            , FormatID, CancelError)

    _prop_map_get_ = {
    }
    _prop_map_put_ = {
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IDevice(DispatchBaseClass):
    # CLSID = IID('{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}')
    CLSID = '{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}'
    # coclass_clsid = IID('{DBAA8843-B1C4-4EDC-B7E0-D6F61162BE58}')
    coclass_clsid = '{DBAA8843-B1C4-4EDC-B7E0-D6F61162BE58}'

    # Result is of type IItem
    def ExecuteCommand(self, CommandID=defaultNamedNotOptArg):
        'Issues the command specified by CommandID to the imaging device. CommandIDs are device dependent. Valid CommandIDs for this Device are contained in the Commands collection.'
        ret = self._oleobj_.InvokeTypes(9, LCID, 1, (9, 0), ((8, 1),),CommandID
            )
        if ret is not None:
            ret = Dispatch(ret, 'ExecuteCommand', '{68F2BF12-A755-4E2B-9BCD-37A22587D078}')
        return ret

    # Result is of type IItem
    def GetItem(self, ItemID=defaultNamedNotOptArg):
        'Returns the Item object specified by ItemID if it exists'
        ret = self._oleobj_.InvokeTypes(8, LCID, 1, (9, 0), ((8, 1),),ItemID
            )
        if ret is not None:
            ret = Dispatch(ret, 'GetItem', '{68F2BF12-A755-4E2B-9BCD-37A22587D078}')
        return ret

    _prop_map_get_ = {
        # Method 'Commands' returns object of type 'IDeviceCommands'
        "Commands": (5, 2, (9, 0), (), "Commands", '{C53AE9D5-6D91-4815-AF93-5F1E1B3B08BD}'),
        "DeviceID": (1, 2, (8, 0), (), "DeviceID", None),
        # Method 'Events' returns object of type 'IDeviceEvents'
        "Events": (6, 2, (9, 0), (), "Events", '{03985C95-581B-44D1-9403-8488B347538B}'),
        # Method 'Items' returns object of type 'IItems'
        "Items": (4, 2, (9, 0), (), "Items", '{46102071-60B4-4E58-8620-397D17B0BB5B}'),
        # Method 'Properties' returns object of type 'IProperties'
        "Properties": (3, 2, (9, 0), (), "Properties", '{40571E58-A308-470A-80AA-FA10F88793A0}'),
        "Type": (2, 2, (3, 0), (), "Type", None),
        "WiaItem": (7, 2, (13, 0), (), "WiaItem", None),
    }
    _prop_map_put_ = {
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IDeviceCommand(DispatchBaseClass):
    # CLSID = IID('{7CF694C0-F589-451C-B56E-398B5855B05E}')
    CLSID = '{7CF694C0-F589-451C-B56E-398B5855B05E}'
    # coclass_clsid = IID('{72226184-AFBB-4059-BF55-0F6C076E669D}')
    coclass_clsid = '{72226184-AFBB-4059-BF55-0F6C076E669D}'

    _prop_map_get_ = {
        "CommandID": (1, 2, (8, 0), (), "CommandID", None),
        "Description": (3, 2, (8, 0), (), "Description", None),
        "Name": (2, 2, (8, 0), (), "Name", None),
    }
    _prop_map_put_ = {
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IDeviceCommands(DispatchBaseClass):
    # CLSID = IID('{C53AE9D5-6D91-4815-AF93-5F1E1B3B08BD}')
    CLSID = '{C53AE9D5-6D91-4815-AF93-5F1E1B3B08BD}'
    # coclass_clsid = IID('{25B047DB-4AAD-4FC2-A0BE-31DDA687FF32}')
    coclass_clsid = '{25B047DB-4AAD-4FC2-A0BE-31DDA687FF32}'

    # Result is of type IDeviceCommand
    # The method Item is actually a property, but must be used as a method to correctly pass the arguments
    def Item(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection by position'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((3, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, 'Item', '{7CF694C0-F589-451C-B56E-398B5855B05E}')
        return ret

    _prop_map_get_ = {
        "Count": (1, 2, (3, 0), (), "Count", None),
    }
    _prop_map_put_ = {
    }
    # Default method for this class is 'Item'
    def __call__(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection by position'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((3, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, '__call__', '{7CF694C0-F589-451C-B56E-398B5855B05E}')
        return ret

    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,2,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, '{7CF694C0-F589-451C-B56E-398B5855B05E}')
    #This class has Count() property - allow len(ob) to provide this
    def __len__(self):
        return self._ApplyTypes_(*(1, 2, (3, 0), (), "Count", None))
    #This class has a __len__ - this is needed so 'if object:' always returns TRUE.
    def __nonzero__(self):
        return True

class IDeviceEvent(DispatchBaseClass):
    # CLSID = IID('{80D0880A-BB10-4722-82D1-07DC8DA157E2}')
    CLSID = '{80D0880A-BB10-4722-82D1-07DC8DA157E2}'
    # coclass_clsid = IID('{617CF892-783C-43D3-B04B-F0F1DE3B326D}')
    coclass_clsid = '{617CF892-783C-43D3-B04B-F0F1DE3B326D}'

    _prop_map_get_ = {
        "Description": (4, 2, (8, 0), (), "Description", None),
        "EventID": (1, 2, (8, 0), (), "EventID", None),
        "Name": (3, 2, (8, 0), (), "Name", None),
        "Type": (2, 2, (3, 0), (), "Type", None),
    }
    _prop_map_put_ = {
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IDeviceEvents(DispatchBaseClass):
    # CLSID = IID('{03985C95-581B-44D1-9403-8488B347538B}')
    CLSID = '{03985C95-581B-44D1-9403-8488B347538B}'
    # coclass_clsid = IID('{3563A59A-BBCD-4C86-94A0-92136C80A8B4}')
    coclass_clsid = '{3563A59A-BBCD-4C86-94A0-92136C80A8B4}'

    # Result is of type IDeviceEvent
    # The method Item is actually a property, but must be used as a method to correctly pass the arguments
    def Item(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection by position'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((3, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, 'Item', '{80D0880A-BB10-4722-82D1-07DC8DA157E2}')
        return ret

    _prop_map_get_ = {
        "Count": (1, 2, (3, 0), (), "Count", None),
    }
    _prop_map_put_ = {
    }
    # Default method for this class is 'Item'
    def __call__(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection by position'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((3, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, '__call__', '{80D0880A-BB10-4722-82D1-07DC8DA157E2}')
        return ret

    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,2,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, '{80D0880A-BB10-4722-82D1-07DC8DA157E2}')
    #This class has Count() property - allow len(ob) to provide this
    def __len__(self):
        return self._ApplyTypes_(*(1, 2, (3, 0), (), "Count", None))
    #This class has a __len__ - this is needed so 'if object:' always returns TRUE.
    def __nonzero__(self):
        return True

class IDeviceInfo(DispatchBaseClass):
    # CLSID = IID('{2A99020A-E325-4454-95E0-136726ED4818}')
    CLSID = '{2A99020A-E325-4454-95E0-136726ED4818}'
    # coclass_clsid = IID('{F09CFB7A-E561-4625-9BB5-208BCA0DE09F}')
    coclass_clsid = '{F09CFB7A-E561-4625-9BB5-208BCA0DE09F}'

    # Result is of type IDevice
    def Connect(self):
        'Establish a connection with this device and return a Device object'
        ret = self._oleobj_.InvokeTypes(4, LCID, 1, (9, 0), (),)
        if ret is not None:
            ret = Dispatch(ret, 'Connect', '{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}')
        return ret

    _prop_map_get_ = {
        "DeviceID": (1, 2, (8, 0), (), "DeviceID", None),
        # Method 'Properties' returns object of type 'IProperties'
        "Properties": (3, 2, (9, 0), (), "Properties", '{40571E58-A308-470A-80AA-FA10F88793A0}'),
        "Type": (2, 2, (3, 0), (), "Type", None),
    }
    _prop_map_put_ = {
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IDeviceInfos(DispatchBaseClass):
    # CLSID = IID('{FE076B64-8406-4E92-9CAC-9093F378E05F}')
    CLSID = '{FE076B64-8406-4E92-9CAC-9093F378E05F}'
    # coclass_clsid = IID('{2DFEE16B-E4AC-4A19-B660-AE71A745D34F}')
    coclass_clsid = '{2DFEE16B-E4AC-4A19-B660-AE71A745D34F}'

    # Result is of type IDeviceInfo
    # The method Item is actually a property, but must be used as a method to correctly pass the arguments
    def Item(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection either by position or Device ID'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((16396, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, 'Item', '{2A99020A-E325-4454-95E0-136726ED4818}')
        return ret

    _prop_map_get_ = {
        "Count": (1, 2, (3, 0), (), "Count", None),
    }
    _prop_map_put_ = {
    }
    # Default method for this class is 'Item'
    def __call__(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection either by position or Device ID'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((16396, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, '__call__', '{2A99020A-E325-4454-95E0-136726ED4818}')
        return ret

    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,2,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, '{2A99020A-E325-4454-95E0-136726ED4818}')
    #This class has Count() property - allow len(ob) to provide this
    def __len__(self):
        return self._ApplyTypes_(*(1, 2, (3, 0), (), "Count", None))
    #This class has a __len__ - this is needed so 'if object:' always returns TRUE.
    def __nonzero__(self):
        return True

class IDeviceManager(DispatchBaseClass):
    # CLSID = IID('{73856D9A-2720-487A-A584-21D5774E9D0F}')
    CLSID = '{73856D9A-2720-487A-A584-21D5774E9D0F}'
    # coclass_clsid = IID('{E1C5D730-7E97-4D8A-9E42-BBAE87C2059F}')
    coclass_clsid = '{E1C5D730-7E97-4D8A-9E42-BBAE87C2059F}'

    def RegisterEvent(self, EventID=defaultNamedNotOptArg, DeviceID='*'):
        'Registers the specified EventID for the specified DeviceID. If DeviceID is "*" then OnEvent will be called whenever the event specified occurs for any device. Otherwise, OnEvent will only be called if the event specified occurs on the device specified.'
        return self._ApplyTypes_(2, 1, (24, 32), ((8, 1), (8, 49)), 'RegisterEvent', None,EventID
            , DeviceID)

    def RegisterPersistentEvent(self, Command=defaultNamedNotOptArg, Name=defaultNamedNotOptArg, Description=defaultNamedNotOptArg, Icon=defaultNamedNotOptArg
            , EventID=defaultNamedNotOptArg, DeviceID='*'):
        'Registers the specified Command to launch when the specified EventID for the specified DeviceID occurs. Command can be either a ClassID or the full path name and the appropriate command-line arguments needed to invoke the application.'
        return self._ApplyTypes_(4, 1, (24, 32), ((8, 1), (8, 1), (8, 1), (8, 1), (8, 1), (8, 49)), 'RegisterPersistentEvent', None,Command
            , Name, Description, Icon, EventID, DeviceID
            )

    def UnregisterEvent(self, EventID=defaultNamedNotOptArg, DeviceID='*'):
        'Unregisters the specified EventID for the specified DeviceID. UnregisterEvent should only be called for EventID and DeviceID for which you called RegisterEvent.'
        return self._ApplyTypes_(3, 1, (24, 32), ((8, 1), (8, 49)), 'UnregisterEvent', None,EventID
            , DeviceID)

    def UnregisterPersistentEvent(self, Command=defaultNamedNotOptArg, Name=defaultNamedNotOptArg, Description=defaultNamedNotOptArg, Icon=defaultNamedNotOptArg
            , EventID=defaultNamedNotOptArg, DeviceID='*'):
        'Unregisters the specified Command for the specified EventID for the specified DeviceID. UnregisterPersistentEvent should only be called for the Command, Name, Description, Icon, EventID and DeviceID for which you called RegisterPersistentEvent.'
        return self._ApplyTypes_(5, 1, (24, 32), ((8, 1), (8, 1), (8, 1), (8, 1), (8, 1), (8, 49)), 'UnregisterPersistentEvent', None,Command
            , Name, Description, Icon, EventID, DeviceID
            )

    _prop_map_get_ = {
        # Method 'DeviceInfos' returns object of type 'IDeviceInfos'
        "DeviceInfos": (1, 2, (9, 0), (), "DeviceInfos", '{FE076B64-8406-4E92-9CAC-9093F378E05F}'),
    }
    _prop_map_put_ = {
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IFilter(DispatchBaseClass):
    # CLSID = IID('{851E9802-B338-4AB3-BB6B-6AA57CC699D0}')
    CLSID = '{851E9802-B338-4AB3-BB6B-6AA57CC699D0}'
    # coclass_clsid = IID('{52AD8A74-F064-4F4C-8544-FF494D349F7B}')
    coclass_clsid = '{52AD8A74-F064-4F4C-8544-FF494D349F7B}'

    _prop_map_get_ = {
        "Description": (2, 2, (8, 0), (), "Description", None),
        "FilterID": (3, 2, (8, 0), (), "FilterID", None),
        "Name": (1, 2, (8, 0), (), "Name", None),
        # Method 'Properties' returns object of type 'IProperties'
        "Properties": (4, 2, (9, 0), (), "Properties", '{40571E58-A308-470A-80AA-FA10F88793A0}'),
    }
    _prop_map_put_ = {
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IFilterInfo(DispatchBaseClass):
    # CLSID = IID('{EFD1219F-8229-4B30-809D-8F6D83341569}')
    CLSID = '{EFD1219F-8229-4B30-809D-8F6D83341569}'
    # coclass_clsid = IID('{318D6B52-9B1C-4E3B-8D90-1F0E857FA9B0}')
    coclass_clsid = '{318D6B52-9B1C-4E3B-8D90-1F0E857FA9B0}'

    _prop_map_get_ = {
        "Description": (2, 2, (8, 0), (), "Description", None),
        "FilterID": (3, 2, (8, 0), (), "FilterID", None),
        "Name": (1, 2, (8, 0), (), "Name", None),
    }
    _prop_map_put_ = {
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IFilterInfos(DispatchBaseClass):
    # CLSID = IID('{AF49723A-499C-411C-B19A-1B8244D67E44}')
    CLSID = '{AF49723A-499C-411C-B19A-1B8244D67E44}'
    # coclass_clsid = IID('{56FA88D3-F3DA-4DE3-94E8-811040C3CCD4}')
    coclass_clsid = '{56FA88D3-F3DA-4DE3-94E8-811040C3CCD4}'

    # Result is of type IFilterInfo
    # The method Item is actually a property, but must be used as a method to correctly pass the arguments
    def Item(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection either by position or name'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((16396, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, 'Item', '{EFD1219F-8229-4B30-809D-8F6D83341569}')
        return ret

    _prop_map_get_ = {
        "Count": (1, 2, (3, 0), (), "Count", None),
    }
    _prop_map_put_ = {
    }
    # Default method for this class is 'Item'
    def __call__(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection either by position or name'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((16396, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, '__call__', '{EFD1219F-8229-4B30-809D-8F6D83341569}')
        return ret

    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,2,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, '{EFD1219F-8229-4B30-809D-8F6D83341569}')
    #This class has Count() property - allow len(ob) to provide this
    def __len__(self):
        return self._ApplyTypes_(*(1, 2, (3, 0), (), "Count", None))
    #This class has a __len__ - this is needed so 'if object:' always returns TRUE.
    def __nonzero__(self):
        return True

class IFilters(DispatchBaseClass):
    # CLSID = IID('{C82FFED4-0A8D-4F85-B90A-AC8E720D39C1}')
    CLSID = '{C82FFED4-0A8D-4F85-B90A-AC8E720D39C1}'
    # coclass_clsid = IID('{31CDD60C-C04C-424D-95FC-36A52646D71C}')
    coclass_clsid = '{31CDD60C-C04C-424D-95FC-36A52646D71C}'

    def Add(self, FilterID=defaultNamedNotOptArg, Index=0):
        'Appends/Inserts a new Filter of the specified FilterID into a Filter collection'
        return self._oleobj_.InvokeTypes(2, LCID, 1, (24, 0), ((8, 1), (3, 49)),FilterID
            , Index)

    # Result is of type IFilter
    # The method Item is actually a property, but must be used as a method to correctly pass the arguments
    def Item(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection by position or FilterID'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((3, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, 'Item', '{851E9802-B338-4AB3-BB6B-6AA57CC699D0}')
        return ret

    def Remove(self, Index=defaultNamedNotOptArg):
        'Removes the designated filter'
        return self._oleobj_.InvokeTypes(3, LCID, 1, (24, 0), ((3, 1),),Index
            )

    _prop_map_get_ = {
        "Count": (1, 2, (3, 0), (), "Count", None),
    }
    _prop_map_put_ = {
    }
    # Default method for this class is 'Item'
    def __call__(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection by position or FilterID'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((3, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, '__call__', '{851E9802-B338-4AB3-BB6B-6AA57CC699D0}')
        return ret

    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,2,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, '{851E9802-B338-4AB3-BB6B-6AA57CC699D0}')
    #This class has Count() property - allow len(ob) to provide this
    def __len__(self):
        return self._ApplyTypes_(*(1, 2, (3, 0), (), "Count", None))
    #This class has a __len__ - this is needed so 'if object:' always returns TRUE.
    def __nonzero__(self):
        return True

class IFormats(DispatchBaseClass):
    # CLSID = IID('{882A274F-DF2F-4F6D-9F5A-AF4FD484530D}')
    CLSID = '{882A274F-DF2F-4F6D-9F5A-AF4FD484530D}'
    # coclass_clsid = IID('{6F62E261-0FE6-476B-A244-50CF7440DDEB}')
    coclass_clsid = '{6F62E261-0FE6-476B-A244-50CF7440DDEB}'

    # The method Item is actually a property, but must be used as a method to correctly pass the arguments
    def Item(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection by position'
        # Result is a Unicode object
        return self._oleobj_.InvokeTypes(0, LCID, 2, (8, 0), ((3, 1),),Index
            )

    _prop_map_get_ = {
        "Count": (1, 2, (3, 0), (), "Count", None),
    }
    _prop_map_put_ = {
    }
    # Default method for this class is 'Item'
    def __call__(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection by position'
        # Result is a Unicode object
        return self._oleobj_.InvokeTypes(0, LCID, 2, (8, 0), ((3, 1),),Index
            )

    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,2,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)
    #This class has Count() property - allow len(ob) to provide this
    def __len__(self):
        return self._ApplyTypes_(*(1, 2, (3, 0), (), "Count", None))
    #This class has a __len__ - this is needed so 'if object:' always returns TRUE.
    def __nonzero__(self):
        return True

class IImageFile(DispatchBaseClass):
    # CLSID = IID('{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}')
    CLSID = '{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}'
    # coclass_clsid = IID('{A2E6DDA0-06EF-4DF3-B7BD-5AA224BB06E8}')
    coclass_clsid = '{A2E6DDA0-06EF-4DF3-B7BD-5AA224BB06E8}'

    def LoadFile(self, Filename=defaultNamedNotOptArg):
        'Loads the ImageFile object with the specified File'
        return self._oleobj_.InvokeTypes(17, LCID, 1, (24, 0), ((8, 1),),Filename
            )

    def SaveFile(self, Filename=defaultNamedNotOptArg):
        'Save the ImageFile object to the specified File'
        return self._oleobj_.InvokeTypes(18, LCID, 1, (24, 0), ((8, 1),),Filename
            )

    _prop_map_get_ = {
        # Method 'ARGBData' returns object of type 'IVector'
        "ARGBData": (4, 2, (9, 0), (), "ARGBData", '{696F2367-6619-49BD-BA96-904DC2609990}'),
        "ActiveFrame": (15, 2, (3, 0), (), "ActiveFrame", None),
        # Method 'FileData' returns object of type 'IVector'
        "FileData": (3, 2, (9, 0), (), "FileData", '{696F2367-6619-49BD-BA96-904DC2609990}'),
        "FileExtension": (2, 2, (8, 0), (), "FileExtension", None),
        "FormatID": (1, 2, (8, 0), (), "FormatID", None),
        "FrameCount": (14, 2, (3, 0), (), "FrameCount", None),
        "Height": (5, 2, (3, 0), (), "Height", None),
        "HorizontalResolution": (7, 2, (5, 0), (), "HorizontalResolution", None),
        "IsAlphaPixelFormat": (11, 2, (11, 0), (), "IsAlphaPixelFormat", None),
        "IsAnimated": (13, 2, (11, 0), (), "IsAnimated", None),
        "IsExtendedPixelFormat": (12, 2, (11, 0), (), "IsExtendedPixelFormat", None),
        "IsIndexedPixelFormat": (10, 2, (11, 0), (), "IsIndexedPixelFormat", None),
        "PixelDepth": (9, 2, (3, 0), (), "PixelDepth", None),
        # Method 'Properties' returns object of type 'IProperties'
        "Properties": (16, 2, (9, 0), (), "Properties", '{40571E58-A308-470A-80AA-FA10F88793A0}'),
        "VerticalResolution": (8, 2, (5, 0), (), "VerticalResolution", None),
        "Width": (6, 2, (3, 0), (), "Width", None),
    }
    _prop_map_put_ = {
        "ActiveFrame": ((15, LCID, 4, 0),()),
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IImageProcess(DispatchBaseClass):
    # CLSID = IID('{41506929-7855-4392-9E6F-98D88513E55D}')
    CLSID = '{41506929-7855-4392-9E6F-98D88513E55D}'
    # coclass_clsid = IID('{BD0D38E4-74C8-4904-9B5A-269F8E9994E9}')
    coclass_clsid = '{BD0D38E4-74C8-4904-9B5A-269F8E9994E9}'

    # Result is of type IImageFile
    def Apply(self, Source=defaultNamedNotOptArg):
        'Takes the specified ImageFile and returns the new ImageFile with all the filters applied on success'
        ret = self._oleobj_.InvokeTypes(4, LCID, 1, (9, 0), ((9, 1),),Source
            )
        if ret is not None:
            ret = Dispatch(ret, 'Apply', '{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}')
        return ret

    _prop_map_get_ = {
        # Method 'FilterInfos' returns object of type 'IFilterInfos'
        "FilterInfos": (1, 2, (9, 0), (), "FilterInfos", '{AF49723A-499C-411C-B19A-1B8244D67E44}'),
        # Method 'Filters' returns object of type 'IFilters'
        "Filters": (2, 2, (9, 0), (), "Filters", '{C82FFED4-0A8D-4F85-B90A-AC8E720D39C1}'),
    }
    _prop_map_put_ = {
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IItem(DispatchBaseClass):
    # CLSID = IID('{68F2BF12-A755-4E2B-9BCD-37A22587D078}')
    CLSID = '{68F2BF12-A755-4E2B-9BCD-37A22587D078}'
    # coclass_clsid = IID('{36F479F3-C258-426E-B5FA-2793DCFDA881}')
    coclass_clsid = '{36F479F3-C258-426E-B5FA-2793DCFDA881}'

    # Result is of type IItem
    def ExecuteCommand(self, CommandID=defaultNamedNotOptArg):
        'Issues the command specified by CommandID. CommandIDs are device dependent. Valid CommandIDs for this Item are contained in the Commands collection.'
        ret = self._oleobj_.InvokeTypes(8, LCID, 1, (9, 0), ((8, 1),),CommandID
            )
        if ret is not None:
            ret = Dispatch(ret, 'ExecuteCommand', '{68F2BF12-A755-4E2B-9BCD-37A22587D078}')
        return ret

    def Transfer(self, FormatID='{00000000-0000-0000-0000-000000000000}'):
        'Returns an ImageFile object, in this version, in the format specified in FormatID if supported, otherwise using the preferred format for this imaging device. Future versions may return a collection of ImageFile objects.'
        return self._ApplyTypes_(7, 1, (12, 32), ((8, 49),), 'Transfer', None,FormatID
            )

    _prop_map_get_ = {
        # Method 'Commands' returns object of type 'IDeviceCommands'
        "Commands": (5, 2, (9, 0), (), "Commands", '{C53AE9D5-6D91-4815-AF93-5F1E1B3B08BD}'),
        # Method 'Formats' returns object of type 'IFormats'
        "Formats": (4, 2, (9, 0), (), "Formats", '{882A274F-DF2F-4F6D-9F5A-AF4FD484530D}'),
        "ItemID": (1, 2, (8, 0), (), "ItemID", None),
        # Method 'Items' returns object of type 'IItems'
        "Items": (3, 2, (9, 0), (), "Items", '{46102071-60B4-4E58-8620-397D17B0BB5B}'),
        # Method 'Properties' returns object of type 'IProperties'
        "Properties": (2, 2, (9, 0), (), "Properties", '{40571E58-A308-470A-80AA-FA10F88793A0}'),
        "WiaItem": (6, 2, (13, 0), (), "WiaItem", None),
    }
    _prop_map_put_ = {
    }
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IItems(DispatchBaseClass):
    # CLSID = IID('{46102071-60B4-4E58-8620-397D17B0BB5B}')
    CLSID = '{46102071-60B4-4E58-8620-397D17B0BB5B}'
    # coclass_clsid = IID('{B243B765-CA9C-4F30-A457-C8B2B57A585E}')
    coclass_clsid = '{B243B765-CA9C-4F30-A457-C8B2B57A585E}'

    def Add(self, Name=defaultNamedNotOptArg, Flags=defaultNamedNotOptArg):
        'Adds a new Item with the specified Name and Flags. The Flags value is created by using the OR operation with members of the WiaItemFlags enumeration.'
        return self._oleobj_.InvokeTypes(2, LCID, 1, (24, 0), ((8, 1), (3, 1)),Name
            , Flags)

    # Result is of type IItem
    # The method Item is actually a property, but must be used as a method to correctly pass the arguments
    def Item(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection by position'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((3, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, 'Item', '{68F2BF12-A755-4E2B-9BCD-37A22587D078}')
        return ret

    def Remove(self, Index=defaultNamedNotOptArg):
        'Removes the designated Item'
        return self._oleobj_.InvokeTypes(3, LCID, 1, (24, 0), ((3, 1),),Index
            )

    _prop_map_get_ = {
        "Count": (1, 2, (3, 0), (), "Count", None),
    }
    _prop_map_put_ = {
    }
    # Default method for this class is 'Item'
    def __call__(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection by position'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((3, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, '__call__', '{68F2BF12-A755-4E2B-9BCD-37A22587D078}')
        return ret

    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,2,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, '{68F2BF12-A755-4E2B-9BCD-37A22587D078}')
    #This class has Count() property - allow len(ob) to provide this
    def __len__(self):
        return self._ApplyTypes_(*(1, 2, (3, 0), (), "Count", None))
    #This class has a __len__ - this is needed so 'if object:' always returns TRUE.
    def __nonzero__(self):
        return True

class IProperties(DispatchBaseClass):
    # CLSID = IID('{40571E58-A308-470A-80AA-FA10F88793A0}')
    CLSID = '{40571E58-A308-470A-80AA-FA10F88793A0}'
    # coclass_clsid = IID('{96F887FC-08B1-4F97-A69C-75280C6A9CF8}')
    coclass_clsid = '{96F887FC-08B1-4F97-A69C-75280C6A9CF8}'

    def Exists(self, Index=defaultNamedNotOptArg):
        'Indicates whether the specified Property exists in the collection'
        return self._oleobj_.InvokeTypes(2, LCID, 1, (11, 0), ((16396, 1),),Index
            )

    # Result is of type IProperty
    # The method Item is actually a property, but must be used as a method to correctly pass the arguments
    def Item(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection either by position or name.'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((16396, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, 'Item', '{706038DC-9F4B-4E45-88E2-5EB7D665B815}')
        return ret

    _prop_map_get_ = {
        "Count": (1, 2, (3, 0), (), "Count", None),
    }
    _prop_map_put_ = {
    }
    # Default method for this class is 'Item'
    def __call__(self, Index=defaultNamedNotOptArg):
        'Returns the specified item in the collection either by position or name.'
        ret = self._oleobj_.InvokeTypes(0, LCID, 2, (9, 0), ((16396, 1),),Index
            )
        if ret is not None:
            ret = Dispatch(ret, '__call__', '{706038DC-9F4B-4E45-88E2-5EB7D665B815}')
        return ret

    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,2,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, '{706038DC-9F4B-4E45-88E2-5EB7D665B815}')
    #This class has Count() property - allow len(ob) to provide this
    def __len__(self):
        return self._ApplyTypes_(*(1, 2, (3, 0), (), "Count", None))
    #This class has a __len__ - this is needed so 'if object:' always returns TRUE.
    def __nonzero__(self):
        return True

class IProperty(DispatchBaseClass):
    # CLSID = IID('{706038DC-9F4B-4E45-88E2-5EB7D665B815}')
    CLSID = '{706038DC-9F4B-4E45-88E2-5EB7D665B815}'
    # coclass_clsid = IID('{2014DE3F-3723-4178-8643-3317A32D4A2B}')
    coclass_clsid = '{2014DE3F-3723-4178-8643-3317A32D4A2B}'

    def SetValue(self, arg0=defaultUnnamedArg):
        'Returns/Sets the Property Value'
        return self._oleobj_.InvokeTypes(0, LCID, 8, (24, 0), ((16396, 1),),arg0
            )

    _prop_map_get_ = {
        "IsReadOnly": (4, 2, (11, 0), (), "IsReadOnly", None),
        "IsVector": (5, 2, (11, 0), (), "IsVector", None),
        "Name": (1, 2, (8, 0), (), "Name", None),
        "PropertyID": (2, 2, (3, 0), (), "PropertyID", None),
        "SubType": (6, 2, (3, 0), (), "SubType", None),
        "SubTypeDefault": (7, 2, (12, 0), (), "SubTypeDefault", None),
        "SubTypeMax": (10, 2, (3, 0), (), "SubTypeMax", None),
        "SubTypeMin": (9, 2, (3, 0), (), "SubTypeMin", None),
        "SubTypeStep": (11, 2, (3, 0), (), "SubTypeStep", None),
        # Method 'SubTypeValues' returns object of type 'IVector'
        "SubTypeValues": (8, 2, (9, 0), (), "SubTypeValues", '{696F2367-6619-49BD-BA96-904DC2609990}'),
        "Type": (3, 2, (3, 0), (), "Type", None),
        "Value": (0, 2, (12, 0), (), "Value", None),
    }
    _prop_map_put_ = {
        "Value": ((0, LCID, 4, 0),()),
    }
    # Default method for this class is 'Value'
    def __call__(self, arg0=defaultUnnamedArg):
        'Returns/Sets the Property Value'
        return self._oleobj_.InvokeTypes(0, LCID, 8, (24, 0), ((16396, 1),),arg0
            )

    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IRational(DispatchBaseClass):
    # CLSID = IID('{3BF1B24A-01A5-4AA3-91F9-25A60B50E49B}')
    CLSID = '{3BF1B24A-01A5-4AA3-91F9-25A60B50E49B}'
    # coclass_clsid = IID('{0C5672F9-3EDC-4B24-95B5-A6C54C0B79AD}')
    coclass_clsid = '{0C5672F9-3EDC-4B24-95B5-A6C54C0B79AD}'

    _prop_map_get_ = {
        "Denominator": (2, 2, (3, 0), (), "Denominator", None),
        "Numerator": (1, 2, (3, 0), (), "Numerator", None),
        "Value": (0, 2, (5, 0), (), "Value", None),
    }
    _prop_map_put_ = {
        "Denominator": ((2, LCID, 4, 0),()),
        "Numerator": ((1, LCID, 4, 0),()),
    }
    # Default property for this class is 'Value'
    def __call__(self):
        return self._ApplyTypes_(*(0, 2, (5, 0), (), "Value", None))
    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)

class IVector(DispatchBaseClass):
    # CLSID = IID('{696F2367-6619-49BD-BA96-904DC2609990}')
    CLSID = '{696F2367-6619-49BD-BA96-904DC2609990}'
    # coclass_clsid = IID('{4DD1D1C3-B36A-4EB4-AAEF-815891A58A30}')
    coclass_clsid = '{4DD1D1C3-B36A-4EB4-AAEF-815891A58A30}'

    def Add(self, Value=defaultNamedNotOptArg, Index=0):
        'If Index is not zero, Inserts a new element into the Vector collection before the specified Index. If Index is zero, Appends a new element to the Vector collection.'
        return self._oleobj_.InvokeTypes(7, LCID, 1, (24, 0), ((16396, 1), (3, 49)),Value
            , Index)

    def Clear(self):
        'Removes all elements.'
        return self._oleobj_.InvokeTypes(9, LCID, 1, (24, 0), (),)

    # Result is of type IImageFile
    # The method GetImageFile is actually a property, but must be used as a method to correctly pass the arguments
    def GetImageFile(self, Width=0, Height=0):
        'Used to get the Thumbnail property of an ImageFile which is an image file, The thumbnail property of an Item which is RGB data, or creating an ImageFile from raw ARGB data. Returns an ImageFile object on success. See the Picture method for more details.'
        ret = self._oleobj_.InvokeTypes(3, LCID, 2, (9, 0), ((3, 49), (3, 49)),Width
            , Height)
        if ret is not None:
            ret = Dispatch(ret, 'GetImageFile', '{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}')
        return ret

    # The method GetPicture is actually a property, but must be used as a method to correctly pass the arguments
    def GetPicture(self, Width=0, Height=0):
        'If the Vector of Bytes contains an image file, then Width and Height are ignored. Otherwise a Vector of Bytes must be RGB data and a Vector of Longs must be ARGB data. Returns a Picture object on success. See the ImageFile method for more details.'
        return self._ApplyTypes_(2, 2, (12, 0), ((3, 49), (3, 49)), 'GetPicture', None,Width
            , Height)

    # The method GetString is actually a property, but must be used as a method to correctly pass the arguments
    def GetString(self, Unicode=True):
        'Returns a Vector of Bytes as a String'
        # Result is a Unicode object
        return self._oleobj_.InvokeTypes(5, LCID, 2, (8, 0), ((11, 49),),Unicode
            )

    # The method Item is actually a property, but must be used as a method to correctly pass the arguments
    def Item(self, Index=defaultNamedNotOptArg):
        'Returns/Sets the specified item in the vector by position'
        return self._ApplyTypes_(0, 2, (12, 0), ((3, 1),), 'Item', None,Index
            )

    def Remove(self, Index=defaultNamedNotOptArg):
        'Removes the designated element and returns it if successful'
        return self._ApplyTypes_(8, 1, (12, 0), ((3, 1),), 'Remove', None,Index
            )

    def SetFromString(self, Value=defaultNamedNotOptArg, Resizable=True, Unicode=True):
        'Stores the string Value into the Vector of Bytes including the NULL terminator. Value may be truncated unless Resizable is True. The string will be stored as an ANSI string unless Unicode is True, in which case it will be stored as a Unicode string.'
        return self._oleobj_.InvokeTypes(10, LCID, 1, (24, 0), ((8, 1), (11, 49), (11, 49)),Value
            , Resizable, Unicode)

    # The method SetItem is actually a property, but must be used as a method to correctly pass the arguments
    def SetItem(self, Index=defaultNamedNotOptArg, arg1=defaultUnnamedArg):
        'Returns/Sets the specified item in the vector by position'
        return self._oleobj_.InvokeTypes(0, LCID, 4, (24, 0), ((3, 1), (16396, 1)),Index
            , arg1)

    _prop_map_get_ = {
        "BinaryData": (4, 2, (12, 0), (), "BinaryData", None),
        "Count": (1, 2, (3, 0), (), "Count", None),
        "Date": (6, 2, (7, 0), (), "Date", None),
        # Method 'ImageFile' returns object of type 'IImageFile'
        "ImageFile": (3, 2, (9, 0), ((3, 49), (3, 49)), "ImageFile", '{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}'),
        "Picture": (2, 2, (12, 0), ((3, 49), (3, 49)), "Picture", None),
        "String": (5, 2, (8, 0), ((11, 49),), "String", None),
    }
    _prop_map_put_ = {
        "BinaryData": ((4, LCID, 4, 0),()),
        "Date": ((6, LCID, 4, 0),()),
    }
    # Default method for this class is 'Item'
    def __call__(self, Index=defaultNamedNotOptArg):
        'Returns/Sets the specified item in the vector by position'
        return self._ApplyTypes_(0, 2, (12, 0), ((3, 1),), '__call__', None,Index
            )

    def __str__(self, *args):
        return str(self.__call__(*args))
    def __int__(self, *args):
        return int(self.__call__(*args))
    def __iter__(self):
        "Return a Python iterator for this object"
        try:
            ob = self._oleobj_.InvokeTypes(-4,LCID,2,(13, 10),())
        except pythoncom.error:
            raise TypeError("This object does not support enumeration")
        return win32com.client.util.Iterator(ob, None)
    #This class has Count() property - allow len(ob) to provide this
    def __len__(self):
        return self._ApplyTypes_(*(1, 2, (3, 0), (), "Count", None))
    #This class has a __len__ - this is needed so 'if object:' always returns TRUE.
    def __nonzero__(self):
        return True

class _IDeviceManagerEvents:
    # CLSID = CLSID_Sink = IID('{2E9A5206-2360-49DF-9D9B-1762B4BEAE77}')
    CLSID = CLSID_Sink = '{2E9A5206-2360-49DF-9D9B-1762B4BEAE77}'
    # coclass_clsid = IID('{E1C5D730-7E97-4D8A-9E42-BBAE87C2059F}')
    coclass_clsid = '{E1C5D730-7E97-4D8A-9E42-BBAE87C2059F}'
    _public_methods_ = [] # For COM Server support
    _dispid_to_func_ = {
                1 : "OnEvent",
        }

    def __init__(self, oobj = None):
        if oobj is None:
            self._olecp = None
        else:
            import win32com.server.util
            from win32com.server.policy import EventHandlerPolicy
            cpc=oobj._oleobj_.QueryInterface(pythoncom.IID_IConnectionPointContainer)
            cp=cpc.FindConnectionPoint(self.CLSID_Sink)
            cookie=cp.Advise(win32com.server.util.wrap(self, usePolicy=EventHandlerPolicy))
            self._olecp,self._olecp_cookie = cp,cookie
    def __del__(self):
        try:
            self.close()
        except pythoncom.com_error:
            pass
    def close(self):
        if self._olecp is not None:
            cp,cookie,self._olecp,self._olecp_cookie = self._olecp,self._olecp_cookie,None,None
            cp.Unadvise(cookie)
    def _query_interface_(self, iid):
        import win32com.server.util
        if iid==self.CLSID_Sink: return win32com.server.util.wrap(self)

    # Event Handlers
    # If you create handlers, they should have the following prototypes:
#	def OnEvent(self, EventID=defaultNamedNotOptArg, DeviceID=defaultNamedNotOptArg, ItemID=defaultNamedNotOptArg):
#		'Occurs for any event registered with RegisterEvent'


from win32com.client import CoClassBaseClass
# This CoClass is known by the name 'WIA.CommonDialog.1'
class CommonDialog(CoClassBaseClass): # A CoClass
    # The CommonDialog control is an invisible-at-runtime control that contains all the methods that display a User Interface. A CommonDialog control can be created using "WIA.CommonDialog" in a call to CreateObject or by dropping a CommonDialog on a form.
    # CLSID = IID('{850D1D11-70F3-4BE5-9A11-77AA6B2BB201}')
    CLSID = '{850D1D11-70F3-4BE5-9A11-77AA6B2BB201}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        ICommonDialog,
    ]
    default_interface = ICommonDialog

class Device(CoClassBaseClass): # A CoClass
    # The Device object represents an active connection to an imaging device.
    # CLSID = IID('{DBAA8843-B1C4-4EDC-B7E0-D6F61162BE58}')
    CLSID = '{DBAA8843-B1C4-4EDC-B7E0-D6F61162BE58}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IDevice,
    ]
    default_interface = IDevice

class DeviceCommand(CoClassBaseClass): # A CoClass
    # The DeviceCommand object describes a CommandID that can be used when calling ExecuteCommand on a Device or Item object.
    # CLSID = IID('{72226184-AFBB-4059-BF55-0F6C076E669D}')
    CLSID = '{72226184-AFBB-4059-BF55-0F6C076E669D}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IDeviceCommand,
    ]
    default_interface = IDeviceCommand

class DeviceCommands(CoClassBaseClass): # A CoClass
    # The DeviceCommands object is a collection of all the supported DeviceCommands for an imaging device. See the Commands property of a Device or Item object for more details on determining the collection of supported device commands.
    # CLSID = IID('{25B047DB-4AAD-4FC2-A0BE-31DDA687FF32}')
    CLSID = '{25B047DB-4AAD-4FC2-A0BE-31DDA687FF32}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IDeviceCommands,
    ]
    default_interface = IDeviceCommands

class DeviceEvent(CoClassBaseClass): # A CoClass
    # The DeviceEvent object describes an EventID that can be used when calling RegisterEvent or RegisterPersistentEvent on a DeviceManager object.
    # CLSID = IID('{617CF892-783C-43D3-B04B-F0F1DE3B326D}')
    CLSID = '{617CF892-783C-43D3-B04B-F0F1DE3B326D}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IDeviceEvent,
    ]
    default_interface = IDeviceEvent

class DeviceEvents(CoClassBaseClass): # A CoClass
    # The DeviceEvents object is a collection of all the supported DeviceEvent for an imaging device. See the Events property of a Device object for more details on determining the collection of supported device events.
    # CLSID = IID('{3563A59A-BBCD-4C86-94A0-92136C80A8B4}')
    CLSID = '{3563A59A-BBCD-4C86-94A0-92136C80A8B4}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IDeviceEvents,
    ]
    default_interface = IDeviceEvents

class DeviceInfo(CoClassBaseClass): # A CoClass
    # The DeviceInfo object is a container that describes the unchanging (static) properties of an imaging device that is currently connected to the computer.
    # CLSID = IID('{F09CFB7A-E561-4625-9BB5-208BCA0DE09F}')
    CLSID = '{F09CFB7A-E561-4625-9BB5-208BCA0DE09F}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IDeviceInfo,
    ]
    default_interface = IDeviceInfo

class DeviceInfos(CoClassBaseClass): # A CoClass
    # The DeviceInfos object is a collection of all the imaging devices currently connected to the computer. See the DeviceInfos property on the DeviceManager object for detail on accessing the DeviceInfos object.
    # CLSID = IID('{2DFEE16B-E4AC-4A19-B660-AE71A745D34F}')
    CLSID = '{2DFEE16B-E4AC-4A19-B660-AE71A745D34F}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IDeviceInfos,
    ]
    default_interface = IDeviceInfos

# This CoClass is known by the name 'WIA.DeviceManager.1'
class DeviceManager(CoClassBaseClass): # A CoClass
    # The DeviceManager control is an invisible-at-runtime control that manages the imaging devices connected to the computer. A DeviceManager control can be created using "WIA.DeviceManager" in a call to CreateObject or by dropping a DeviceManager on a form.
    # CLSID = IID('{E1C5D730-7E97-4D8A-9E42-BBAE87C2059F}')
    CLSID = '{E1C5D730-7E97-4D8A-9E42-BBAE87C2059F}'
    coclass_sources = [
        _IDeviceManagerEvents,
    ]
    default_source = _IDeviceManagerEvents
    coclass_interfaces = [
        IDeviceManager,
    ]
    default_interface = IDeviceManager

class Filter(CoClassBaseClass): # A CoClass
    # The Filter object represents a unit of modification on an ImageFile. To use a Filter, add it to the Filters collection, then set the filter's properties and finally use the Apply method of the ImageProcess object to filter an ImageFile.
    # CLSID = IID('{52AD8A74-F064-4F4C-8544-FF494D349F7B}')
    CLSID = '{52AD8A74-F064-4F4C-8544-FF494D349F7B}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IFilter,
    ]
    default_interface = IFilter

class FilterInfo(CoClassBaseClass): # A CoClass
    # The FilterInfo object is a container that describes a Filter object without requiring a Filter to be Added to the process chain. See the FilterInfos property on the ImageProcess object for details on accessing FilterInfo objects.
    # CLSID = IID('{318D6B52-9B1C-4E3B-8D90-1F0E857FA9B0}')
    CLSID = '{318D6B52-9B1C-4E3B-8D90-1F0E857FA9B0}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IFilterInfo,
    ]
    default_interface = IFilterInfo

class FilterInfos(CoClassBaseClass): # A CoClass
    # The FilterInfos object is a collection of all the available FilterInfo objects. See the FilterInfos property on the ImageProcess object for detail on accessing the FilterInfos object.
    # CLSID = IID('{56FA88D3-F3DA-4DE3-94E8-811040C3CCD4}')
    CLSID = '{56FA88D3-F3DA-4DE3-94E8-811040C3CCD4}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IFilterInfos,
    ]
    default_interface = IFilterInfos

class Filters(CoClassBaseClass): # A CoClass
    # The Filters object is a collection of the Filters that will be applied to an ImageFile when you call the Apply method on the ImageProcess object.
    # CLSID = IID('{31CDD60C-C04C-424D-95FC-36A52646D71C}')
    CLSID = '{31CDD60C-C04C-424D-95FC-36A52646D71C}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IFilters,
    ]
    default_interface = IFilters

class Formats(CoClassBaseClass): # A CoClass
    # The Formats object is a collection of supported FormatIDs that you can use when calling Transfer on an Item object or ShowTransfer on a CommonDialog object for this Item.
    # CLSID = IID('{6F62E261-0FE6-476B-A244-50CF7440DDEB}')
    CLSID = '{6F62E261-0FE6-476B-A244-50CF7440DDEB}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IFormats,
    ]
    default_interface = IFormats

# This CoClass is known by the name 'WIA.ImageFile.1'
class ImageFile(CoClassBaseClass): # A CoClass
    # The ImageFile object is a container for images transferred to your computer when you call Transfer or ShowTransfer. It also supports image files through LoadFile. An ImageFile object can be created using "WIA.ImageFile" in a call to CreateObject.
    # CLSID = IID('{A2E6DDA0-06EF-4DF3-B7BD-5AA224BB06E8}')
    CLSID = '{A2E6DDA0-06EF-4DF3-B7BD-5AA224BB06E8}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IImageFile,
    ]
    default_interface = IImageFile

# This CoClass is known by the name 'WIA.ImageProcess.1'
class ImageProcess(CoClassBaseClass): # A CoClass
    # The ImageProcess object manages the filter chain. An ImageProcess object can be created using "WIA.ImageProcess" in a call to CreateObject.
    # CLSID = IID('{BD0D38E4-74C8-4904-9B5A-269F8E9994E9}')
    CLSID = '{BD0D38E4-74C8-4904-9B5A-269F8E9994E9}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IImageProcess,
    ]
    default_interface = IImageProcess

class Item(CoClassBaseClass): # A CoClass
    # The Item object is a container for an item on an imaging device object. See the Items property on the Device or Item object for details on accessing Item objects.
    # CLSID = IID('{36F479F3-C258-426E-B5FA-2793DCFDA881}')
    CLSID = '{36F479F3-C258-426E-B5FA-2793DCFDA881}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IItem,
    ]
    default_interface = IItem

class Items(CoClassBaseClass): # A CoClass
    # The Items object contains a collection of Item objects. See the Items property on the Device or Item object for details on accessing the Items object.
    # CLSID = IID('{B243B765-CA9C-4F30-A457-C8B2B57A585E}')
    CLSID = '{B243B765-CA9C-4F30-A457-C8B2B57A585E}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IItems,
    ]
    default_interface = IItems

class Properties(CoClassBaseClass): # A CoClass
    # The Properties object is a collection of all the Property objects associated with a given Device, DeviceInfo, Filter, ImageFile or Item object. See the Properties property on any of these objects for detail on accessing the Properties object.
    # CLSID = IID('{96F887FC-08B1-4F97-A69C-75280C6A9CF8}')
    CLSID = '{96F887FC-08B1-4F97-A69C-75280C6A9CF8}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IProperties,
    ]
    default_interface = IProperties

class Property(CoClassBaseClass): # A CoClass
    # The Property object is a container for a property associated with a Device, DeviceInfo, Filter, ImageFile or Item object. See the Properties property on any of these objects for details on accessing Property objects.
    # CLSID = IID('{2014DE3F-3723-4178-8643-3317A32D4A2B}')
    CLSID = '{2014DE3F-3723-4178-8643-3317A32D4A2B}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IProperty,
    ]
    default_interface = IProperty

# This CoClass is known by the name 'WIA.Rational.1'
class Rational(CoClassBaseClass): # A CoClass
    # The Rational object is a container for the rational values found in Exif tags. It is a supported element type of the Vector object and may be created using "WIA.Rational" in a call to CreateObject.
    # CLSID = IID('{0C5672F9-3EDC-4B24-95B5-A6C54C0B79AD}')
    CLSID = '{0C5672F9-3EDC-4B24-95B5-A6C54C0B79AD}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IRational,
    ]
    default_interface = IRational

# This CoClass is known by the name 'WIA.Vector.1'
class Vector(CoClassBaseClass): # A CoClass
    # The Vector object is a collection of values of the same type. It is used throughout the library in many different ways. The Vector object may be created using "WIA.Vector" in a call to CreateObject.
    # CLSID = IID('{4DD1D1C3-B36A-4EB4-AAEF-815891A58A30}')
    CLSID = '{4DD1D1C3-B36A-4EB4-AAEF-815891A58A30}'
    coclass_sources = [
    ]
    coclass_interfaces = [
        IVector,
    ]
    default_interface = IVector

ICommonDialog_vtables_dispatch_ = 1
ICommonDialog_vtables_ = [
    (( 'ShowAcquisitionWizard' , 'Device' , 'pvResult' , ), 1, (1, (), [ (9, 1, None, "IID('{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}')") ,
             (16396, 10, None, None) , ], 1 , 1 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'ShowAcquireImage' , 'DeviceType' , 'Intent' , 'Bias' , 'FormatID' ,
             'AlwaysSelectDevice' , 'UseCommonUI' , 'CancelError' , 'ppResult' , ), 2, (2, (), [
             (3, 49, '0', None) , (3, 49, '0', None) , (3, 49, '131072', None) , (8, 49, "'{00000000-0000-0000-0000-000000000000}'", None) , (11, 49, 'False', None) ,
             (11, 49, 'True', None) , (11, 49, 'False', None) , (16393, 10, None, "IID('{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}')") , ], 1 , 1 , 4 , 0 , 32 , (3, 32, None, None) , 0 , )),
    (( 'ShowSelectDevice' , 'DeviceType' , 'AlwaysSelectDevice' , 'CancelError' , 'ppResult' ,
             ), 3, (3, (), [ (3, 49, '0', None) , (11, 49, 'False', None) , (11, 49, 'False', None) , (16393, 10, None, "IID('{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}')") , ], 1 , 1 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
    (( 'ShowSelectItems' , 'Device' , 'Intent' , 'Bias' , 'SingleSelect' ,
             'UseCommonUI' , 'CancelError' , 'ppResult' , ), 4, (4, (), [ (9, 1, None, "IID('{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}')") ,
             (3, 49, '0', None) , (3, 49, '131072', None) , (11, 49, 'True', None) , (11, 49, 'True', None) , (11, 49, 'False', None) ,
             (16393, 10, None, "IID('{46102071-60B4-4E58-8620-397D17B0BB5B}')") , ], 1 , 1 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
    (( 'ShowDeviceProperties' , 'Device' , 'CancelError' , ), 5, (5, (), [ (9, 1, None, "IID('{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}')") ,
             (11, 49, 'False', None) , ], 1 , 1 , 4 , 0 , 44 , (3, 0, None, None) , 0 , )),
    (( 'ShowItemProperties' , 'Item' , 'CancelError' , ), 6, (6, (), [ (9, 1, None, "IID('{68F2BF12-A755-4E2B-9BCD-37A22587D078}')") ,
             (11, 49, 'False', None) , ], 1 , 1 , 4 , 0 , 48 , (3, 0, None, None) , 0 , )),
    (( 'ShowTransfer' , 'Item' , 'FormatID' , 'CancelError' , 'pvResult' ,
             ), 7, (7, (), [ (9, 1, None, "IID('{68F2BF12-A755-4E2B-9BCD-37A22587D078}')") , (8, 49, "'{00000000-0000-0000-0000-000000000000}'", None) , (11, 49, 'False', None) , (16396, 10, None, None) , ], 1 , 1 , 4 , 0 , 52 , (3, 32, None, None) , 0 , )),
    (( 'ShowPhotoPrintingWizard' , 'Files' , ), 8, (8, (), [ (16396, 1, None, None) , ], 1 , 1 , 4 , 0 , 56 , (3, 0, None, None) , 0 , )),
]

IDevice_vtables_dispatch_ = 1
IDevice_vtables_ = [
    (( 'DeviceID' , 'pbstrResult' , ), 1, (1, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Type' , 'pResult' , ), 2, (2, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'Properties' , 'ppResult' , ), 3, (3, (), [ (16393, 10, None, "IID('{40571E58-A308-470A-80AA-FA10F88793A0}')") , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
    (( 'Items' , 'ppResult' , ), 4, (4, (), [ (16393, 10, None, "IID('{46102071-60B4-4E58-8620-397D17B0BB5B}')") , ], 1 , 2 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
    (( 'Commands' , 'ppResult' , ), 5, (5, (), [ (16393, 10, None, "IID('{C53AE9D5-6D91-4815-AF93-5F1E1B3B08BD}')") , ], 1 , 2 , 4 , 0 , 44 , (3, 0, None, None) , 0 , )),
    (( 'Events' , 'ppResult' , ), 6, (6, (), [ (16393, 10, None, "IID('{03985C95-581B-44D1-9403-8488B347538B}')") , ], 1 , 2 , 4 , 0 , 48 , (3, 0, None, None) , 0 , )),
    (( 'WiaItem' , 'ppResult' , ), 7, (7, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 52 , (3, 0, None, None) , 0 , )),
    (( 'GetItem' , 'ItemID' , 'ppResult' , ), 8, (8, (), [ (8, 1, None, None) ,
             (16393, 10, None, "IID('{68F2BF12-A755-4E2B-9BCD-37A22587D078}')") , ], 1 , 1 , 4 , 0 , 56 , (3, 0, None, None) , 0 , )),
    (( 'ExecuteCommand' , 'CommandID' , 'ppResult' , ), 9, (9, (), [ (8, 1, None, None) ,
             (16393, 10, None, "IID('{68F2BF12-A755-4E2B-9BCD-37A22587D078}')") , ], 1 , 1 , 4 , 0 , 60 , (3, 0, None, None) , 0 , )),
]

IDeviceCommand_vtables_dispatch_ = 1
IDeviceCommand_vtables_ = [
    (( 'CommandID' , 'pbstrResult' , ), 1, (1, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Name' , 'pbstrResult' , ), 2, (2, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'Description' , 'pbstrResult' , ), 3, (3, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
]

IDeviceCommands_vtables_dispatch_ = 1
IDeviceCommands_vtables_ = [
    (( 'Item' , 'Index' , 'ppResult' , ), 0, (0, (), [ (3, 1, None, None) ,
             (16393, 10, None, "IID('{7CF694C0-F589-451C-B56E-398B5855B05E}')") , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Count' , 'pResult' , ), 1, (1, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( '_NewEnum' , 'ppResult' , ), -4, (-4, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 1 , )),
]

IDeviceEvent_vtables_dispatch_ = 1
IDeviceEvent_vtables_ = [
    (( 'EventID' , 'pbstrResult' , ), 1, (1, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Type' , 'pResult' , ), 2, (2, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'Name' , 'pbstrResult' , ), 3, (3, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
    (( 'Description' , 'pbstrResult' , ), 4, (4, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
]

IDeviceEvents_vtables_dispatch_ = 1
IDeviceEvents_vtables_ = [
    (( 'Item' , 'Index' , 'ppResult' , ), 0, (0, (), [ (3, 1, None, None) ,
             (16393, 10, None, "IID('{80D0880A-BB10-4722-82D1-07DC8DA157E2}')") , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Count' , 'pResult' , ), 1, (1, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( '_NewEnum' , 'ppResult' , ), -4, (-4, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 1 , )),
]

IDeviceInfo_vtables_dispatch_ = 1
IDeviceInfo_vtables_ = [
    (( 'DeviceID' , 'pbstrResult' , ), 1, (1, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Type' , 'pResult' , ), 2, (2, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'Properties' , 'ppResult' , ), 3, (3, (), [ (16393, 10, None, "IID('{40571E58-A308-470A-80AA-FA10F88793A0}')") , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
    (( 'Connect' , 'ppResult' , ), 4, (4, (), [ (16393, 10, None, "IID('{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}')") , ], 1 , 1 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
]

IDeviceInfos_vtables_dispatch_ = 1
IDeviceInfos_vtables_ = [
    (( 'Item' , 'Index' , 'ppResult' , ), 0, (0, (), [ (16396, 1, None, None) ,
             (16393, 10, None, "IID('{2A99020A-E325-4454-95E0-136726ED4818}')") , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Count' , 'pResult' , ), 1, (1, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( '_NewEnum' , 'ppResult' , ), -4, (-4, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 1 , )),
]

IDeviceManager_vtables_dispatch_ = 1
IDeviceManager_vtables_ = [
    (( 'DeviceInfos' , 'ppResult' , ), 1, (1, (), [ (16393, 10, None, "IID('{FE076B64-8406-4E92-9CAC-9093F378E05F}')") , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 1024 , )),
    (( 'RegisterEvent' , 'EventID' , 'DeviceID' , ), 2, (2, (), [ (8, 1, None, None) ,
             (8, 49, "'*'", None) , ], 1 , 1 , 4 , 0 , 32 , (3, 32, None, None) , 0 , )),
    (( 'UnregisterEvent' , 'EventID' , 'DeviceID' , ), 3, (3, (), [ (8, 1, None, None) ,
             (8, 49, "'*'", None) , ], 1 , 1 , 4 , 0 , 36 , (3, 32, None, None) , 0 , )),
    (( 'RegisterPersistentEvent' , 'Command' , 'Name' , 'Description' , 'Icon' ,
             'EventID' , 'DeviceID' , ), 4, (4, (), [ (8, 1, None, None) , (8, 1, None, None) ,
             (8, 1, None, None) , (8, 1, None, None) , (8, 1, None, None) , (8, 49, "'*'", None) , ], 1 , 1 , 4 , 0 , 40 , (3, 32, None, None) , 0 , )),
    (( 'UnregisterPersistentEvent' , 'Command' , 'Name' , 'Description' , 'Icon' ,
             'EventID' , 'DeviceID' , ), 5, (5, (), [ (8, 1, None, None) , (8, 1, None, None) ,
             (8, 1, None, None) , (8, 1, None, None) , (8, 1, None, None) , (8, 49, "'*'", None) , ], 1 , 1 , 4 , 0 , 44 , (3, 32, None, None) , 0 , )),
]

IFilter_vtables_dispatch_ = 1
IFilter_vtables_ = [
    (( 'Name' , 'pbstrResult' , ), 1, (1, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Description' , 'pbstrResult' , ), 2, (2, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'FilterID' , 'pbstrResult' , ), 3, (3, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
    (( 'Properties' , 'ppResult' , ), 4, (4, (), [ (16393, 10, None, "IID('{40571E58-A308-470A-80AA-FA10F88793A0}')") , ], 1 , 2 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
]

IFilterInfo_vtables_dispatch_ = 1
IFilterInfo_vtables_ = [
    (( 'Name' , 'pbstrResult' , ), 1, (1, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Description' , 'pbstrResult' , ), 2, (2, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'FilterID' , 'pbstrResult' , ), 3, (3, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
]

IFilterInfos_vtables_dispatch_ = 1
IFilterInfos_vtables_ = [
    (( 'Item' , 'Index' , 'ppResult' , ), 0, (0, (), [ (16396, 1, None, None) ,
             (16393, 10, None, "IID('{EFD1219F-8229-4B30-809D-8F6D83341569}')") , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Count' , 'pResult' , ), 1, (1, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( '_NewEnum' , 'ppResult' , ), -4, (-4, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 1 , )),
]

IFilters_vtables_dispatch_ = 1
IFilters_vtables_ = [
    (( 'Item' , 'Index' , 'ppResult' , ), 0, (0, (), [ (3, 1, None, None) ,
             (16393, 10, None, "IID('{851E9802-B338-4AB3-BB6B-6AA57CC699D0}')") , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Count' , 'pResult' , ), 1, (1, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( '_NewEnum' , 'ppResult' , ), -4, (-4, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 1 , )),
    (( 'Add' , 'FilterID' , 'Index' , ), 2, (2, (), [ (8, 1, None, None) ,
             (3, 49, '0', None) , ], 1 , 1 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
    (( 'Remove' , 'Index' , ), 3, (3, (), [ (3, 1, None, None) , ], 1 , 1 , 4 , 0 , 44 , (3, 0, None, None) , 0 , )),
]

IFormats_vtables_dispatch_ = 1
IFormats_vtables_ = [
    (( 'Item' , 'Index' , 'pbstrResult' , ), 0, (0, (), [ (3, 1, None, None) ,
             (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Count' , 'pResult' , ), 1, (1, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( '_NewEnum' , 'ppResult' , ), -4, (-4, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 1 , )),
]

IImageFile_vtables_dispatch_ = 1
IImageFile_vtables_ = [
    (( 'FormatID' , 'pbstrResult' , ), 1, (1, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'FileExtension' , 'pbstrResult' , ), 2, (2, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'FileData' , 'ppResult' , ), 3, (3, (), [ (16393, 10, None, "IID('{696F2367-6619-49BD-BA96-904DC2609990}')") , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
    (( 'ARGBData' , 'ppResult' , ), 4, (4, (), [ (16393, 10, None, "IID('{696F2367-6619-49BD-BA96-904DC2609990}')") , ], 1 , 2 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
    (( 'Height' , 'plResult' , ), 5, (5, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 44 , (3, 0, None, None) , 0 , )),
    (( 'Width' , 'plResult' , ), 6, (6, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 48 , (3, 0, None, None) , 0 , )),
    (( 'HorizontalResolution' , 'plfResult' , ), 7, (7, (), [ (16389, 10, None, None) , ], 1 , 2 , 4 , 0 , 52 , (3, 0, None, None) , 0 , )),
    (( 'VerticalResolution' , 'plfResult' , ), 8, (8, (), [ (16389, 10, None, None) , ], 1 , 2 , 4 , 0 , 56 , (3, 0, None, None) , 0 , )),
    (( 'PixelDepth' , 'plResult' , ), 9, (9, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 60 , (3, 0, None, None) , 0 , )),
    (( 'IsIndexedPixelFormat' , 'pboolResult' , ), 10, (10, (), [ (16395, 10, None, None) , ], 1 , 2 , 4 , 0 , 64 , (3, 0, None, None) , 0 , )),
    (( 'IsAlphaPixelFormat' , 'pboolResult' , ), 11, (11, (), [ (16395, 10, None, None) , ], 1 , 2 , 4 , 0 , 68 , (3, 0, None, None) , 0 , )),
    (( 'IsExtendedPixelFormat' , 'pboolResult' , ), 12, (12, (), [ (16395, 10, None, None) , ], 1 , 2 , 4 , 0 , 72 , (3, 0, None, None) , 0 , )),
    (( 'IsAnimated' , 'pboolResult' , ), 13, (13, (), [ (16395, 10, None, None) , ], 1 , 2 , 4 , 0 , 76 , (3, 0, None, None) , 0 , )),
    (( 'FrameCount' , 'plResult' , ), 14, (14, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 80 , (3, 0, None, None) , 0 , )),
    (( 'ActiveFrame' , 'plResult' , ), 15, (15, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 84 , (3, 0, None, None) , 0 , )),
    (( 'ActiveFrame' , 'plResult' , ), 15, (15, (), [ (3, 1, None, None) , ], 1 , 4 , 4 , 0 , 88 , (3, 0, None, None) , 0 , )),
    (( 'Properties' , 'ppResult' , ), 16, (16, (), [ (16393, 10, None, "IID('{40571E58-A308-470A-80AA-FA10F88793A0}')") , ], 1 , 2 , 4 , 0 , 92 , (3, 0, None, None) , 0 , )),
    (( 'LoadFile' , 'Filename' , ), 17, (17, (), [ (8, 1, None, None) , ], 1 , 1 , 4 , 0 , 96 , (3, 0, None, None) , 0 , )),
    (( 'SaveFile' , 'Filename' , ), 18, (18, (), [ (8, 1, None, None) , ], 1 , 1 , 4 , 0 , 100 , (3, 0, None, None) , 0 , )),
]

IImageProcess_vtables_dispatch_ = 1
IImageProcess_vtables_ = [
    (( 'FilterInfos' , 'ppResult' , ), 1, (1, (), [ (16393, 10, None, "IID('{AF49723A-499C-411C-B19A-1B8244D67E44}')") , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Filters' , 'ppResult' , ), 2, (2, (), [ (16393, 10, None, "IID('{C82FFED4-0A8D-4F85-B90A-AC8E720D39C1}')") , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'Apply' , 'Source' , 'ppResult' , ), 4, (4, (), [ (9, 1, None, "IID('{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}')") ,
             (16393, 10, None, "IID('{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}')") , ], 1 , 1 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
]

IItem_vtables_dispatch_ = 1
IItem_vtables_ = [
    (( 'ItemID' , 'pbstrResult' , ), 1, (1, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Properties' , 'ppResult' , ), 2, (2, (), [ (16393, 10, None, "IID('{40571E58-A308-470A-80AA-FA10F88793A0}')") , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'Items' , 'ppResult' , ), 3, (3, (), [ (16393, 10, None, "IID('{46102071-60B4-4E58-8620-397D17B0BB5B}')") , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
    (( 'Formats' , 'ppResult' , ), 4, (4, (), [ (16393, 10, None, "IID('{882A274F-DF2F-4F6D-9F5A-AF4FD484530D}')") , ], 1 , 2 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
    (( 'Commands' , 'ppResult' , ), 5, (5, (), [ (16393, 10, None, "IID('{C53AE9D5-6D91-4815-AF93-5F1E1B3B08BD}')") , ], 1 , 2 , 4 , 0 , 44 , (3, 0, None, None) , 0 , )),
    (( 'WiaItem' , 'ppResult' , ), 6, (6, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 48 , (3, 0, None, None) , 0 , )),
    (( 'Transfer' , 'FormatID' , 'pvResult' , ), 7, (7, (), [ (8, 49, "'{00000000-0000-0000-0000-000000000000}'", None) ,
             (16396, 10, None, None) , ], 1 , 1 , 4 , 0 , 52 , (3, 32, None, None) , 0 , )),
    (( 'ExecuteCommand' , 'CommandID' , 'ppResult' , ), 8, (8, (), [ (8, 1, None, None) ,
             (16393, 10, None, "IID('{68F2BF12-A755-4E2B-9BCD-37A22587D078}')") , ], 1 , 1 , 4 , 0 , 56 , (3, 0, None, None) , 0 , )),
]

IItems_vtables_dispatch_ = 1
IItems_vtables_ = [
    (( 'Item' , 'Index' , 'ppResult' , ), 0, (0, (), [ (3, 1, None, None) ,
             (16393, 10, None, "IID('{68F2BF12-A755-4E2B-9BCD-37A22587D078}')") , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Count' , 'pResult' , ), 1, (1, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( '_NewEnum' , 'ppResult' , ), -4, (-4, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 36 , (3, 0, None, None) , 1 , )),
    (( 'Add' , 'Name' , 'Flags' , ), 2, (2, (), [ (8, 1, None, None) ,
             (3, 1, None, None) , ], 1 , 1 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
    (( 'Remove' , 'Index' , ), 3, (3, (), [ (3, 1, None, None) , ], 1 , 1 , 4 , 0 , 44 , (3, 0, None, None) , 0 , )),
]

IProperties_vtables_dispatch_ = 1
IProperties_vtables_ = [
    (( 'Item' , 'Index' , 'ppResult' , ), 0, (0, (), [ (16396, 1, None, None) ,
             (16393, 10, None, "IID('{706038DC-9F4B-4E45-88E2-5EB7D665B815}')") , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Count' , 'pResult' , ), 1, (1, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'Exists' , 'Index' , 'pboolResult' , ), 2, (2, (), [ (16396, 1, None, None) ,
             (16395, 10, None, None) , ], 1 , 1 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
    (( '_NewEnum' , 'ppResult' , ), -4, (-4, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 40 , (3, 0, None, None) , 1 , )),
]

IProperty_vtables_dispatch_ = 1
IProperty_vtables_ = [
    (( 'Value' , 'pvResult' , ), 0, (0, (), [ (16396, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Value' , 'pvResult' , ), 0, (0, (), [ (16396, 1, None, None) , ], 1 , 4 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'Value' , 'pvResult' , ), 0, (0, (), [ (16396, 1, None, None) , ], 1 , 8 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
    (( 'Name' , 'pbstrResult' , ), 1, (1, (), [ (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
    (( 'PropertyID' , 'plResult' , ), 2, (2, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 44 , (3, 0, None, None) , 0 , )),
    (( 'Type' , 'plResult' , ), 3, (3, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 48 , (3, 0, None, None) , 0 , )),
    (( 'IsReadOnly' , 'pboolResult' , ), 4, (4, (), [ (16395, 10, None, None) , ], 1 , 2 , 4 , 0 , 52 , (3, 0, None, None) , 0 , )),
    (( 'IsVector' , 'pboolResult' , ), 5, (5, (), [ (16395, 10, None, None) , ], 1 , 2 , 4 , 0 , 56 , (3, 0, None, None) , 0 , )),
    (( 'SubType' , 'pResult' , ), 6, (6, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 60 , (3, 0, None, None) , 0 , )),
    (( 'SubTypeDefault' , 'pvResult' , ), 7, (7, (), [ (16396, 10, None, None) , ], 1 , 2 , 4 , 0 , 64 , (3, 0, None, None) , 0 , )),
    (( 'SubTypeValues' , 'ppResult' , ), 8, (8, (), [ (16393, 10, None, "IID('{696F2367-6619-49BD-BA96-904DC2609990}')") , ], 1 , 2 , 4 , 0 , 68 , (3, 0, None, None) , 0 , )),
    (( 'SubTypeMin' , 'plResult' , ), 9, (9, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 72 , (3, 0, None, None) , 0 , )),
    (( 'SubTypeMax' , 'plResult' , ), 10, (10, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 76 , (3, 0, None, None) , 0 , )),
    (( 'SubTypeStep' , 'plResult' , ), 11, (11, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 80 , (3, 0, None, None) , 0 , )),
]

IRational_vtables_dispatch_ = 1
IRational_vtables_ = [
    (( 'Value' , 'pResult' , ), 0, (0, (), [ (16389, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Numerator' , 'plResult' , ), 1, (1, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'Numerator' , 'plResult' , ), 1, (1, (), [ (3, 1, None, None) , ], 1 , 4 , 4 , 0 , 36 , (3, 0, None, None) , 0 , )),
    (( 'Denominator' , 'plResult' , ), 2, (2, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
    (( 'Denominator' , 'plResult' , ), 2, (2, (), [ (3, 1, None, None) , ], 1 , 4 , 4 , 0 , 44 , (3, 0, None, None) , 0 , )),
]

IVector_vtables_dispatch_ = 1
IVector_vtables_ = [
    (( 'Item' , 'Index' , 'pResult' , ), 0, (0, (), [ (3, 1, None, None) ,
             (16396, 10, None, None) , ], 1 , 2 , 4 , 0 , 28 , (3, 0, None, None) , 0 , )),
    (( 'Item' , 'Index' , 'pResult' , ), 0, (0, (), [ (3, 1, None, None) ,
             (16396, 1, None, None) , ], 1 , 4 , 4 , 0 , 32 , (3, 0, None, None) , 0 , )),
    (( 'Count' , 'plResult' , ), 1, (1, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 40 , (3, 0, None, None) , 0 , )),
    (( 'Picture' , 'Width' , 'Height' , 'pvResult' , ), 2, (2, (), [
             (3, 49, '0', None) , (3, 49, '0', None) , (16396, 10, None, None) , ], 1 , 2 , 4 , 0 , 44 , (3, 0, None, None) , 0 , )),
    (( 'Picture' , 'Width' , 'Height' , 'pvResult' , ), 2, (2, (), [
             (3, 49, '0', None) , (3, 49, '0', None) , (16396, 10, None, None) , ], 1 , 2 , 4 , 0 , 44 , (3, 0, None, None) , 0 , )),
    (( 'ImageFile' , 'Width' , 'Height' , 'ppResult' , ), 3, (3, (), [
             (3, 49, '0', None) , (3, 49, '0', None) , (16393, 10, None, "IID('{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}')") , ], 1 , 2 , 4 , 0 , 48 , (3, 0, None, None) , 0 , )),
    (( 'ImageFile' , 'Width' , 'Height' , 'ppResult' , ), 3, (3, (), [
             (3, 49, '0', None) , (3, 49, '0', None) , (16393, 10, None, "IID('{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}')") , ], 1 , 2 , 4 , 0 , 48 , (3, 0, None, None) , 0 , )),
    (( 'BinaryData' , 'pvResult' , ), 4, (4, (), [ (16396, 10, None, None) , ], 1 , 2 , 4 , 0 , 52 , (3, 0, None, None) , 0 , )),
    (( 'BinaryData' , 'pvResult' , ), 4, (4, (), [ (16396, 1, None, None) , ], 1 , 4 , 4 , 0 , 56 , (3, 0, None, None) , 0 , )),
    (( 'String' , 'Unicode' , 'pbstrResult' , ), 5, (5, (), [ (11, 49, 'True', None) ,
             (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 60 , (3, 0, None, None) , 0 , )),
    (( 'String' , 'Unicode' , 'pbstrResult' , ), 5, (5, (), [ (11, 49, 'True', None) ,
             (16392, 10, None, None) , ], 1 , 2 , 4 , 0 , 60 , (3, 0, None, None) , 0 , )),
    (( 'Date' , 'pdResult' , ), 6, (6, (), [ (16391, 10, None, None) , ], 1 , 2 , 4 , 0 , 64 , (3, 0, None, None) , 0 , )),
    (( 'Date' , 'pdResult' , ), 6, (6, (), [ (7, 1, None, None) , ], 1 , 4 , 4 , 0 , 68 , (3, 0, None, None) , 0 , )),
    (( '_NewEnum' , 'ppResult' , ), -4, (-4, (), [ (16397, 10, None, None) , ], 1 , 2 , 4 , 0 , 72 , (3, 0, None, None) , 1 , )),
    (( 'Add' , 'Value' , 'Index' , ), 7, (7, (), [ (16396, 1, None, None) ,
             (3, 49, '0', None) , ], 1 , 1 , 4 , 0 , 76 , (3, 0, None, None) , 0 , )),
    (( 'Remove' , 'Index' , 'pvResult' , ), 8, (8, (), [ (3, 1, None, None) ,
             (16396, 10, None, None) , ], 1 , 1 , 4 , 0 , 80 , (3, 0, None, None) , 0 , )),
    (( 'Clear' , ), 9, (9, (), [ ], 1 , 1 , 4 , 0 , 84 , (3, 0, None, None) , 0 , )),
    (( 'SetFromString' , 'Value' , 'Resizable' , 'Unicode' , ), 10, (10, (), [
             (8, 1, None, None) , (11, 49, 'True', None) , (11, 49, 'True', None) , ], 1 , 1 , 4 , 0 , 88 , (3, 0, None, None) , 0 , )),
]

RecordMap = {
}

CLSIDToClassMap = {
    '{318D6B52-9B1C-4E3B-8D90-1F0E857FA9B0}' : FilterInfo,
    '{56FA88D3-F3DA-4DE3-94E8-811040C3CCD4}' : FilterInfos,
    '{72226184-AFBB-4059-BF55-0F6C076E669D}' : DeviceCommand,
    '{850D1D11-70F3-4BE5-9A11-77AA6B2BB201}' : CommonDialog,
    '{2014DE3F-3723-4178-8643-3317A32D4A2B}' : Property,
    '{C82FFED4-0A8D-4F85-B90A-AC8E720D39C1}' : IFilters,
    '{40571E58-A308-470A-80AA-FA10F88793A0}' : IProperties,
    '{B4760F13-D9F3-4DF8-94B5-D225F86EE9A1}' : ICommonDialog,
    '{31CDD60C-C04C-424D-95FC-36A52646D71C}' : Filters,
    '{706038DC-9F4B-4E45-88E2-5EB7D665B815}' : IProperty,
    '{41506929-7855-4392-9E6F-98D88513E55D}' : IImageProcess,
    '{68F2BF12-A755-4E2B-9BCD-37A22587D078}' : IItem,
    '{36F479F3-C258-426E-B5FA-2793DCFDA881}' : Item,
    '{52AD8A74-F064-4F4C-8544-FF494D349F7B}' : Filter,
    '{C53AE9D5-6D91-4815-AF93-5F1E1B3B08BD}' : IDeviceCommands,
    '{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}' : IImageFile,
    '{0C5672F9-3EDC-4B24-95B5-A6C54C0B79AD}' : Rational,
    '{2E9A5206-2360-49DF-9D9B-1762B4BEAE77}' : _IDeviceManagerEvents,
    '{F09CFB7A-E561-4625-9BB5-208BCA0DE09F}' : DeviceInfo,
    '{46102071-60B4-4E58-8620-397D17B0BB5B}' : IItems,
    '{3BF1B24A-01A5-4AA3-91F9-25A60B50E49B}' : IRational,
    '{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}' : IDevice,
    '{AF49723A-499C-411C-B19A-1B8244D67E44}' : IFilterInfos,
    '{25B047DB-4AAD-4FC2-A0BE-31DDA687FF32}' : DeviceCommands,
    '{DBAA8843-B1C4-4EDC-B7E0-D6F61162BE58}' : Device,
    '{BD0D38E4-74C8-4904-9B5A-269F8E9994E9}' : ImageProcess,
    '{7CF694C0-F589-451C-B56E-398B5855B05E}' : IDeviceCommand,
    '{73856D9A-2720-487A-A584-21D5774E9D0F}' : IDeviceManager,
    '{B243B765-CA9C-4F30-A457-C8B2B57A585E}' : Items,
    '{617CF892-783C-43D3-B04B-F0F1DE3B326D}' : DeviceEvent,
    '{6F62E261-0FE6-476B-A244-50CF7440DDEB}' : Formats,
    '{96F887FC-08B1-4F97-A69C-75280C6A9CF8}' : Properties,
    '{03985C95-581B-44D1-9403-8488B347538B}' : IDeviceEvents,
    '{3563A59A-BBCD-4C86-94A0-92136C80A8B4}' : DeviceEvents,
    '{4DD1D1C3-B36A-4EB4-AAEF-815891A58A30}' : Vector,
    '{2A99020A-E325-4454-95E0-136726ED4818}' : IDeviceInfo,
    '{E1C5D730-7E97-4D8A-9E42-BBAE87C2059F}' : DeviceManager,
    '{851E9802-B338-4AB3-BB6B-6AA57CC699D0}' : IFilter,
    '{882A274F-DF2F-4F6D-9F5A-AF4FD484530D}' : IFormats,
    '{2DFEE16B-E4AC-4A19-B660-AE71A745D34F}' : DeviceInfos,
    '{80D0880A-BB10-4722-82D1-07DC8DA157E2}' : IDeviceEvent,
    '{FE076B64-8406-4E92-9CAC-9093F378E05F}' : IDeviceInfos,
    '{696F2367-6619-49BD-BA96-904DC2609990}' : IVector,
    '{A2E6DDA0-06EF-4DF3-B7BD-5AA224BB06E8}' : ImageFile,
    '{EFD1219F-8229-4B30-809D-8F6D83341569}' : IFilterInfo,
}
CLSIDToPackageMap = {}
win32com.client.CLSIDToClass.RegisterCLSIDsFromDict( CLSIDToClassMap )
VTablesToPackageMap = {}
VTablesToClassMap = {
    '{46102071-60B4-4E58-8620-397D17B0BB5B}' : 'IItems',
    '{EFD1219F-8229-4B30-809D-8F6D83341569}' : 'IFilterInfo',
    '{706038DC-9F4B-4E45-88E2-5EB7D665B815}' : 'IProperty',
    '{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}' : 'IDevice',
    '{AF49723A-499C-411C-B19A-1B8244D67E44}' : 'IFilterInfos',
    '{C82FFED4-0A8D-4F85-B90A-AC8E720D39C1}' : 'IFilters',
    '{B4760F13-D9F3-4DF8-94B5-D225F86EE9A1}' : 'ICommonDialog',
    '{7CF694C0-F589-451C-B56E-398B5855B05E}' : 'IDeviceCommand',
    '{73856D9A-2720-487A-A584-21D5774E9D0F}' : 'IDeviceManager',
    '{40571E58-A308-470A-80AA-FA10F88793A0}' : 'IProperties',
    '{41506929-7855-4392-9E6F-98D88513E55D}' : 'IImageProcess',
    '{68F2BF12-A755-4E2B-9BCD-37A22587D078}' : 'IItem',
    '{80D0880A-BB10-4722-82D1-07DC8DA157E2}' : 'IDeviceEvent',
    '{2A99020A-E325-4454-95E0-136726ED4818}' : 'IDeviceInfo',
    '{3BF1B24A-01A5-4AA3-91F9-25A60B50E49B}' : 'IRational',
    '{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}' : 'IImageFile',
    '{C53AE9D5-6D91-4815-AF93-5F1E1B3B08BD}' : 'IDeviceCommands',
    '{851E9802-B338-4AB3-BB6B-6AA57CC699D0}' : 'IFilter',
    '{882A274F-DF2F-4F6D-9F5A-AF4FD484530D}' : 'IFormats',
    '{03985C95-581B-44D1-9403-8488B347538B}' : 'IDeviceEvents',
    '{FE076B64-8406-4E92-9CAC-9093F378E05F}' : 'IDeviceInfos',
    '{696F2367-6619-49BD-BA96-904DC2609990}' : 'IVector',
}


NamesToIIDMap = {
    'IRational' : '{3BF1B24A-01A5-4AA3-91F9-25A60B50E49B}',
    'IDevice' : '{3714EAC4-F413-426B-B1E8-DEF2BE99EA55}',
    'IDeviceEvents' : '{03985C95-581B-44D1-9403-8488B347538B}',
    'IItems' : '{46102071-60B4-4E58-8620-397D17B0BB5B}',
    'IDeviceManager' : '{73856D9A-2720-487A-A584-21D5774E9D0F}',
    'IProperties' : '{40571E58-A308-470A-80AA-FA10F88793A0}',
    'IDeviceCommands' : '{C53AE9D5-6D91-4815-AF93-5F1E1B3B08BD}',
    'IProperty' : '{706038DC-9F4B-4E45-88E2-5EB7D665B815}',
    'IFilterInfo' : '{EFD1219F-8229-4B30-809D-8F6D83341569}',
    'ICommonDialog' : '{B4760F13-D9F3-4DF8-94B5-D225F86EE9A1}',
    'IImageFile' : '{F4243B65-3F63-4D99-93CD-86B6D62C5EB2}',
    'IDeviceInfos' : '{FE076B64-8406-4E92-9CAC-9093F378E05F}',
    'IDeviceCommand' : '{7CF694C0-F589-451C-B56E-398B5855B05E}',
    'IDeviceEvent' : '{80D0880A-BB10-4722-82D1-07DC8DA157E2}',
    'IFilters' : '{C82FFED4-0A8D-4F85-B90A-AC8E720D39C1}',
    'IFormats' : '{882A274F-DF2F-4F6D-9F5A-AF4FD484530D}',
    'IFilterInfos' : '{AF49723A-499C-411C-B19A-1B8244D67E44}',
    'IItem' : '{68F2BF12-A755-4E2B-9BCD-37A22587D078}',
    'IFilter' : '{851E9802-B338-4AB3-BB6B-6AA57CC699D0}',
    'IVector' : '{696F2367-6619-49BD-BA96-904DC2609990}',
    'IImageProcess' : '{41506929-7855-4392-9E6F-98D88513E55D}',
    'IDeviceInfo' : '{2A99020A-E325-4454-95E0-136726ED4818}',
    '_IDeviceManagerEvents' : '{2E9A5206-2360-49DF-9D9B-1762B4BEAE77}',
}

win32com.client.constants.__dicts__.append(constants.__dict__)

