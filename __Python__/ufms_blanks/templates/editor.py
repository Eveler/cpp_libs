# -*- coding: utf-8 -*-
import json
from json.decoder import WHITESPACE
import logging
from traceback import print_exc

try:
    # from PyQt5.Qt import (QMainWindow, QApplication, QFileDialog, QToolBar, QWidget, QVBoxLayout, QTextEdit, QTimer,
    # QLabel, QColor, QByteArray, QBuffer, QPixmap, QBoxLayout, QPainter, QPen,
    # QPrintPreviewWidget, QPrinter, QPrintDialog)
    from PyQt5.Qt import *
except ImportError:
    # from PyQt4.Qt import (QMainWindow, QApplication, QFileDialog, QToolBar, QWidget, QVBoxLayout, QTextEdit, QTimer,
    # QLabel, QColor, QByteArray, QBuffer, QPixmap, QBoxLayout, QPainter, QPen,
    # QPrintPreviewWidget, QPrinter, QPrintDialog)
    # from PyQt4.Qt import *
    pass

__author__ = 'Savenko'


class ReportDict(dict):
    def __init__(self):
        super(dict, self).__init__()

    def __getattr__(self, item):
        if isinstance(self[item], dict) and not isinstance(self[item], ReportDict):
            obj = ReportDict()
            for k, v in self[item].items():
                obj.__setattr__(k, v)
            return obj
        else:
            return self[item]

    def __setattr__(self, key, value):
        if isinstance(value, dict) and not isinstance(value, ReportDict):
            obj = ReportDict()
            for k, v in value.items():
                obj.__setattr__(k, v)
            self[key] = obj
        else:
            self[key] = value


class Report(ReportDict):
    def __init__(self):
        super(ReportDict, self).__init__()
        # self["report"] = {'page': {"size": "A4"}}
        page = [ReportDict()]
        page[0].size = "A4"
        page[0].orientation = "Portrait"
        # image = QPixmap("D:\\devel\\python\\ufms_blanks\\templates\\ScanImage001bw.png")
        # image = image.convertToFormat(QImage.Format_ARGB32)
        # image = image.scaledToHeight(image.height()*96/600)
        # img = _MyDict()
        # img.x = 0
        # img.y = 0
        # ba = QByteArray()
        # buf = QBuffer(ba)
        # buf.open(QBuffer.WriteOnly)
        # image.save(buf, 'PNG')
        # img.data = str(ba.toBase64().data())
        # page[0].Image = img
        report = ReportDict()
        report.pages = page
        self.report = report


class _ReportDecoder(json.JSONDecoder):
    def decode(self, s, _w=WHITESPACE.match):
        ret = json.JSONDecoder.decode(self, s, _w)
        if "report" in ret:
            rep = Report()
            rep.report = ret["report"]
            return rep
        return ret


class ReportPreview(QWidget):
    def __init__(self, parent=None, report=''):
        from icons import icon_fit, icon_zoom_in, icon_zoom_out, icon_print, icon_pdf

        super(QWidget, self).__init__(parent)

        self.set_data()
        if report:
            self.set_report(report)
        else:
            self.report = report

        layout = QVBoxLayout(self)
        self.setLayout(layout)

        toolbar = QToolBar(self)
        toolbar.addAction(icon_fit, QObject().tr(u"Вместить"), self.fit)
        toolbar.addSeparator()
        toolbar.addAction(icon_zoom_in, QObject().tr(u"Увеличить"), self.zoom_in)
        toolbar.addAction(icon_zoom_out, QObject().tr(u"Уменьшить"), self.zoom_out)
        toolbar.addSeparator()
        toolbar.addAction(icon_print, QObject().tr(u"Распечатать"), self.print)
        toolbar.addAction(icon_pdf, QObject().tr(u"Сохранить в PDF"), self.print2pdf)
        layout.addWidget(toolbar)

        self.printer = QPrinter()
        self.preview = QPrintPreviewWidget(self.printer, self)
        self.preview.paintRequested.connect(self.generate)
        layout.addWidget(self.preview)

    def fit(self):
        self.preview.fitToWidth()

    def zoom_in(self):
        self.preview.zoomIn()

    def zoom_out(self):
        self.preview.zoomOut()

    def print(self):
        d = QPrintDialog(self.printer, self)
        if d.exec_() == QPrintDialog.Accepted:
            self.preview.print_()

    def print2pdf(self):
        file_name = QFileDialog.getSaveFileName(self, "Сохранить в", filter="PDF (*.pdf)")
        if file_name[0]:
            self.printer.setOutputFileName(file_name[0])
            self.preview.print_()
            self.printer.setOutputFileName(None)

    def set_report(self, report):
        self.report = report
        assert self.report, "report is null"
        self.preview.updatePreview()

    def set_data(self, data={}):
        self.data = data

    def _generate_json(self, painter, report):
        def clear_preview():
            # item = self.preview.layout().takeAt(0)
            # while item:
            # item = self.preview.layout().takeAt(0)
            pass

        # clear_preview()
        # dpi = 96
        # A4 by default, 210 x 297 mm
        # w, h = 210 * dpi / 25, 297 * dpi / 25
        i = 0
        for page in report.report.pages:
            # if i >= self.preview.layout().count():
            # lb = QLabel(self.preview)
            # self.preview.layout().addWidget(lb)
            # lb = self.preview.layout().itemAt(i)
            # i += 1
            # if lb:
            # lb = lb.widget()
            # report = _MyDict()
            # report.page = page
            # if report.page.size == "A3":
            # w, h = 297 * dpi / 25, 420 * dpi / 25
            # pix = QPixmap(w, h)
            # pix.fill(QColor(255, 255, 255))
            # painter = QPainter()
            # for key, val in report.page.items():
            # if key != "size" and key != "orientation":
            # try:
            # painter.begin(pix)
            # if key == "Image":
            # x = val.x
            #                     y = val.y
            #                     ba = QByteArray().fromBase64(val.data)
            #                     p = QPixmap()
            #                     p.loadFromData(ba)
            #                     painter.drawPixmap(x, y, p)
            #                 else:
            #                     params = ['"%s"' % v if type(v) == str else "%s" % v for v in val]
            #                     to_eval = "painter.draw%s(%s)" % (key, ','.join(params))
            #                     eval(to_eval)
            #             except ValueError or TypeError as e:
            #                 clear_preview()
            #                 lb = QLabel(self.preview)
            #                 lb.clear()
            #                 lb.setText(str(e))
            #                 self.preview.layout().addWidget(lb)
            #                 print(e)
            #             except Exception as e:
            #                 print(e)
            #             finally:
            #                 painter.end()
            #     lb.setPixmap(pix)
            if i > 0:
                self.printer.newPage()
            i += 1
            self.printer.setPageSize(eval("QPrinter().%s" % page['size'] if page['size'] else "A4"))
            self.printer.setOrientation(QPrinter.Portrait)
            # setPageMargins(left, top, right, bottom)
            self.printer.setPageMargins(20, 15, 15, 15, QPrinter.Millimeter)
            rep = ReportDict()
            rep.page = page
            for key, val in rep.page.items():
                if key != "size" and key != "orientation":
                    try:
                        if key == "Image":
                            x = val.x
                            y = val.y
                            ba = QByteArray().fromBase64(val.data)
                            p = QPixmap()
                            p.loadFromData(ba)
                            painter.drawPixmap(x, y, p)
                        else:
                            params = ['"%s"' % v if type(v) == str else "%s" % v for v in val]
                            to_eval = "painter.draw%s(%s)" % (key, ','.join(params))
                            print(to_eval)
                            eval(to_eval)
                    except ValueError or TypeError as e:
                        print(e)
                    except Exception as e:
                        print(e)

    def _generate_xml(self, painter, report, **kwargs):
        # init some variables
        class TestData(str):
            def __init__(self, name='TestData'):
                super(TestData, self).__init__()
                self.__str__ = self.__repr__
                self._name = name

            def __getattr__(self, item):
                # return (str(item) + u': Тестовые данные ') * 10
                return TestData(item)

            def __getitem__(self, item):
                # return (str(item) + u': Тестовые данные ') * 10
                return TestData(item)

            def __repr__(self):
                return "%s: %s" % (str(self._name), u' Тестовые данные' * 10)

            def __call__(self, *args, **kwargs):
                return "%s: %s" % (str(self._name), u' Тестовые данные' * 10)

        if report.tag == "template":
            dpi = int(report.get("dpi", 96))
            inch = self.printer.resolution()
            cm = inch / 2.54
            mm = cm / 10
        else:
            if "dpi" in kwargs['kwargs']:
                dpi = kwargs['kwargs']["dpi"]
                inch = kwargs['kwargs']["inch"]
                cm = kwargs['kwargs']["cm"]
                mm = kwargs['kwargs']["mm"]
            if "page_right_px" in kwargs['kwargs']:
                page_right_px = kwargs['kwargs']['page_right_px']
                page_bottom_px = kwargs['kwargs']['page_bottom_px']
                margin_right = kwargs['kwargs']['margin_right']
                margin_bottom = kwargs['kwargs']['margin_bottom']
            args = kwargs['kwargs']
            for key in args:
                if key in ('TestData', 'kwargs', 'self', 'report', 'painter', 'args', 'key'):
                    continue
                vars()[key] = args[key]
        if self.data:
            data = self.data
        else:
            data = TestData()

        # In the cases of loops we need to skip children nodes as they analyze them by himself
        skip_children = False
        # page_count = 0

        self.err_str = ''
        for child in report:
            try:
                if child.tag == "newPage":
                    self.printer.newPage()
                if child.tag in ("newPage", "page"):
                    self.printer.setPageSize(eval("QPrinter().%s" % child.get("size", "A4")))
                    self.printer.setOrientation(eval("QPrinter.%s" % child.get("orientation", "Portrait")))
                    # setPageMargins(left, top, right, bottom)
                    margin_left = float(child.get("margin_left", 20))
                    margin_right = float(child.get("margin_right", 15))
                    margin_top = float(child.get("margin_top", 15))
                    margin_bottom = float(child.get("margin_bottom", 15))
                    self.printer.setPageMargins(margin_left, margin_top, margin_right, margin_bottom,
                                                QPrinter.Millimeter)
                    page_right_px = self.printer.pageLayout().pageSize().sizePixels(self.printer.resolution()).width()
                    page_bottom_px = self.printer.pageLayout().pageSize().sizePixels(self.printer.resolution()).height()
                    # page_left_mm = self.printer.pageLayout().pageSize().size(QPageSize().Millimeter).width()
                    # page_bottom_mm = self.printer.pageLayout().pageSize().sizePixels(self.printer.resolution()).height()
                elif child.tag == "assign":
                    # to_eval = "variables['%s'] = %s" % (child.get("name"), child.get("value", ''))
                    to_eval = "%s = %s" % (child.get("name"), child.get("value", ''))
                    logging.debug(to_eval)
                    # assign(child.get("name"), child.get("value", ''))
                    vars()[child.get("name")] = eval(child.get("value", ''))
                elif child.tag == "script":
                    to_eval = "%s" % child.text
                    logging.debug(to_eval)
                    # eval(to_eval)
                    exec(to_eval)
                elif child.tag == "for":
                    to_eval = "for %s in %s: self._generate_xml(painter, child, kwargs=locals())" % \
                              (child.get("var"), child.get("in", ''))
                    logging.debug(to_eval)
                    # eval(to_eval)
                    exec(to_eval)
                    skip_children = True
                elif child.tag == "while":
                    to_eval = """
%s = eval(%s)
while %s: self._generate_xml(painter, child, kwargs=locals())
                    """ % (child.get("init_var", ''), child.get("init_val", ''), child.get("cond"))
                    logging.debug(to_eval)
                    # eval(to_eval)
                    exec(to_eval)
                    skip_children = True
                elif child.tag == "if":
                    to_eval = "%s" % child.get("cond")
                    logging.debug('if ' + to_eval)
                    if eval(to_eval):
                        self._generate_xml(painter, child, kwargs=locals())
                    skip_children = True
                else:
                    to_eval = "painter.%s(%s)" % (child.tag, child.get("params", ''))
                    logging.debug(to_eval)
                    eval(to_eval)
            except Exception:
                from sys import exc_info

                logging.error('to_eval = "%s"' % to_eval, exc_info=True)
                tp, val, tb = exc_info()
                self.err_str += "%s: %s\n" % \
                                (str(tp).replace('<class ', '').replace("'>:", ''), str(val).replace('\n', '\n<br/>'))
                print_exc()
            if not skip_children:
                self._generate_xml(painter, child, kwargs=locals())

    def generate(self, printer):
        self.err_str = ''
        from xml.etree import ElementTree as ET

        if (self.report is None) or (not self.report):
            return
        assert self.report, "Report is not set"

        painter = QPainter()
        try:
            painter.begin(printer)
            if isinstance(self.report, ReportDict):
                self._generate_json(painter, self.report)
            elif ET.iselement(self.report):
                self._generate_xml(painter, self.report)
            else:
                raise ValueError("Cannot parse report")
        except Exception:
            tp, val, tb = exc_info()
            self.err_str = "%s: %s" % \
                           (str(tp).replace('<class ', '').replace("'>", "'"), str(val).replace('\n', '\n<br/>'))
            print_exc()
        finally:
            painter.end()

    def error_string(self):
        return self.err_str


class MainWnd(QMainWindow):
    def __init__(self):
        self.file_name = ''
        from icons import icon_new, icon_open, icon_floppy, icon_update

        super(QMainWindow, self).__init__()
        self.title = u'[*] Редактор шаблонов'
        self.setWindowTitle(self.title)
        self.setMinimumWidth(640)
        self.setMinimumHeight(480)

        lb = QLabel(u"стр.")
        self.statusBar().addPermanentWidget(lb)
        self.cur_line = QLabel()
        self.statusBar().addPermanentWidget(self.cur_line)
        lb = QLabel(u'кол.')
        self.statusBar().addPermanentWidget(lb)
        self.cur_col = QLabel()
        self.statusBar().addPermanentWidget(self.cur_col)
        lb = QWidget()
        # lb.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        # lb.setMinimumWidth(100)
        self.statusBar().addPermanentWidget(lb, 1)

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.preview_update)

        wgt = QWidget(self)
        self.setCentralWidget(wgt)

        layout = QBoxLayout(QBoxLayout.LeftToRight, wgt)
        wgt.setLayout(layout)

        wgt = QWidget(self)
        la = QVBoxLayout(wgt)
        self.text_edit = QTextEdit(self)
        self.text_edit.textChanged.connect(self.text_changed)
        self.text_edit.cursorPositionChanged.connect(self.show_pos)
        self.new()
        # layout.addWidget(self.text_edit)
        la.addWidget(self.text_edit)
        self.l_err = QLabel(wgt)
        la.addWidget(self.l_err)
        layout.addWidget(wgt)

        # self.preview = QWidget(self)
        # la = QVBoxLayout(self.preview)
        # self.preview.setLayout(la)
        # sa = QScrollArea(self)
        # sa.setWidgetResizable(True)
        # sa.setWidget(self.preview)
        # layout.addWidget(sa)
        self.preview = ReportPreview(self)
        layout.addWidget(self.preview)

        self.toolbar = QToolBar("Main", self)
        self.toolbar.addAction(icon_new, u"Новый", self.new)
        self.toolbar.addAction(icon_open, u"Открыть", self.open)
        self.toolbar.addAction(icon_floppy, u"Сохранить", self.save)
        self.toolbar.addSeparator()
        self.toolbar.addAction(icon_update, u"Обновить", self.preview_update)
        self.addToolBar(self.toolbar)

        rep = Report()
        print(rep)
        self.text_edit.setPlainText(json.dumps(rep, indent=4))

    def show_pos(self):
        cursor = self.text_edit.textCursor()
        self.cur_col.setText(str(cursor.columnNumber()))
        line_num = 0
        pos = cursor.position()
        lines = self.text_edit.toPlainText().split('\n')
        lines_len = 0
        for line in lines:
            if pos <= lines_len:
                break
            lines_len += len(line) + 1
            line_num += 1
        if line_num > len(lines):
            line_num -= 1
        if cursor.columnNumber() == 0:
            line_num += 1
        self.cur_line.setText(str(line_num))

    def set_err(self, text=''):
        tp, val, tb = exc_info()
        text = text or ("%s: %s" % (str(tp).replace('<class ', '').replace("'>:", ''), val))
        self.l_err.setText('<p style="color: red">%s</p>' % text)
        print("ERROR: %s" % text)

    def new(self):
        try:
            self.text_edit.textChanged.disconnect()
        except:
            self.set_err("disconnect() failed between 'text_changed' and all its connections")
        self.text_edit.clear()
        self.file_name = ''
        # self.setWindowTitle(self.title)
        self.setWindowModified(False)
        self.text_edit.textChanged.connect(self.text_changed)

    def open(self):
        file_name = QFileDialog.getOpenFileName(self, u"Открыть", '', "Файлы шаблонов (*.utpl);;Все файлы (*.*)")
        if file_name:
            try:
                self.text_edit.textChanged.disconnect()
            except:
                self.set_err("disconnect() failed between 'text_changed' and all its connections")
            try:
                self.text_edit.setPlainText(open(file_name[0], 'r').read(-1))
                self.file_name = file_name[0]
                self.setWindowModified(False)
                self.setWindowTitle("%s - %s" % (self.file_name, self.title))
                self.text_edit.textChanged.connect(self.text_changed)
                self.preview_update()
            except:
                self.set_err()

    def save(self):
        if not self.file_name:
            file_name = QFileDialog.getSaveFileName(self, u"Сохранить", '', "Файлы шаблонов (*.utpl);;Все файлы (*.*)")
        else:
            file_name = [self.file_name]
        if file_name[0]:
            try:
                res = open(file_name[0], "w").write(self.text_edit.toPlainText())
                if res:
                    self.file_name = file_name[0]
                    self.setWindowTitle("%s - %s" % (self.file_name, self.title))
                    self.setWindowModified(False)
            except:
                self.set_err()

    def text_changed(self):
        # self.setWindowTitle(self.title + " *")
        self.setWindowModified(True)
        if self.timer.isActive():
            self.timer.stop()
            # self.preview_update()
        self.timer.start(500)

    def preview_update(self):
        self.timer.stop()
        self.l_err.clear()

        try:
            try:
                self.report = json.loads(self.text_edit.toPlainText(), cls=_ReportDecoder)
            except ValueError or TypeError as e:
                # self.set_err(str(e))
                from xml.etree import ElementTree as ET

                self.report = ET.fromstring(self.text_edit.toPlainText())
            if "report" in self.report:
                self.preview.set_report(self.report)
            elif self.report.tag == "template":
                self.preview.set_report(self.report)
                if self.preview.error_string():
                    self.set_err(self.preview.error_string())

        except Exception as e:
            self.set_err()


if __name__ == "__main__":
    from sys import argv, exc_info

    app = QApplication(argv)

    from icons import icon_editor

    app.setWindowIcon(icon_editor)
    wnd = MainWnd()
    app.setActiveWindow(wnd)
    wnd.showMaximized()
    app.exec_()
