# -*- cooding: utf-8 -*-
from sqlalchemy.engine import create_engine
from sqlalchemy.schema import MetaData

from declarlocker.objects import Base


__author__ = 'mike'

metadata = MetaData()
# engine = create_engine('sqlite:///:memory:', echo=True)
engine = create_engine('sqlite:///:memory:')
Base.metadata.create_all(engine)
from sqlalchemy.orm import sessionmaker

Session = sessionmaker(bind=engine)
session = Session()
