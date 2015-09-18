import sys

from cx_Freeze import setup, Executable

base = None
if sys.platform == "win32":
    base = "Win32GUI"
icon_file = "1414939292_Online_writing.ico"
buildOptions = dict(icon = icon_file, excludes = "dbf.ver_2", optimize = 2, compressed = True)

setup(
        name = "blanks",
        version = "0.1",
        description = "Sample cx_Freeze script",
        options = dict(build_exe = buildOptions),
        executables = [Executable("ufms_blanks.py", base = base)])