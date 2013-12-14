/*
# Usage.
node app.js
curl -H "Content-Type: application/json" -d '{"the_answer": 42}' localhost:3000
*/

var express = require('express');
var kafka = require('node-kafka');

var producer = new kafka.Producer({
    host: 'localhost',
    port: 9092,
    topic: 'test',
    partition: 0
})

producer.connect(function() {
    var app = express();

    app.use(express.json());

    app.post('/', function(req, res) {
        producer.send(JSON.stringify(req.body));
        res.send('OK: ' + JSON.stringify(req.body) + '\n');
    });

    app.listen(process.env.port || 3000);
});
