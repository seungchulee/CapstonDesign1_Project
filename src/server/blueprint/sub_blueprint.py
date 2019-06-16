from flask import Blueprint, render_template, request, redirect, session
from functools import wraps
from database import sub_dao
from datetime import datetime, timedelta

sub_blue = Blueprint('sub', __name__)

@sub_blue.route('/sub/send', methods=['get'])
def sub_send():
    user_id = request.args.get('id')
    arduino_sub_num = request.args.get('arduino_sub_num')
    power = request.args.get('power') 
    td = timedelta(hours = 9)
        
    sub_dao.subSend(user_id, arduino_sub_num, datetime.now() + td,  power)
    return '1'
@sub_blue.route('/sub/response', methods=['get'])
def sub_response():
    result = 'person='
    user_id = request.args.get('id')

    data = sub_dao.subResponse(user_id)

    result = result + str(data[0])
    print(result)
    return result


@sub_blue.route('/user_graph')
def user_graph():
    data_dict={}
    data_list=[]
    data_year=[]
    data_month=[]
    data_day=[]
    data_hour=[]
    data_min=[]

    user_id = session['user_id']
    data_dict['user_name'] = sub_dao.get_name(user_id)[0]

    data_list = sub_dao.get_subInfo(user_id)
    data_len = len(data_list)
    for idx in data_list:
        str1=idx[0].strftime("%Y-%m-%d-%H-%M")
        year,month,day,hour,minute=str1.split("-")
        data_year.append(year)
        data_month.append(month)
        data_day.append(day)
        data_hour.append(hour)
        data_min.append(minute)
    html = render_template('user/user_graph.html', data_len=data_len, data_dict = data_dict, data_list = data_list, data_year = data_year, data_month = data_month, data_day = data_day, data_hour = data_hour, data_min = data_min)
    return html
