from flask import Blueprint, render_template, request, redirect, session
from functools import wraps
from database import main_dao
from datetime import datetime, timedelta
main_blue = Blueprint('main', __name__)

@main_blue.route('/main/send', methods = ['get'])
def main_send():
    isPerson = request.args.get('isPerson')
    user_id = request.args.get('id')
    people = request.args.get('people')

    td = timedelta(hours = 9)
        
    main_dao.mainSend(user_id, datetime.now() + td, isPerson, people)
    return '0'

