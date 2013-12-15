var express = require('express');
var kafka = require('kafka');

var producer = new kafka.Producer({
    host: 'localhost',
    port: 9092,
    topic: 'test',
    partition: 0
});

producer.connect(function() {
    var app = express();

    app.use(express.json());

    app.post('/', function(req, res) {
        producer.send(JSON.stringify(req.body));
        res.send(JSON.stringify(req.body) + '\n');
    });

    app.listen(process.env.port || 3000);
});
