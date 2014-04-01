# -*- coding: utf-8 -*-
import datetime

from sqlalchemy.engine import create_engine
try:
    from sqlalchemy.ext.declarative.api import declarative_base
except ImportError:
    from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.schema import MetaData, Column
from sqlalchemy.sql.expression import text
from sqlalchemy.types import Integer, String, TIMESTAMP


__author__ = 'mike'

Base = declarative_base()


class DeclarLock(Base):
    """
    Manage info about declars locks.
    Mapped to sql table declarlocks
    """

    __tablename__ = "declarlocks"
    id = Column(Integer, primary_key=True, autoincrement=True)
    table_name = Column(String, nullable=False)
    table_id = Column(Integer, nullable=False)
    # user_name = Column(String, nullable=False, server_default=text("current_user()"))
    user_name = Column(String, nullable=False)
    priority = Column(Integer, server_default=text("999"))
    # placed = Column(TIMESTAMP, server_default=text("now()"))
    placed = Column(TIMESTAMP)

    def __init__(self, table_id, table_name="declars", user="current_user", priority="999",
                 placed=datetime.datetime.now()):
        super(DeclarLock, self).__init__()
        self.table_name = table_name
        self.table_id = table_id
        self.user_name = user
        self.priority = priority
        self.placed = placed

    def __repr__(self):
        return "<DeclarLock #%s on %s(%s) placed by %s at %s, priority = %s>" % \
               (self.id, self.table_name, self.table_id, self.user_name, self.placed, self.priority)


metadata = MetaData()
# engine = create_engine('sqlite:///:memory:', echo=True)
engine = create_engine('sqlite:///:memory:')
Base.metadata.create_all(engine)
from sqlalchemy.orm import sessionmaker

Session = sessionmaker(bind=engine)
session = Session()
