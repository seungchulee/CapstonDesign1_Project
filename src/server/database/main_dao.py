
import pymysql
from database import connection

def mainSend(*data):
    conn = connection.get_connection()

    sql = '''
            insert into main_send
            (id, time, isPerson, people)
            values (%s, %s, %s, %s)
          '''
    cursor = conn.cursor()
    cursor.execute(sql, data)

    conn.commit()
    conn.close()
