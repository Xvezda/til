var foo = require('./foo.js');
var egg = require('./egg.js');

console.log('=== before monkeypatch ===');
foo.bar();
egg.ham();

// Monkeypatch part
var fooExports = foo;
fooExports.bar = function() {
  console.log('this is bar and it is now monkeypatched! :)');
};

// It is possible because; every time `require('./foo.js')` is called,
// same instance of `exports` is returned.
console.log('=== after monkeypatch ===');
foo.bar();
egg.ham();
