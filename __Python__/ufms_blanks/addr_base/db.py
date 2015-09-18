# -*- coding: utf-8 -*-
from datetime import date

from sqlalchemy.engine import create_engine
from sqlalchemy.ext.declarative.api import declarative_base
from sqlalchemy.orm.session import sessionmaker
from sqlalchemy.sql.schema import Column, ForeignKey
from sqlalchemy.types import Integer, Text, Date
from traceback import print_exc


__author__ = 'Savenko'

Base = declarative_base()


class AddrDB():
    def __init__(self, dbstr="sqlite:///addr.db", echo=False):
        metadata = Base.metadata
        engine = create_engine(dbstr, echo=echo)
        metadata.reflect(bind=engine)
        metadata.create_all(engine)
        self.session = sessionmaker(bind=engine)()
        # self.ver_date = VersionDate()
        self.ver_date = metadata.tables["ver_date"]
        # self.abbreviation = Abbreviation()
        self.abbreviation = metadata.tables["abbreviations"]
        # self.subject = Subject()
        self.subject = metadata.tables["subjects"]
        # self.region = Region()
        self.region = metadata.tables["regions"]
        # self.raion = Raion()
        self.raion = metadata.tables["raions"]
        # self.town = Town()
        self.town = metadata.tables["towns"]
        # self.locality = Locality()
        self.locality = metadata.tables["localities"]
        # self.street = Street()
        self.street = metadata.tables["streets"]
        # self.address = Address()
        self.address = metadata.tables["address"]
        self.tmp_addr = metadata.tables["tmp_addr"]

    def commit(self):
        self.session.commit()

    def clear(self):
        for tbl in (self.tmp_addr, self.address, self.street, self.locality, self.town, self.raion, self.region,
                    self.subject, self.abbreviation):
            try:
                self.session.query(tbl).delete()
            except:
                try:
                    self.session.query(tbl).delete('fetch')
                except:
                    print_exc()
        self.session.commit()

    def query_street(self, value):
        return self.session.query(self.street.c.name, self.abbreviation.c.short_name).filter(
            self.street.c.name.like(value+"%")).all()

    def query_locality(self, value):
        return self.session.query(self.locality.c.name, self.abbreviation.c.short_name).filter(
            self.locality.c.name.like(value+"%")).all()

    def query_town(self, value):
        return self.session.query(self.town.c.name, self.abbreviation.c.short_name).filter(
            self.town.c.name.like(value+"%")).all()

    def query_raion(self, value, subject=''):
        return self.session.query(self.raion.c.name, self.abbreviation.c.short_name).filter(
            self.raion.c.name.like(value+"%")).all()

    def query_region(self, value, subject=''):
        return self.session.query(self.region.c.name, self.abbreviation.c.short_name).filter(
            self.region.c.name.like(value+"%")).all()

    def query_subject(self, value):
        return self.session.query(self.subject.c.name, self.abbreviation.c.short_name).filter(
            self.subject.c.name.like(value+"%")).all()

    def get_version(self):
        res = self.session.query(self.ver_date.c.ver_date).first()
        if res is None:
            return date.min
        return res

    def add_abbreviation(self, short_name, long_name):
        abbrev = Abbreviation(long_name=long_name, short_name=short_name)
        self.session.add(abbrev)


class VersionDate(Base):
    __tablename__ = "ver_date"
    ver_date = Column(Date, primary_key=True)


class Abbreviation(Base):
    __tablename__ = "abbreviations"
    id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    long_name = Column(Text, nullable=False)
    short_name = Column(Text, nullable=False, index=True)


class Subject(Base):
    __tablename__ = "subjects"
    id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    name = Column(Text, index=True, nullable=False)
    index = Column(Text, index=True)
    abbrev_id = Column(Integer, ForeignKey('abbreviations.id'))


class Region(Base):
    __tablename__ = "regions"
    id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    name = Column(Text, index=True, nullable=False)
    index = Column(Text, index=True)
    abbrev_id = Column(Integer, ForeignKey('abbreviations.id'))


class Raion(Base):
    __tablename__ = "raions"
    id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    name = Column(Text, index=True, nullable=False)
    index = Column(Text, index=True)
    abbrev_id = Column(Integer, ForeignKey('abbreviations.id'))


class Town(Base):
    __tablename__ = "towns"
    id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    name = Column(Text, index=True, nullable=False)
    index = Column(Text, index=True)
    abbrev_id = Column(Integer, ForeignKey('abbreviations.id'))


class Locality(Base):
    __tablename__ = "localities"
    id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    name = Column(Text, index=True, nullable=False)
    index = Column(Text, index=True)
    abbrev_id = Column(Integer, ForeignKey('abbreviations.id'))


class Street(Base):
    __tablename__ = "streets"
    id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    name = Column(Text, index=True, nullable=False)
    index = Column(Text, index=True)
    abbrev_id = Column(Integer, ForeignKey('abbreviations.id'))


class Address(Base):
    __tablename__ = "address"
    id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    index = Column(Text, index=True)
    subject_id = Column(Integer, ForeignKey('subjects.id'), nullable=False)
    region_id = Column(Integer, ForeignKey('regions.id'))
    town_id = Column(Integer, ForeignKey('towns.id'))
    locality_id = Column(Integer, ForeignKey('localities.id'))
    street_id = Column(Integer, ForeignKey('streets.id'))
    house = Column(Text)
    housing = Column(Text)
    flat = Column(Integer)


class TmpAddress(Base):
    __tablename__ = "tmp_addr"
    id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    subject_id = Column(Integer, nullable=False)
    region_id = Column(Integer)
    town_id = Column(Integer)
    locality_id = Column(Integer)
    street_id = Column(Integer)
