# -*- coding: utf-8 -*-
from sqlalchemy.engine import create_engine
from sqlalchemy.ext.declarative.api import declarative_base
from sqlalchemy.schema import MetaData, Column
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
    user_name = Column(String, nullable=False, server_default="current_user()")
    priority = Column(Integer, server_default="999")
    placed = Column(TIMESTAMP, server_default="now()")

    def __init__(self, table_id, table_name="declars", priority="999"):
        super(DeclarLock, self).__init__()
        self.table_name = table_name
        self.table_id = table_id
        self.priority = priority

    def __repr__(self):
        return "<DeclarLock #%s on %s(%s) placed by %s at %s, priority = %s>" % \
               (self.id, self.table_name, self.table_id, self.user_name, self.placed, self.priority)


metadata = MetaData()
engine = create_engine('sqlite:///:memory:', echo=True)
Base.metadata.create_all(engine)
from sqlalchemy.orm import sessionmaker

Session = sessionmaker(bind=engine)
