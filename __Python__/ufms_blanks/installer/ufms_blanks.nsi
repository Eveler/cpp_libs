; Script generated with the Venis Install Wizard

; Define your application name
!define APPNAME "Бланки"
!define APPNAMEANDVERSION "Бланки 0.1"

; Main Install settings
Name "${APPNAMEANDVERSION}"
InstallDir "c:\ufms_blanks"
InstallDirRegKey HKLM "Software\${APPNAME}" ""
OutFile "Output\setup.exe"

; Version Information
VIAddVersionKey  "CompanyName"     "Савенко Михаил"
VIAddVersionKey  "LegalCopyright"  "(c)Савенко Михаил"
VIAddVersionKey  "ProductName"     "Бланки"
VIAddVersionKey  "ProductVersion"  "0.1"
VIProductVersion "0.1.0.0"

; Modern interface settings
!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_FINISHPAGE_RUN "python $INSTDIR\ufms_blanks.pyw"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Set languages (first is default language)
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_RESERVEFILE_LANGDLL

;Function .onInit
Function inst_prereq
	GetTempFileName $0
	File /oname=$0  "D:\Distr\Progr\python\ActivePython-3.4.1.0-win32-x86.msi"
	;ExecWait '"msiexec" /i $0 /passive /norestart'
	ExecWait '"msiexec" /i $0'
	Delete $0
	GetTempFileName $0
	File /oname=$0 "D:\Distr\Progr\python\PyQt\PyQt5-5.3.2-gpl-Py3.4-Qt5.3.1-x32.exe"
	IfFileExists C:\Python34\Lib\site-packages\PyQt5\__init__.py +2
		;ExecWait '"$0" /S'
		ExecWait '"$0"'
	Delete $0
FunctionEnd

Section "Бланки" Section1

	; Set Section properties
	SetOverwrite on

	; Set Section Files and Shortcuts
	SetOutPath "$INSTDIR\"
	File "..\config.py"
	File "..\db.py"
	File "..\icons.py"
	File "..\ufms_blanks.pyw"
	SetOutPath "$INSTDIR\addr_base\"
	File "..\addr_base\db.py"
	File "..\addr_base\kladr.py"
	File "..\addr_base\net.py"
	File "..\addr_base\__init__.py"
	SetOutPath "$INSTDIR\addr_base\7z\"
	File "..\addr_base\7z\7z.dll"
	File "..\addr_base\7z\7z.exe"
	SetOutPath "$INSTDIR\templates\"
	File "..\templates\editor.py"
	File "..\templates\__init__.py"
	File "..\templates\адресный листок прибытия xml.utpl"
	File "..\templates\адресный листок убытия xml.utpl"
	SetOutPath "$PROFILE\.ufms_blanks\"
	File "C:\Users\Savenko\.ufms_blanks\ufms_blanks.ini"
	SetOutPath "$INSTDIR\"
	File /r "C:\Python34\Lib\site-packages\dbf"
	File /r "C:\Users\Savenko\AppData\Roaming\Python\Python34\site-packages\sqlalchemy"
	CreateShortCut "$DESKTOP\Бланки.lnk" "$INSTDIR\ufms_blanks.pyw"
	CreateDirectory "$SMPROGRAMS\Бланки"
	CreateShortCut "$SMPROGRAMS\Бланки\Бланки.lnk" "$INSTDIR\ufms_blanks.pyw"
	CreateShortCut "$SMPROGRAMS\Бланки\Uninstall.lnk" "$INSTDIR\uninstall.exe"
	
	Call inst_prereq

SectionEnd

Section -FinishSection

	WriteRegStr HKLM "Software\${APPNAME}" "" "$INSTDIR"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayName" "${APPNAME}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "UninstallString" "$INSTDIR\uninstall.exe"
	WriteUninstaller "$INSTDIR\uninstall.exe"

SectionEnd

; Modern install component descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${Section1} ""
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;Uninstall section
Section Uninstall

	;Remove from registry...
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"
	DeleteRegKey HKLM "SOFTWARE\${APPNAME}"

	; Delete self
	Delete "$INSTDIR\uninstall.exe"

	; Delete Shortcuts
	Delete "$DESKTOP\Бланки.lnk"
	Delete "$SMPROGRAMS\Бланки\Бланки.lnk"
	Delete "$SMPROGRAMS\Бланки\Uninstall.lnk"

	; Clean up Бланки
	Delete "$INSTDIR\config.py"
	Delete "$INSTDIR\db.py"
	Delete "$INSTDIR\icons.py"
	Delete "$INSTDIR\ufms_blanks.pyw"
	Delete "$INSTDIR\addr_base\db.py"
	Delete "$INSTDIR\addr_base\kladr.py"
	Delete "$INSTDIR\addr_base\net.py"
	Delete "$INSTDIR\addr_base\__init__.py"
	Delete "$INSTDIR\addr_base\7z\7z.dll"
	Delete "$INSTDIR\addr_base\7z\7z.exe"
	Delete "$INSTDIR\templates\editor.py"
	Delete "$INSTDIR\templates\__init__.py"
	Delete "$INSTDIR\templates\адресный листок прибытия xml.utpl"
	Delete "$INSTDIR\templates\адресный листок убытия xml.utpl"
	Delete "$INSTDIR\templates\ufms_blanks.ini"

	; Remove remaining directories
	RMDir /r "$INSTDIR\dbf"
	RMDir /r "$INSTDIR\sqlalchemy"
	RMDir "$SMPROGRAMS\Бланки"
	RMDir /r "$INSTDIR\templates\"
	RMDir /r "$INSTDIR\addr_base\7z\"
	RMDir /r "$INSTDIR\addr_base\"
	RMDir /r "$INSTDIR\"

SectionEnd

; eof