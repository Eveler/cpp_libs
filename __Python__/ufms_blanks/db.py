# -*- coding: utf-8 -*-
from builtins import staticmethod
from datetime import date
import logging
from sys import exc_info
from traceback import print_exc
from sqlalchemy.engine import create_engine
from sqlalchemy.exc import StatementError
from sqlalchemy.ext.declarative.api import declarative_base
from sqlalchemy.orm.session import sessionmaker
from sqlalchemy.sql.ddl import CreateColumn
from sqlalchemy.sql.schema import Column
from sqlalchemy.types import Integer, Text, Date, Boolean

__author__ = 'Savenko'

Base = declarative_base()


class DataType:
    INT = 0
    TEXT = 1
    DATE = 2
    BOOL = 3
    FLOAT = 4
    LIST = 5


class Db():
    def __init__(self, dbstr="sqlite:///ufms.db", echo=False):
        self.version = 2
        metadata = Base.metadata
        engine = create_engine(dbstr, echo=echo)
        metadata.create_all(engine)
        metadata.reflect(bind=engine)
        self.session = sessionmaker(bind=engine)()
        self.humans = metadata.tables["humans"]
        self.lasterror = u''

        self.version_tbl = metadata.tables['version']
        v = self.session.query(self.version_tbl).first()
        version = v.version if v else 0
        if version < self.version:
            try:
                while version < self.version:
                    self.__getattribute__('migrate_%s_%s' % (version, version + 1))()
                    version += 1
                v = Version(version=self.version)
                self.session.connection().execute('DELETE FROM version')
                self.session.add(v)
                self.session.commit()
            except:
                logging.warning("Migration failed.", exc_info=True)

    def fields(self):
        # FIXME: also get fields from db
        return Human.columns()

    def field_type(self, name):
        # FIXME: also get fields types from db
        return Human.data_type(name)

    def is_required(self, name):
        # FIXME: also get fields types from db
        return Human.is_required(name)

    def field_hr_name(self, name):
        # FIXME: also get fields human readable names from db
        return Human.human_readable_name(name)

    def field_input_mask(self, name):
        # FIXME: also get fields human readable names from db
        return Human.input_mask(name)

    def search(self, surname='', middlename='', lastname='', h_id=''):
        if not surname and not middlename and not lastname and not h_id:
            return []
        query = self.session.query(self.humans)
        if surname:
            query = query.filter(self.humans.c.surname.like('%' + surname[0].upper() + surname[1:] + '%'))
        if middlename:
            query = query.filter(self.humans.c.middlename.like('%' + middlename[0].upper() + middlename[1:] + '%'))
        if lastname:
            query = query.filter(self.humans.c.lastname.like('%' + lastname[0].upper() + lastname[1:] + '%'))
        if h_id:
            query = query.filter(self.humans.c.id == h_id)
        return query.all()

    def save(self, **kw):
        if not kw:
            return False

        if 'id' in kw:
            h = self.session.query(Human).filter(self.humans.c.id == kw['id']).one()
            for k in kw:
                if k == 'id':
                    continue
                # print("%s = %s, type = %s" % (k, kw[k], type(kw[k])))
                if isinstance(kw[k], date) and date.min == kw[k]:
                    h.__setattr__(k, None)
                elif isinstance(kw[k], str) and '' == kw[k]:
                    h.__setattr__(k, None)
                else:
                    h.__setattr__(k, kw[k])
        else:
            params = []
            for k in kw:
                params.append("%s = kw['%s']" % (k, k))
            to_eval = "Human(%s)" % ', '.join(params)
            h = eval(to_eval)

        self.session.add(h)
        try:
            self.session.commit()
        except StatementError:
            exc_type, exc_val, exc_tb = exc_info()
            self.lasterror = u'Ошибка сохранения в БД: ' + str(exc_val)
            logging.error("Error saving to DB", exc_info=True)
            print_exc()
            self.session.rollback()
            return False
        return True

    def migrate_0_1(self):
        conn = self.session.connection()
        for column_name in ["birth_country", "birth_region", "birth_rayon", "birth_town", "birth_locality",
                            "citizenship", "stay_region", "stay_rayon", "stay_town", "stay_locality", "stay_street",
                            "stay_house", "stay_housing", "stay_flat", "organ", "organ_cod", "passport_type",
                            "passport_series", "passport_num", "passport_organ", "passport_organ_cod", "out_country",
                            "out_region", "out_rayon", "out_town", "out_locality", "out_street", "out_house",
                            "out_housing", "out_flat", "from_country", "from_region", "from_rayon", "from_town",
                            "from_locality", "from_street", "from_house", "from_housing", "from_flat", "to_street",
                            "to_house", "to_housing", "to_flat", "new_surname", "new_name", "new_lastname", "cause"]:
            conn.execute("ALTER TABLE humans ADD COLUMN %s text" % column_name)
        for column_name in ["live_date", "stay_date", "passport_date", "new_birthday", "prepared", "removal_date"]:
            conn.execute("ALTER TABLE humans ADD COLUMN %s date" % column_name)
        for column_name in ["new_male"]:
            conn.execute("ALTER TABLE humans ADD COLUMN %s bool" % column_name)

    def migrate_1_2(self):
        conn = self.session.connection()
        for column_name in ["legal", "married", "zags", "father_surname", "father_middlename", "father_lastname",
                            "mather_surname", "mather_middlename", "mather_lastname", "live_region", "live_rayon",
                            "live_town", "live_locality", "live_street", "live_house", "live_housing", "live_flat",
                            "to_region", "to_raion", "to_town", "to_locality", "citizenship", "visa_series",
                            "visa_num", "entry_purpose", "profession", "migration_card_series", "migration_card_num"]:
            conn.execute("ALTER TABLE humans ADD COLUMN %s text" % column_name)
        for column_name in ["married_date", "passport_validity", "visa_date", "visa_validity", "entry_date"]:
            conn.execute("ALTER TABLE humans ADD COLUMN %s date" % column_name)
        for column_name in ["visa", "residence"]:
            conn.execute("ALTER TABLE humans ADD COLUMN %s bool" % column_name)


class Version(Base):
    __tablename__ = "version"
    version = Column(Integer, primary_key=True)


class Human(Base):
    __tablename__ = "humans"
    id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    # user_name = Column(String, nullable=False, server_default=text("current_user()"))
    surname = Column(Text, nullable=False)
    middlename = Column(Text, nullable=False)
    lastname = Column(Text)
    birthday = Column(Date)
    male = Column(Boolean)
    birth_country = Column(Text)
    birth_region = Column(Text)
    birth_rayon = Column(Text)
    birth_town = Column(Text)
    birth_locality = Column(Text)
    citizenship = Column(Text)
    live_date = Column(Date)
    stay_date = Column(Date)
    stay_region = Column(Text)
    stay_rayon = Column(Text)
    stay_town = Column(Text)
    stay_locality = Column(Text)
    stay_street = Column(Text)
    stay_house = Column(Text)
    stay_housing = Column(Text)
    stay_flat = Column(Text)
    organ = Column(Text)
    organ_cod = Column(Text)
    passport_type = Column(Text)
    passport_series = Column(Text)
    passport_num = Column(Text)
    passport_date = Column(Date)
    passport_organ = Column(Text)
    passport_organ_cod = Column(Text)
    passport_validity = Column(Date)
    out_country = Column(Text)
    out_region = Column(Text)
    out_rayon = Column(Text)
    out_town = Column(Text)
    out_locality = Column(Text)
    out_street = Column(Text)
    out_house = Column(Text)
    out_housing = Column(Text)
    out_flat = Column(Text)
    from_country = Column(Text)
    from_region = Column(Text)
    from_rayon = Column(Text)
    from_town = Column(Text)
    from_locality = Column(Text)
    from_street = Column(Text)
    from_house = Column(Text)
    from_housing = Column(Text)
    from_flat = Column(Text)
    to_region = Column(Text)
    to_raion = Column(Text)
    to_town = Column(Text)
    to_locality = Column(Text)
    to_street = Column(Text)
    to_house = Column(Text)
    to_housing = Column(Text)
    to_flat = Column(Text)
    new_surname = Column(Text)
    new_name = Column(Text)
    new_lastname = Column(Text)
    new_birthday = Column(Date)
    new_male = Column(Boolean)
    cause = Column(Text)
    prepared = Column(Date)
    removal_date = Column(Date)
    legal = Column(Text)
    married = Column(Text)
    married_date = Column(Date)
    zags = Column(Text)
    father_surname = Column(Text)
    father_middlename = Column(Text)
    father_lastname = Column(Text)
    mather_surname = Column(Text)
    mather_middlename = Column(Text)
    mather_lastname = Column(Text)
    live_region = Column(Text)
    live_rayon = Column(Text)
    live_town = Column(Text)
    live_locality = Column(Text)
    live_street = Column(Text)
    live_house = Column(Text)
    live_housing = Column(Text)
    live_flat = Column(Text)
    residence = Column(Boolean)
    visa = Column(Boolean)
    visa_series = Column(Text)
    visa_num = Column(Text)
    visa_date = Column(Date)
    visa_validity = Column(Date)
    entry_purpose = Column(Text)
    entry_date = Column(Date)
    profession = Column(Text)
    migration_card_series = Column(Text)
    migration_card_num = Column(Text)

    def __repr__(self):
        return u"<%s %s %s %s д.р." % (
            self.surname, self.middlename, self.lastname, date(self.birthday).strftime("%d.%m.%Y"))

    @staticmethod
    def columns():
        return ["surname", "middlename", "lastname", "birthday", "male", "birth_country", "birth_region", "birth_rayon",
                "birth_town", "birth_locality", "citizenship", "live_date", "stay_date", "stay_region", "stay_rayon",
                "stay_town", "stay_locality", "stay_street", "stay_house", "stay_housing", "stay_flat", "organ",
                "organ_cod", "passport_type", "passport_series", "passport_num", "passport_date", "passport_organ",
                "passport_organ_cod", "passport_validity", "out_country", "out_region", "out_rayon", "out_town",
                "out_locality", "out_street", "out_house", "out_housing", "out_flat", "from_country", "from_region",
                "from_rayon", "from_town", "from_locality", "from_street", "from_house", "from_housing", "from_flat",
                "to_region", "to_raion", "to_town", "to_locality", "to_street", "to_house", "to_housing", "to_flat",
                "new_surname", "new_name", "new_lastname", "new_birthday", "new_male", "cause", "prepared",
                "removal_date", "legal", "married", "married_date", "zags", "father_surname", "father_middlename",
                "father_lastname", "mather_surname", "mather_middlename", "mather_lastname", "live_region",
                "live_rayon", "live_town", "live_locality", "live_street", "live_house", "live_housing", "live_flat",
                "visa", "residence", "visa_series", "visa_num", "visa_date", "visa_validity", "entry_purpose",
                "entry_date", "profession", "migration_card_series", "migration_card_num"]

    @staticmethod
    def data_type(col_name):
        if col_name not in Human.columns():
            return None

        if col_name in ("surname", "middlename", "lastname", "birth_country", "birth_region", "birth_rayon",
                        "birth_town", "birth_locality", "citizenship", "stay_region", "stay_rayon", "stay_town",
                        "stay_locality", "stay_street", "stay_house", "stay_housing", "stay_flat", "organ", "organ_cod",
                        "passport_type", "passport_series", "passport_num", "passport_organ", "passport_organ_cod",
                        "out_country", "out_region", "out_rayon", "out_town", "out_locality", "out_street", "out_house",
                        "out_housing", "out_flat", "from_country", "from_region", "from_rayon", "from_town",
                        "from_locality", "from_street", "from_house", "from_housing", "from_flat", "to_region",
                        "to_raion", "to_town", "to_locality", "to_street", "to_house", "to_housing", "to_flat",
                        "new_surname", "new_name", "new_lastname", "cause", "legal", "married", "zags",
                        "father_surname", "father_middlename", "father_lastname", "mather_surname",
                        "mather_middlename", "mather_lastname", "live_region", "live_rayon", "live_town",
                        "live_locality", "live_street", "live_house", "live_housing", "live_flat", "visa_series",
                        "visa_num", "profession", "migration_card_series", "migration_card_num"):
            return DataType.TEXT
        if col_name in ("birthday", "live_date", "stay_date", "passport_date", "new_birthday", "prepared",
                        "removal_date", "married_date", "passport_validity", "visa_date", "visa_validity",
                        "entry_date"):
            return DataType.DATE
        if col_name in ("male", "new_male", "visa", "residence"):
            return DataType.BOOL
        if col_name in ("entry_purpose"):
            return DataType.LIST

    @staticmethod
    def is_required(col_name):
        if col_name not in Human.columns():
            return None

        if col_name in ("surname", "middlename", "birthday"):
            return True

        return False

    @staticmethod
    def human_readable_name(col_name):
        if col_name == "surname":
            return u"Фамилия"
        elif col_name == "middlename":
            return u"Имя"
        elif col_name == "lastname":
            return u"Отчество"
        elif col_name == "birthday":
            return u"Дата рождения"
        elif col_name == "male":
            return u"Пол мужской"
        elif col_name == "birth_country":
            return u"Страна рождения"
        elif col_name == "birth_region":
            return u"Регион рождения"
        elif col_name == "birth_rayon":
            return u"Район рождения"
        elif col_name == "birth_town":
            return u"Город рождения"
        elif col_name == "birth_locality":
            return u"Населённый пункт"
        elif col_name == "citizenship":
            return u"Гражданство/Дата принятия российского гражданства"
        elif col_name == "live_date":
            return u"Дата регистрации с"
        elif col_name == "stay_date":
            return u"Дата пребывания по"
        elif col_name == "stay_region":
            return u"Регион пребывания"
        elif col_name == "stay_rayon":
            return u"Район пребывания"
        elif col_name == "stay_town":
            return u"Город пребывания"
        elif col_name == "stay_locality":
            return u"Населённый пункт пребывания"
        elif col_name == "stay_street":
            return u"Улица пребывания"
        elif col_name == "stay_house":
            return u"Дом пребывания"
        elif col_name == "stay_housing":
            return u"Корпус пребывания"
        elif col_name == "stay_flat":
            return u"Квартира пребывания"
        elif col_name == "organ":
            return u"Орган регистрационного учета"
        elif col_name == "organ_cod":
            return u"Код органа"
        elif col_name == "passport_type":
            return u"Вид документа"
        elif col_name == "passport_series":
            return u"Серия"
        elif col_name == "passport_num":
            return u"№"
        elif col_name == "passport_date":
            return u"Дата выдачи"
        elif col_name == "passport_organ":
            return u"Выдавший орган"
        elif col_name == "passport_organ_cod":
            return u"Код органа"
        elif col_name == "passport_validity":
            return u"Срок действия"
        elif col_name == "out_country":
            return u"Страна выбытия"
        elif col_name == "out_region":
            return u"Регион выбытия"
        elif col_name == "out_rayon":
            return u"Район выбытия"
        elif col_name == "out_town":
            return u"Город выбытия"
        elif col_name == "out_locality":
            return u"Населённый пункт выбытия"
        elif col_name == "out_street":
            return u"Улица выбытия"
        elif col_name == "out_house":
            return u"Дом выбытия"
        elif col_name == "out_housing":
            return u"Корпус выбытия"
        elif col_name == "out_flat":
            return u"Квартира выбытия"
        elif col_name == "from_country":
            return u"Прибыл: страна"
        elif col_name == "from_region":
            return u"Прибыл: регион"
        elif col_name == "from_rayon":
            return u"Прибыл: район"
        elif col_name == "from_town":
            return u"Прибыл: город"
        elif col_name == "from_locality":
            return u"Прибыл: населенный пункт"
        elif col_name == "from_street":
            return u"Прибыл: улица"
        elif col_name == "from_house":
            return u"Прибыл: дом"
        elif col_name == "from_housing":
            return u"Прибыл: корпус"
        elif col_name == "from_flat":
            return u"Прибыл: квартира"
        elif col_name == "to_region":
            return u"Регион обращения"
        elif col_name == "to_raion":
            return u"Район обращения"
        elif col_name == "to_town":
            return u"Город обращения"
        elif col_name == "to_locality":
            return u"Населенный пункт обращения"
        elif col_name == "to_street":
            return u"Переехал/обратился: улица"
        elif col_name == "to_house":
            return u"Прибыл/обратился: дом"
        elif col_name == "to_housing":
            return u"Прибыл/обратился: корпус"
        elif col_name == "to_flat":
            return u"Прибыл/обратился: кваритира"
        elif col_name == "new_surname":
            return u"Новая фамилия"
        elif col_name == "new_name":
            return u"Новое имя"
        elif col_name == "new_lastname":
            return u"Новое отчество"
        elif col_name == "new_birthday":
            return u"Новая дата рождения"
        elif col_name == "new_male":
            return u"Новый пол мужской"
        elif col_name == "cause":
            return u"Причины"
        elif col_name == "prepared":
            return u"Дата составления"
        elif col_name == "removal_date":
            return u"Дата снятия с учёта"
        elif col_name == "legal":
            return u"Законный представитель"
        elif col_name == "married":
            return u'В браке с'
        elif col_name == "married_date":
            return u'Дата регистрации брака'
        elif col_name == "zags":
            return u'Место регистрации брака (ЗАГС)'
        elif col_name == "father_surname":
            return u"Фимилия отца"
        elif col_name == "father_middlename":
            return u"Имя отца"
        elif col_name == "father_lastname":
            return u"Отчество отца"
        elif col_name == "mather_surname":
            return u"Фимилия матери"
        elif col_name == "mather_middlename":
            return u"Имя матери"
        elif col_name == "mather_lastname":
            return u'Отчество матери'
        elif col_name == "live_region":
            return u"Регион проживания"
        elif col_name == "live_rayon":
            return u"Район проживания"
        elif col_name == "live_town":
            return u"Город проживания"
        elif col_name == "live_locality":
            return u"Населённый пункт проживания"
        elif col_name == "live_street":
            return u"Улица проживания"
        elif col_name == "live_house":
            return u"Дом проживания"
        elif col_name == "live_housing":
            return u"Корпус проживания"
        elif col_name == "live_flat":
            return u"Квартира проживания"
        elif col_name == "visa":
            return u"Виза?"
        elif col_name == "residence":
            return u"Вид на жительсто"
        elif col_name == "visa_series":
            return u"Серия"
        elif col_name == "visa_num":
            return u"Номер"
        elif col_name == "visa_date":
            return u"Дата выдачи"
        elif col_name == "visa_validity":
            return u"Действительно до"
        elif col_name == "entry_purpose":
            return u"Цель въезда"
        elif col_name == "entry_date":
            return u"Дата въезда"
        elif col_name == "profession":
            return u"Профессия"
        elif col_name == "migration_card_series":
            return u"Серия миграционной карты"
        elif col_name == "migration_card_num":
            return u"Номер миграционной карты"
        else:
            return col_name

    @staticmethod
    def input_mask(col_name: str):
        """
        Returns column input mask. See QTextEdit.inputMask() in Qt documentation.
        :param col_name:
        :return: str
        """
        return ""

    @staticmethod
    def list_choices(col_name: str):
        if col_name == "entry_purpose":
            return (u"служебная", u"туризм", u"деловая", u"учеба", u"работа", u"частная", u"транзит", u"гуманитарная",
                    u"другая")
        return None

    @staticmethod
    def columns_groups():
        """
        Returns names of colunms interface containers.
        :return:
        """
        return [u'Персона']

    @staticmethod
    def group_columns(group_name):
        """
        Returns columns to place in interface container.
        :param group_name:
        :return:
        """
        if group_name == u'Персона':
            return ["surname", "middlename", "lastname", "birthday", "male"]

        return []
