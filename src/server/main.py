# main.py

from flask import Flask, render_template, request, url_for
from blueprint import user_blueprint

app = Flask(__name__)

app.register_blueprint(user_blueprint.user_blue)

@app.route('/')
def index() :
    html = render_template('index.html')
    return html

@app.route('/main_send', methods=['GET'])
def main_send():
    isPerson = request.args.get('isPerson')
    arduino_main_num = request.args.get('arduino_main_num')
    print(isPerson, arduino_main_num)
    return '0'

if __name__=='__main__':
    app.run(host = '0.0.0.0', port = 3000, debug=True) # host='0.0.0.0')
