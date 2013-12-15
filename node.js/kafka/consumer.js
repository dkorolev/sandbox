var kafka = require('kafka');

var consumer = new kafka.Consumer({
    host: 'localhost',
    port: 9092,
    pollInterval: 2000,
    maxSize: 1024 * 1024,
});

consumer.on('message', function(topic, message) {
    console.log(message);
});

consumer.connect(function() {
    consumer.subscribeTopic({
        name: 'test',
        partition: 0,
    });
});
