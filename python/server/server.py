import logging

log = logging.getLogger('dima')
hdlr = logging.FileHandler('/var/log/dima.log')
formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
hdlr.setFormatter(formatter)
log.addHandler(hdlr) 
log.setLevel(logging.INFO)

from flask import Flask

app = Flask(__name__)
app.debug = True

@app.route("/")
def index():
    log.info("/")
    content = 'OK'
    content_type = 'text/plain; charset=utf-8'
    return content, 200, {'Content-type': content_type}

if __name__ == '__main__':
    app.run()
