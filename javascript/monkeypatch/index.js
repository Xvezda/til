var foo = require('./foo.js');
var egg = require('./egg.js');

console.log('before monkeypatch');
foo.bar();
egg.ham();

// Monkeypatch part
var fooExports = foo;
fooExports.bar = function() {
  console.log('this is bar and it is now monkeypatched! :)');
};

console.log('after monkeypatch');
foo.bar();
egg.ham();
