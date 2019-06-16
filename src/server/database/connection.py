import pymysql

def get_connection():
    conn = pymysql.Connect(host='18.223.29.244', user='root',
                                password='vlfflq3621', db='energy_saver', charset='utf8')
    return conn
