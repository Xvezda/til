var foo = require('./foo.js');

exports.ham = function() {
  console.log('call foo.bar()');
  foo.bar();
};

exports.expose = function() {
  return foo;
};
