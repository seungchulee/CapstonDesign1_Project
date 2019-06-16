
import pymysql
from database import connection

def checkLogin(*data):
    conn = connection.get_connection()

    sql = '''
            select id, password from user_info
            where id = %s and password = %s
          '''
    
    cursor = conn.cursor()
    cursor.execute(sql, data)

    result = cursor.fetchone()
    if result == None:
        user_id = -1
    else:
        user_id = result[0]

    conn.close()

    return user_id

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
def get_mainInfo(user_id):
    conn = connection.get_connection()
    sql = '''
                select time, isPerson from main_send
                where id = %s
          '''

    cursor = conn.cursor()
    cursor.execute(sql, user_id)

    result = cursor.fetchall()

    conn.close()

    return result 
    
