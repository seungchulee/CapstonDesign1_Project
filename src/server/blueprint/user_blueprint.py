from flask import Blueprint, render_template, request, redirect, session
from functools import wraps
from database import user_dao

user_blue = Blueprint('user', __name__)

@user_blue.route('/user_login')
def user_login():
    html = render_template('user/user_login.html')
    return html

@user_blue.route('/user_login_pro', methods=['post'])
def user_login_pro():
    
    user_id = request.values.get('user_id')
    user_pw = request.values.get('user_pw')

    result = user_dao.checkLogin(user_id, user_pw)
    if result == -1:
        return '''
                    <script>
                        alert("login fail")
                        location.href = '/user_login'
                    </script>
               '''
    else:
        session['login'] = 'YES'
        session['user_id'] = result
        return redirect('/')


@user_blue.route('/user_data')
def user_data():
    data_dict = {}
    data_list = []

    user_id = session['user_id']
    data_dict['user_name'] = user_dao.get_name(user_id)[0]
   
    data_list = user_dao.get_mainInfo(user_id)
    html = render_template('user/user_data.html', data_dict = data_dict, data_list = data_list)
    return html
