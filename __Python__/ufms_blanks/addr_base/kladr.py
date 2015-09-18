# -*- coding: utf-8 -*-
from datetime import date

from dbf.ver_33 import Table, DbfStatus

from addr_base.db import AddrDB


__author__ = 'Savenko'

from addr_base.net import load


class KLADR():
    def __init__(self, auto_update=True):
        self.address = AddrDB(echo=True)

        if auto_update:
            if self.is_update():
                self.update()

    def is_update(self):
        ver_date = load("http://fias.nalog.ru/Public/Downloads/Actual/VerDate.txt")
        day, month, year = ver_date.split(b'.')
        return date(int(year), int(month), int(day)) > self.address.get_version()

    def update(self):
        import tempfile

        tmpdir = tempfile.mkdtemp()

        # base = load("http://fias.nalog.ru/Public/Downloads/Actual/BASE.7z", tmpdir+"/BASE.7z")

        from subprocess import call

        call("addr_base/7z/7z.exe e -o%s %s" % (tmpdir, "BASE.7z"))
        self.address.clear()

        abbrev = Table(tmpdir + "/SOCRBASE.DBF", codepage='cp866')
        abbrev.open(DbfStatus.READ_ONLY)
        for record in abbrev:
            scname = record.scname.strip()
            socrname = record.socrname.strip()
            self.address.add_abbreviation(scname, socrname)
        self.address.commit()

        kladr = Table(tmpdir + "/KLADR.DBF", codepage='cp866')
        kladr.open(DbfStatus.READ_ONLY)
        print(kladr)
        # Структура кодового обозначения в блоке "Код":
        # СС РРР ГГГ ППП АА, где
        # СС – код субъекта Российской Федерации (региона), коды регионов представлены в Приложении 2 к Описанию
        # классификатора адресов Российской Федерации (КЛАДР);
        # РРР – код района;
        # ГГГ – код города;
        # ППП – код населенного пункта,
        # АА – признак актуальности адресного объекта.
        # Признак актуальности может принимать следующие значения:
        # “00” – актуальный объект (его наименование, подчиненность соответствуют состоянию на данный
        # момент адресного пространства).
        #             “01”-“50” – объект был переименован, в данной записи приведено одно из прежних его наименований
        #   (актуальный адресный объект присутствует в базе данных с тем же кодом, но с признаком актуальности “00”;
        #             “51” –  объект был переподчинен или влился в состав другого объекта (актуальный адресный объект
        #   определяется по базе Altnames.dbf);
        #             “52”-“98” – резервные значения признака актуальности;
        #             ”99” – адресный объект не существует, т.е. нет соответствующего ему актуального адресного объекта.
        record = kladr[1]
        code_subject, code_region = record.code[:2], record.code[2:5]
        code_town, code_locality, code_actual = record.code[5:8], record.code[8:11], record.code[11:13]
        print(record)
        print(code_subject, code_region, code_town, code_locality, code_actual)
        #         Блок "Статус объекта" содержит значение признака (“признак центра”), которое определяет, является ли
        #   данный адресный объект центром административно - территориального образования: столицей республики, центром
        #   края, области, района и т.п. Длина – 1 разряд. Данный блок может содержать следующие значения:
        # 0 - объект не является центром административно-территориального образования;
        # 1 – объект является центром района;
        # 2 – объект является центром (столицей) региона;
        # 3 – объект является одновременно и центром района и центром региона;
        # 4 – центральный район, т.е. район, в котором находится центр региона (только для объектов 2-го уровня).
        # Блок "Статус объекта" предназначен для правильного формирования почтового адреса с использованием базы данных
        #   КЛАДР: если значением этого поля является “1”, то в адресе указываются регион и населенный пункт (район не
        #   указывается); если – “2” или “3”, то в адресе указывается только центр региона (регион и район не
        #   указываются).
        status = record.status
        name = record.name.strip()
        socr = record.socr.strip()
        index = record.index.strip()
        print(status, name, socr, index)

        # self.kladr_name_idx = self.kladr.create_index(lambda rec: rec.name)
        # first = self.kladr_name_idx.search(match=('Приморский',), partial=True)
        # print(first)
        # for record in first:
        # print(record)

        street = Table(tmpdir + "/STREET.DBF", codepage='cp866')
        street.open(DbfStatus.READ_ONLY)
        print(street)
        # Структура кодового обозначения в блоке "Код":
        # СС РРР ГГГ ППП УУУУ ДДДД, где
        # СС – код субъекта Российской Федерации (региона), коды регионов представлены в Приложении 2 к Описанию
        #   классификатора адресов Российской Федерации (КЛАДР);
        # РРР – код района;
        # ГГГ – код города;
        # ППП – код населенного пункта;
        # УУУУ – код улицы (если адрес не содержит наименования улицы, т.е. дома привязаны непосредственно к городу или
        #   населенному пункту, то код улицы будет содержать нули – 0000);
        # ДДДД – порядковый номер позиции классификатора с обозначениями домов.

        # Структура кодового обозначения в блоке "Код":
        # СС РРР ГГГ ППП УУУУ ДДДД КККК, где
        # СС – код субъекта Российской Федерации (региона), коды регионов представлены в Приложении 2 к Описанию
        #   классификатора адресов Российской Федерации (КЛАДР);
        # РРР – код района;
        # ГГГ – код города;
        # ППП – код населенного пункта;
        # УУУУ – код улицы;
        # ДДДД – порядковый номер позиции классификатора с обозначениями домов;
        # КККК – порядковый номер позиции классификатора с обозначениями квартир.
        record = street[1]
        code_subject, code_region = record.code[:2], record.code[2:5]
        code_town, code_locality, code_street = record.code[5:8], record.code[8:11], record.code[11:15]
        print(record)
        print(code_subject, code_region, code_town, code_locality, code_street)
        name = record.name.strip()
        socr = record.socr.strip()
        index = record.index.strip()
        print(name, socr, index)

        for res in self.address.query_subject(u'Примор'):
            print(res)

        abbrev.close()
        kladr.close()
        street.close()
        from shutil import rmtree

        rmtree(tmpdir, ignore_errors=True)
