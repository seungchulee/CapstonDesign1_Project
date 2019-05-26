# main.py

from flask import Flask, render_template


# 웹 서버 역활을 하기위한 객체를 생성한다.
app = Flask(__name__)
# 블루플린트를 등록한다.

# blueprint를 이용하여 업무를 나눈다.
# blueprint를 이용하여 url의 prefix를 부여하여 url별 계열을 나눈다.

# 주소만 입력해서 요청했을 때 호출되는 함수
@app.route('/')
def index() :
    html = render_template('user/user_login.html')
    # 읽어온 html 데이터를 브라우저로 전달한다.
    return html
#, port=80)
# 웹 서버를 실행한다.
#app.run(host='0.0.0.0', port=80)
if __name__=='__main__':
    # host : 접속할 컴퓨터의 IP, 0.0.0.0으로 셋팅하면 모든 컴퓨터 허용
    # port : 포트번호 설정, 80이면 웹 브라우저에서 포트번호 생략가능
    # app.run(host='0.0.0.0', port=80)
    app.run(debug=True) # host='0.0.0.0')