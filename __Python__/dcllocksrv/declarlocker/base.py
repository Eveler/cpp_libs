# -*- coding: utf-8 -*-
import logging
from uuid import uuid4

from sqlalchemy.engine import create_engine

from declarlocker.objects import Base, DeclarLock


__author__ = 'Mike'
# session = None


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
        logging.info("Registered client uid = %s, addr = %s", uid, obj.host)
        return uid.__str__()

    def is_registered(self, uid):
        return uid in self.registered

    def unregister(self, uid):
        c = []
        for l, o in self.clients:
            if o.uid == uid:
                logging.info("Deleting lock %s. Client addr: %s", l, o.host)
                c.append(o)
                self.session.delete(l)
                self.session.commit()
                self.clients.remove([l, o])
        for o in c:
            o.set_uid(None)
        self.registered.remove(uid)


    def is_locked_with_high_priority(self, table_id, table_name, priority):
        locks = self.session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
            .filter(DeclarLock.table_name == table_name).filter(DeclarLock.priority > priority).all()

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

        locks = self.session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
            .filter(DeclarLock.table_name == table_name).filter(DeclarLock.priority >= priority).all()

        for instance in locks:
            logging.debug("Found %s", instance)

        if len(locks) > 0:
            return False

        for instance in self.session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
                .filter(DeclarLock.table_name == table_name).filter(DeclarLock.priority < priority).all():
            for l, o in self.clients:
                if l == instance:
                    logging.info("Notifying client %s (addr: %s) to unlock %s.", o, o.host, instance)
                    o.notify({"table_name": table_name, "table_id": table_id, "user": user})

        lock = DeclarLock(table_id, table_name, user, priority)
        self.session.add(lock)
        self.session.commit()
        self.clients.append([lock, obj])
        logging.info("Added %s. Client addr: %s", lock, obj.host)
        return True

    def locked_by(self, table_id, table_name):
        user_name = self.session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
            .filter(DeclarLock.table_name == table_name).first().user_name
        logging.debug("locked_by = %s", user_name)
        return user_name

    def unlock(self, table_id, table_name, priority):
        """
        Delete lock
        """
        for instance in self.session.query(DeclarLock).filter(DeclarLock.table_id == table_id) \
                .filter(DeclarLock.table_name == table_name) \
                .filter(DeclarLock.priority == priority).all():
            for l, o in self.clients:
                if l == instance:
                    logging.info("Deleting lock %s. Client addr: %s", instance, o.host)
                    self.session.delete(instance)
                    self.session.commit()
                    self.clients.remove([l, o])
                    o.notify(False)

                # metadata = MetaData()
                # engine = create_engine('sqlite:///:memory:', echo=True)
                # engine = create_engine('sqlite:///:memory:', echo=(logging.root.level == logging.DEBUG))

    def connect_db(self, dbstr):
        engine = create_engine(dbstr, echo=(logging.root.level == logging.DEBUG))
        Base.metadata.create_all(engine)

        from sqlalchemy.orm import sessionmaker

        Session = sessionmaker(bind=engine)
        self.session = Session()


lockmanager = LockManager()
