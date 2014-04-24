# -*- coding: utf-8 -*-
import logging

from sqlalchemy.engine import create_engine
from sqlalchemy.schema import MetaData

from declarlocker.objects import Base, DeclarLock


__author__ = 'Mike'


class LockManager:
    """
    Manage DeclarLock instances
    """

    def __init__(self):
        pass

    def set_lock(self, obj, table_id, table_name, user, priority):
        """
        Try to set lock up
        :rtype : bool
        """
        locks = session.query(DeclarLock).filter(DeclarLock.table_id == table_id)\
            .filter(DeclarLock.priority <= priority).all()

        for instance in locks:
            print("Found %s" % instance)

        if len(locks) > 0:
            return False

        lock = DeclarLock(table_id, table_name, user, priority)
        session.add(lock)
        session.commit()
        logging.info("Added %s" % lock)
        return True


metadata = MetaData()
# engine = create_engine('sqlite:///:memory:', echo=True)
engine = create_engine('sqlite:///:memory:')
Base.metadata.create_all(engine)
from sqlalchemy.orm import sessionmaker

Session = sessionmaker(bind=engine)
session = Session()

lockmanager = LockManager()
