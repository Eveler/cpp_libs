# -*- coding: utf-8 -*-
import logging
from uuid import UUID, uuid4

from sqlalchemy.engine import create_engine
from sqlalchemy.schema import MetaData
from twisted.python import log

from declarlocker.objects import Base, DeclarLock


__author__ = 'Mike'


class LockManager:
    """
    Manage DeclarLock instances
    """
    clients = []
    registered = []

    def __init__(self):
        pass

    def register(self, obj):
        uid = uuid4()
        obj.set_uid(uid.__str__())
        self.registered.append(uid.__str__())
        logging.debug("Registered client uid = %s", uid)
        return uid.__str__()

    def is_registered(self, uid):
        return uid in self.registered

    def unregister(self, uid):
        c = []
        for l, o in self.clients:
            if o.uid == uid:
                logging.info("Deleting lock %s.", l)
                c.append(o)
                session.delete(l)
                session.commit()
                self.clients.remove([l, o])
        for o in c:
            o.set_uid(None)
        self.registered.remove(uid)


    def is_locked_with_high_priority(self, table_id, table_name, priority):
        locks = session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
            .filter(DeclarLock.table_name == table_name).filter(DeclarLock.priority < priority).all()

        for instance in locks:
            logging.debug("Found %s", instance)

        return len(locks) > 0


    def set_lock(self, obj, table_id, table_name, user, priority):
        """
        Try to set lock up.
        If there is lock with lower priority, notify that clients, they need to unlock
        :rtype : bool
        """
        logging.debug("Try to set lock on %s(%s), prority = %s", table_name, table_id, priority)

        locks = session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
            .filter(DeclarLock.table_name == table_name).filter(DeclarLock.priority <= priority).all()

        for instance in locks:
            logging.debug("Found %s", instance)

        if len(locks) > 0:
            return False

        for instance in session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
                .filter(DeclarLock.table_name == table_name).filter(DeclarLock.priority > priority).all():
            for l, o in self.clients:
                if l == instance:
                    logging.info("Notifying client %s to unlock %s.", o, instance)
                    o.notify({"table_name": table_name, "table_id": table_id, "user": user})

        lock = DeclarLock(table_id, table_name, user, priority)
        session.add(lock)
        session.commit()
        self.clients.append([lock, obj])
        logging.info("Added %s", lock)
        return True

    def locked_by(self, table_id, table_name):
        user_name = session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
            .filter(DeclarLock.table_name == table_name).first().user_name
        logging.debug("locked_by = %s", user_name)
        return user_name

    def unlock(self, table_id, table_name):
        """
        Delete lock
        """
        for instance in session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
                .filter(DeclarLock.table_name == table_name).all():
            for l, o in self.clients:
                if l == instance:
                    logging.info("Deleting lock %s.", instance)
                    session.delete(instance)
                    session.commit()
                    self.clients.remove([l, o])
                    o.notify(False)


metadata = MetaData()
# engine = create_engine('sqlite:///:memory:', echo=True)
engine = create_engine('sqlite:///:memory:', echo=(logging.root.level == logging.DEBUG))
Base.metadata.create_all(engine)
from sqlalchemy.orm import sessionmaker

Session = sessionmaker(bind=engine)
session = Session()

lockmanager = LockManager()
