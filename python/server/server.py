import logging

log = logging.getLogger('dima')
hdlr = logging.FileHandler('/var/log/dima.log')
formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
hdlr.setFormatter(formatter)
log.addHandler(hdlr) 
log.setLevel(logging.INFO)

import json
from flask import Flask, request

app = Flask(__name__)
app.debug = True

content_type = 'text/plain; charset=utf-8'
response_params = {'Content-type': content_type}

@app.route("/")
def index():
    log.info('GET /')
    content = 'OK\n'
    return content, 200, response_params

@app.route('/', methods=['POST'])
def post():
    log.info('POST /')
    log.info(request.data)
    try:
        data = json.loads(request.data)
        return 'POST\n', 200, response_params
    except ValueError:
        return 'Invalid JSON\n', 415, response_params

if __name__ == '__main__':
    app.run()
