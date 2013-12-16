import logging
logging.basicConfig()

from kafka.client import KafkaClient
from kafka.producer import SimpleProducer

kafka = KafkaClient("localhost", 9092)

producer = SimpleProducer(kafka, "test")
producer.send_messages("sent from python")

kafka.close()
