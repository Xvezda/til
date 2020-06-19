var os = require('os');
var interfaces = os.networkInterfaces();

var ipv4Interfaces = Object.entries(interfaces).map(function (entry) {
  var addresses = entry[1];
  return {
    name: entry[0],
    details: addresses.filter(function (address) {
      return address.family === 'IPv4';
    })
  };
});

var filtered = ipv4Interfaces.filter(function (interface) {
  return interface.details && interface.details.length > 0
});

filtered.forEach(function (interface) {
  console.log(interface.name, interface.details.shift().address);
});

