import logging
logging.basicConfig()

from kafka.client import KafkaClient
from kafka.consumer import SimpleConsumer

kafka = KafkaClient("localhost", 9092)

consumer = SimpleConsumer(kafka, "test", "test")
for message in consumer:
    print(message)

# Invoking consumer.commit() does not work with the message below.
# Each run of this script just dumps all the messages.
# consumer.commit()
error_message='''
WARNING:kafka:Could not send request [F
                                        kafka-pythontest
test��

��] to server <KafkaConnection host=dima-i8 port=9092>: Kafka @ dima-i8:9092 went away
Traceback (most recent call last):
  File "log_saver.py", line 14, in <module>
    consumer.commit()
  File "/home/dima/.local/lib/python2.7/site-packages/kafka/consumer.py", line 144, in commit
    resps = self.client.send_offset_commit_request(self.group, reqs)
  File "/home/dima/.local/lib/python2.7/site-packages/kafka/client.py", line 318, in send_offset_commit_request
    resps = self._send_broker_aware_request(payloads, encoder, decoder)
  File "/home/dima/.local/lib/python2.7/site-packages/kafka/client.py", line 184, in _send_broker_aware_request
    raise FailedPayloadsException(failed_payloads)
kafka.common.FailedPayloadsException: [OffsetCommitRequest(topic='test', partition=0, offset=7, metadata=None), OffsetCommitRequest(topic='test', partition=1, offset=1, metadata=None)]
dima@dima-i8:~/github/dkorolev/sandbox/python/log_saver$ 
'''

kafka.close()
