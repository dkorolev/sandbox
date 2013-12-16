import logging

log = logging.getLogger('dima')
hdlr = logging.FileHandler('/var/log/log_dumper.log')
formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
hdlr.setFormatter(formatter)
log.addHandler(hdlr) 
log.setLevel(logging.INFO)

from kafka.client import KafkaClient
from kafka.producer import SimpleProducer

import json
from flask import Flask, request

app = Flask(__name__)
app.debug = True

content_type = 'text/plain; charset=utf-8'
response_params = {'Content-type': content_type}

kafka = KafkaClient('localhost', 9092)
producer = SimpleProducer(kafka, 'test', async=True)

kafka.close()
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
        producer.send_messages(json.dumps(data))
        return 'POST\n', 200, response_params
    except ValueError:
        return 'Invalid JSON\n', 415, response_params

if __name__ == '__main__':
    app.run()
