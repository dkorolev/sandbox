import logging
logging.basicConfig()

from kafka.client import KafkaClient
from kafka.consumer import SimpleConsumer

kafka = KafkaClient("localhost", 9092)

consumer = SimpleConsumer(kafka, "test", "test")
for message in consumer:
  print(message)

kafka.close()
