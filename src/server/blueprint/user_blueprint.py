from flask import Blueprint, render_template, request, redirect, session
from functools import wraps

user_blue = Blueprint('user', __name__)

@user_blue.route('/user_login')
def user_join():
    html = render_template('user/user_login.html')
    return html

