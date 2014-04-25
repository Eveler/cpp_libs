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
    clients = []

    def __init__(self):
        pass

    def set_lock(self, obj, table_id, table_name, user, priority):
        """
        Try to set lock up.
        If there is lock with lower priority, notify that clients, they need to unlock
        :rtype : bool
        """
        locks = session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
            .filter(DeclarLock.priority <= priority).all()

        for instance in locks:
            logging.debug("Found %s" % instance)

        if len(locks) > 0:
            return False

        for instance in session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
                .filter(DeclarLock.priority > priority).all():
            for l, o in self.clients[instance.user_name]:
                if l == instance:
                    logging.debug("Notifying client %s to unlock %s. Deleting that lock" % (o, instance))
                    o.notify(instance.table_id)
                    session.delete(instance)
                    del instance

        lock = DeclarLock(table_id, table_name, user, priority)
        session.add(lock)
        session.commit()
        self.clients.append([lock, obj])
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
