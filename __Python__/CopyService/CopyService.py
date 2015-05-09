import psycopg2
from psycopg2._psycopg import cursor, connection

__author__ = 'Михаил'

#begin function: copyService
def copyService(searchSId, new_SIdx=None, munisipial=False, new_Name="", new_Root=None):

    conn = psycopg2.connect(database="MFCs", user="postgres", password="me2db4con", host="192.168.91.60")
    assert isinstance(conn, connection)
    cur = conn.cursor()

    assert isinstance(cur, cursor)
    assert isinstance(searchSId, int)
    cur.execute("SELECT aname, root, deadline, workdays, srv_name_id, isactive, organ, continue_wo_reqdoc FROM ctrldatesrvs  WHERE id="+searchSId.__str__()+" ORDER BY \"sIdxFloat\"")
    while cur.rownumber < cur.rowcount:
        print(cur.fetchone()[0])
    cur.close()
    conn.close()
#end function: copyService


#begin main
if __name__=="__main__":
    copyService(searchSId=42599, new_SIdx="120Г")