#!/usr/bin/node

var _ = require('underscore');
var thrift = require('thrift');
var Int64 = require('node-int64');
var DimaService = require('./gen-nodejs/DimaService');
var ttypes = require('./gen-nodejs/dima_types');

exports.run = function() {
  var connection = thrift.createConnection("localhost", 9090);
  var client = thrift.createClient(DimaService, connection);

  connection.on('error', function(err) {
    console.error(err);
  });

  var e = new ttypes.DimaEntry();
  e.ms = new Int64(Date.now());
  e.value = new Int64(42);
  e.message = 'Hello from node.js';
  client.dima_push(e, function(err, data) {
    if (err) {
      console.log('ERROR', err);
      process.exit(1);
    } else {
      client.dima_stats(function(err, data) {
        if (err) {
          console.log('ERROR', err);
          process.exit(1);
        } else {
          console.log('OK');
          console.log(data);
          console.log(data.sum.toString());
          connection.end();
        }
      });
    }
  });
};

if (require.main === module) {
  exports.run();
}
