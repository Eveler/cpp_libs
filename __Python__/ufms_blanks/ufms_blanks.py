#!/bin/env python
# -*- coding: utf-8 -*-
import logging
from sys import argv
# from sys import path
# path.insert(0, "C:\\Python34\\Lib\\site-packages\\PyQt5")
# print(path)
from addr_base.kladr import KLADR
from config import UfmsConfig
from db import DataType, Db
from templates.editor import ReportPreview, ReportDict
from xml.etree import ElementTree as ET
from datetime import date

try:
    from PyQt5.Qt import *
except ImportError:
    # from PyQt4.Qt import *
    pass

__author__ = 'Savenko'


# def copy_img(pixi, img, x_shift=0, y_shift=0):
# assert pixi.format() == QImage.Format_ARGB32, "First arg has wrong QImage format. Must be Format_ARGB32"
# assert img.format() == QImage.Format_ARGB32, "Second arg has wrong QImage format. Must be Format_ARGB32"
#
# for y in range(0, pixi.height(), 1):
# for x in range(0, pixi.width(), 1):
# if x < img.width() and y < img.height() and pixi.pixel(x, y) != QColor(255, 255, 255).rgba():
#                 img.setPixel(x, y, pixi.pixel(x, y))

class HumanEditor(QWidget):
    canceled = pyqtSignal(QWidget)
    closed = pyqtSignal(QWidget)
    need_edit = pyqtSignal(str)

    def __init__(self, db, parent=None, is_preview=False, kw={}):
        super(QWidget, self).__init__(parent)
        c_wgt = QWidget(self)
        if is_preview:
            l = QHBoxLayout()
            l.addWidget(c_wgt)
        else:
            l = QVBoxLayout()
            layout = QHBoxLayout()
            layout.setContentsMargins(2, 2, 2, 2)
            h_wgt = QWidget(self)
            l.addWidget(h_wgt)
            h_wgt.setLayout(layout)
            splitter = QSplitter(h_wgt)
            splitter.setStyleSheet("""
            QSplitter::handle {
                border: 1px black;
                color: black;
            }
            """)
            layout.addWidget(splitter)
            # splitter.addWidget(c_wgt)
            scroll = QScrollArea(self)
            splitter.addWidget(scroll)
            scroll.setWidget(c_wgt)
        self.setLayout(l)
        l.setContentsMargins(2, 2, 2, 2)
        l = QFormLayout(c_wgt)
        l.setContentsMargins(2, 2, 2, 2)
        c_wgt.setLayout(l)

        if is_preview:
            fields = ("surname", "middlename", "lastname", "birthday")
        else:
            fields = db.fields()
        for field in fields:
            if field in db.fields():
                if db.field_type(field) == DataType.BOOL:
                    wgt = QCheckBox(self)
                    wgt.setObjectName(field)
                    wgt.stateChanged.connect(self.changed)
                elif db.field_type(field) == DataType.DATE:
                    wgt = QDateEdit(self)
                    wgt.setSpecialValueText(' . .')
                    wgt.setDate(date.min)
                    wgt.setCalendarPopup(True)
                    wgt.setObjectName(field)
                    wgt.dateChanged.connect(self.changed)
                elif db.field_type(field) in (DataType.FLOAT, DataType.INT):
                    wgt = QDoubleSpinBox(self)
                    wgt.setObjectName(field)
                    wgt.valueChanged.connect(self.changed)
                elif db.field_type(field) == DataType.LIST:
                    wgt = QComboBox(self)
                    wgt.setObjectName(field)
                    wgt.addItems(db.list_choices(field))
                    wgt.valueChanged.connect(self.changed)
                else:  # db.field_type(field) == DataType.TEXT:
                    wgt = QLineEdit(self)
                    wgt.setObjectName(field)
                    wgt.setInputMask(db.field_input_mask(field))
                    if field in ("surname", "middlename", "lastname"):
                        wgt.textChanged.connect(self.to_upper)
                    wgt.textChanged.connect(self.changed)

                if is_preview:
                    wgt.setReadOnly(is_preview)
                l.addRow(
                    db.field_hr_name(field) + ('<span style="color:red">*</span>' if db.is_required(field) else ''),
                    wgt)

        bb = QDialogButtonBox(self)
        if is_preview:
            b = QPushButton(icon_editor, QObject().tr(u"Редактировать"), self)
            b.setObjectName('Editor_caller')
            b.clicked.connect(self.cancel)
            bb.addButton(b, QDialogButtonBox.RejectRole)
        else:
            l.addRow(u'<font size="small">Обязателные поля отмечены <span style="color:red">*</span></font>', QWidget())

            b = QPushButton(icon_save, QObject().tr(u"Сохранить"), self)
            b.clicked.connect(self.save)
            bb.addButton(b, QDialogButtonBox.ApplyRole)
            b = QPushButton(icon_cancel, QObject().tr(u"Отмена"), self)
            b.clicked.connect(self.cancel)
            bb.addButton(b, QDialogButtonBox.RejectRole)
            b = QPushButton(icon_close, QObject().tr(u"Закрыть/Сохранить"), self)
            b.clicked.connect(self.about_to_close)
            bb.addButton(b, QDialogButtonBox.AcceptRole)


            from os import getcwd
            self.report = ET.fromstring(
                open(getcwd()+u"\\templates\\адресный листок убытия xml.utpl").read(-1))
            self.box = QComboBox(self)
            # TODO: fill box from db
            self.box.addItem(u'Адресный листок убытия',
                             getcwd()+u"\\templates\\адресный листок убытия xml.utpl")
            self.box.addItem(u'Адресный листок прибытия',
                             getcwd()+u'\\templates\\адресный листок прибытия xml.utpl')
            self.box.addItem(u'Заявление о снятии с регистрационного учёта',
                             getcwd()+u'\\templates\\заявление о снятии с регистрационного учёта xml.utpl')
            self.box.currentIndexChanged.connect(self.switch_report)
            self.box.setCurrentIndex(0)

            self.timer = QTimer(self)
            self.timer.timeout.connect(self.preview_update)
            self.preview = ReportPreview(self)
            b = QWidget(self)
            b.setLayout(QVBoxLayout())
            b.layout().addWidget(self.box)
            b.layout().addWidget(self.preview)
            # splitter.addWidget(self.preview)
            splitter.addWidget(b)

        self.layout().addWidget(bb)

        self.db = db
        for k in kw:
            if kw[k] is None:
                continue
            if k == 'id':
                self.id = kw[k]
            obj = self.findChild(QCheckBox, k)
            if obj:
                obj.setChecked(kw[k])
            obj = self.findChild(QDateEdit, k)
            if obj:
                obj.setDate(kw[k])
            obj = self.findChild(QDoubleSpinBox, k)
            if obj:
                obj.setValue(kw[k])
            obj = self.findChild(QLineEdit, k)
            if obj:
                obj.setText(kw[k])

        if not is_preview:
            c_wgt.adjustSize()
            scroll.setMinimumWidth(c_wgt.width() + 20)

    def switch_report(self):
        print('*'*80)
        self.report = ET.fromstring(open(self.box.currentData()).read(-1))
        self.preview_update()

    def _data(self):
        params = ReportDict()
        for obj in self.findChildren(QCheckBox):
            params[obj.objectName()] = obj.isChecked()
        for obj in self.findChildren(QDateEdit):
            from datetime import date
            if date(1752, 9, 14) >= date(obj.date().year(), obj.date().month(), obj.date().day()):
                params[obj.objectName()] = None
            else:
                params[obj.objectName()] = date(obj.date().year(), obj.date().month(), obj.date().day())
        for obj in self.findChildren(QDoubleSpinBox):
            params[obj.objectName()] = obj.value()
        for obj in self.findChildren(QLineEdit):
            if "qt_" in obj.objectName():
                continue
            params[obj.objectName()] = obj.text()

        return params

    def to_upper(self, text):
        if not text:
            return
        self.sender().setText(text[0].upper() + text[1:])

    def save(self):
        params = []
        try:
            params.append('id = %s' % self.id)
        except:
            pass
        for obj in self.findChildren(QCheckBox):
            params.append("%s = %s" % (obj.objectName(), obj.isChecked()))
        for obj in self.findChildren(QDateEdit):
            # params.append("%s = '%s'" % (obj.objectName(), obj.date().toString("dd.MM.yyyy")))
            params.append(
                "%s = date(%s, %s, %s)" % (obj.objectName(), obj.date().year(), obj.date().month(), obj.date().day()))
        for obj in self.findChildren(QDoubleSpinBox):
            params.append("%s = '%s'" % (obj.objectName(), obj.value()))
        for obj in self.findChildren(QLineEdit):
            if "qt_" in obj.objectName():
                continue
            params.append("%s = '%s'" % (obj.objectName(), obj.text()))
        to_eval = "self.db.save(%s)" % ', '.join(params)
        # print(to_eval)
        return eval(to_eval)

    def cancel(self):
        if self.sender().objectName() == 'Editor_caller':
            assert self.id, 'id not assigned'
            self.need_edit.emit(str(self.id))
            return
        self.canceled.emit(self)

    def about_to_close(self):
        if self.save():
            self.closed.emit(self)
        else:
            QMessageBox.warning(self, u'Ошибка', self.db.lasterror)

    def preview_update(self):
        self.timer.stop()

        self.preview.set_data(self._data())
        if "report" in self.report:
            self.preview.set_report(self.report)
        elif self.report.tag == "template":
            self.preview.set_report(self.report)
            if self.preview.error_string():
                logging.error(self.preview.error_string())

    def changed(self):
        try:
            if self.timer is None:
                return
        except:
            return
        if self.timer.isActive():
            # self.preview_update()
            self.timer.stop()
            self.timer.start(700)
        else:
            self.timer.start(700)


class MainWnd(QMainWindow):
    def __init__(self, title=''):
        super(QMainWindow, self).__init__()
        if not title:
            title = QObject().tr(u'Печать бланков')
        self.setWindowTitle(title)
        self.setMinimumWidth(640)
        self.setMinimumHeight(480)

        self.config = UfmsConfig()
        # self.kladr = KLADR()

        # центральный виджет содержит 2 блока: блок поиска и скролл для результатов
        # блок поиска состоит из "горизонтального" виджета, на котором "вертикальные" с полями поиска
        self.c_wgt = QWidget(self)
        self.setCentralWidget(self.c_wgt)
        c_layout = QVBoxLayout(self.c_wgt)
        c_layout.setContentsMargins(2, 2, 2, 2)
        self.c_wgt.setLayout(c_layout)

        self.h_wgt = QWidget(self)
        h_layout = QHBoxLayout(self.h_wgt)
        h_layout.setContentsMargins(2, 2, 2, 2)
        self.h_wgt.setLayout(h_layout)
        c_layout.addWidget(self.h_wgt)

        wgt = QWidget(self)
        layout = QVBoxLayout(wgt)
        layout.setContentsMargins(2, 2, 2, 2)
        self.surname = QLineEdit()
        self.surname.setPlaceholderText(QObject().tr(u"Фамилия (начните вводить для поиска)"))
        self.surname.textChanged.connect(self.search)
        layout.addWidget(self.surname)
        h_layout.addWidget(wgt)
        self.surname.setFocus()

        wgt = QWidget(self)
        layout = QVBoxLayout(wgt)
        layout.setContentsMargins(2, 2, 2, 2)
        self.middlename = QLineEdit()
        self.middlename.setPlaceholderText(QObject().tr(u"Имя (начните вводить для поиска)"))
        self.middlename.textChanged.connect(self.search)
        layout.addWidget(self.middlename)
        h_layout.addWidget(wgt)

        wgt = QWidget(self)
        layout = QVBoxLayout(wgt)
        layout.setContentsMargins(2, 2, 2, 2)
        self.lastname = QLineEdit()
        self.lastname.setPlaceholderText(QObject().tr(u"Отчество (начните вводить для поиска)"))
        self.lastname.textChanged.connect(self.search)
        layout.addWidget(self.lastname)
        h_layout.addWidget(wgt)

        self.scroll = QScrollArea(self)
        self.scroll_wgt = QWidget(self.scroll)
        self.scroll_layout = QVBoxLayout(self.scroll_wgt)
        self.scroll_layout.setContentsMargins(2, 2, 2, 2)
        self.scroll_wgt.setLayout(self.scroll_layout)
        self.scroll.setWidget(self.scroll_wgt)
        c_layout.addWidget(self.scroll)

        self.toolbar = QToolBar(QObject().tr(u"Панель инструментов"), self)
        self.action_add = self.toolbar.addAction(icon_add, QObject().tr(u"Новый"), self.add)
        self.addToolBar(self.toolbar)

        self.db = Db("%s:///%s" % (self.config.options["db"]["type"], self.config.options["db"]["db"]), True)

    def search(self):
        # for obj in self.scroll_layout.parent().findChildren(HumanEditor):
        #     self.scroll_layout.removeWidget(obj)
        #     obj.deleteLater()
        for he_obj in self.scroll_wgt.findChildren(HumanEditor):
            self.scroll_layout.removeWidget(he_obj)
            he_obj.deleteLater()
        for human in self.db.search(self.surname.text(), self.middlename.text(), self.lastname.text()):
            params = {}
            for field in human.keys():
                params[field] = human.__getattribute__(field)
            he = HumanEditor(self.db, self.scroll_wgt, is_preview=True, kw=params)
            he.need_edit.connect(self.edit)
            self.scroll_layout.addWidget(he)
            he.show()
            self.scroll_wgt.adjustSize()

    def add(self):
        params = {}
        if self.surname.text():
            params['surname'] = self.surname.text()
        if self.middlename.text():
            params['middlename'] = self.middlename.text()
        if self.lastname.text():
            params['lastname'] = self.lastname.text()
        he = HumanEditor(self.db, self, kw=params)
        he.closed.connect(self.remove_he)
        he.canceled.connect(self.remove_he)

        self.scroll.hide()
        for he_obj in self.scroll_wgt.findChildren(HumanEditor):
            self.scroll_layout.removeWidget(he_obj)
            he_obj.deleteLater()

        for obj in (self.surname, self.middlename, self.lastname):
            obj.setText('')
        self.h_wgt.hide()
        self.action_add.setEnabled(False)
        self.c_wgt.layout().addWidget(he)
        surname = he.findChild(QLineEdit, 'surname')
        if surname:
            surname.setFocus()

    def edit(self, h_id):
        for human in self.db.search(h_id=h_id):
            params = {}
            for field in human.keys():
                params[field] = human.__getattribute__(field)
            he = HumanEditor(self.db, self, kw=params)
            he.closed.connect(self.remove_he)
            he.canceled.connect(self.remove_he)

            self.scroll.hide()
            for he_obj in self.scroll_wgt.findChildren(HumanEditor):
                self.scroll_layout.removeWidget(he_obj)
                he_obj.deleteLater()

            for obj in (self.surname, self.middlename, self.lastname):
                obj.setText('')
            self.h_wgt.hide()
            self.action_add.setEnabled(False)
            self.c_wgt.layout().addWidget(he)
            surname = he.findChild(QLineEdit, 'surname')
            if surname:
                surname.setFocus()

    def remove_he(self, obj):
        self.c_wgt.layout().removeWidget(obj)
        obj.deleteLater()

        self.h_wgt.show()
        self.scroll.show()
        self.action_add.setEnabled(True)
        self.surname.setFocus()

# dispaly_dpi = 96
#
# reportlab.rl_settings.TTFSearchPath = "c:/windows/fonts"
# pdfmetrics.registerFont(TTFont("Arial", "arial.ttf"))
# pdfmetrics.registerFont(TTFont("Times", "times.ttf"))
# styles = getSampleStyleSheet()
# # doc = SimpleDocTemplate("test.pdf")
# c = Canvas("test.pdf", A4, pageCompression=1)
# w, h = A4
# d = shapes.Drawing(w, h)
#
# c.drawImage("templates/ScanImage001bw.png", 0, 0 + h - h * dispaly_dpi / 600, w * dispaly_dpi / 600,
#             h * dispaly_dpi / 600,
#             preserveAspectRatio=True)
#
# s = shapes.Image(0, int(0 + h - h * dispaly_dpi / 600), int(w * dispaly_dpi / 600), int(h * dispaly_dpi / 600),
#                  "templates/ScanImage001bw.png")
# d.add(s)
#
# story = []
# # story.append(platypus.Image("templates/ScanImage001bw.png", width=10 * cm, height=10 * cm))
# p = platypus.Paragraph('<font name="Times" size=18>' + u'Текст ' + '</font>', styles["Normal"])
# # story.append(p)
#
# s = shapes.String(4 * cm, 22 * cm, u'Текст')
# s.fontName = "Times"
# s.fontSize = 18
# d.add(s)
#
# platypus.Frame(0, 0, A4[0], A4[1]).addFromList(story, c)
# f = platypus.Frame(4.6 * cm, 17.3 * cm, 2 * cm, 1 * cm, showBoundary=2)
# f.addFromList([p], c)
#
# # doc.build(story)
# c.save()
#
# img = renderPM.drawToString(d, 'PNG', dispaly_dpi)
# # img = d.asString('png')

if __name__ == "__main__":
    # QApplication.addLibraryPath("C:\\Python34\\Lib\\site-packages\\PyQt5")
    app = QApplication(argv)
    app.setApplicationName(u'Бланки')
    # app.setWindowIcon(QIcon("Copy v2_256x256.png"))
    from icons import icon_app, icon_add, icon_save, icon_cancel, icon_close, icon_editor

    app.setWindowIcon(icon_app)

    # pix = QPixmap()
    # pix.loadFromData(img)

    # base = QImage(int(21 * 2.5 * dispaly_dpi), int(29 * 2.5 * dispaly_dpi), QImage.Format_ARGB32)
    # print("%sx%s, %s" % (base.width(), base.height(), 29 * 2.5 * dispaly_dpi))
    # base.fill(QColor(255, 255, 255))

    # img = QImage("templates/ScanImage001bw.png").convertToFormat(5)
    # img = img.scaledToHeight(img.width() * dispaly_dpi / 600)
    #
    # pe = img.paintEngine()
    # pe.
    # copy_img(img, base)
    # img = base

    # pixi = pix.toImage().convertToFormat(5).scaledToHeight(img.height())
    # print("img: %sx%s, pixi: %sx%s" % (img.width(), img.height(), pixi.width(), pixi.height()))
    # copy_img(pixi, img)

    # wgt = QLabel()
    # wgt.setScaledContents(True)
    # wgt.setPixmap(pix)
    # wgt.setPixmap(pix.fromImage(img))

    # sa = QScrollArea()
    # sa.setWidget(wgt)

    wnd = MainWnd(app.applicationName())
    # wnd.setCentralWidget(sa)
    wnd.show()

    # from templates import editor
    # ed = editor.MainWnd()
    # ed.setWindowModality(2)
    # ed.showMaximized()

    app.setActiveWindow(wnd)
    app.exec_()
