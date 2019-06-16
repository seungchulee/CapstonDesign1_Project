
import pymysql
from database import connection

def subSend(*data):
    conn = connection.get_connection()

    sql = '''
            insert into sub_send
            (id, arduino_sub_num, time, power)
            values (%s, %s, %s, %s)
          '''
    cursor = conn.cursor()
    cursor.execute(sql, data)

    conn.commit()
    conn.close()
def subResponse(user_id):

    conn = connection.get_connection()

    sql = '''
            select isPerson from main_send
            where id = %s order by time desc limit 1
          '''
    cursor = conn.cursor()
    cursor.execute(sql, user_id)

    result = cursor.fetchone()

    conn.close()

    return result

def get_name(user_id):
    conn = connection.get_connection()
    sql = '''
                select name from user_info
                where id = %s
          '''
    cursor = conn.cursor()
    cursor.execute(sql, user_id)

    result = cursor.fetchone()

    conn.close()

    return result

def get_subInfo(user_id):
    conn = connection.get_connection()
    sql = '''
                select time, power from sub_send
                where id = %s
          '''

    cursor = conn.cursor()
    cursor.execute(sql, user_id)

    result = cursor.fetchall()

    conn.close()

    return result 

