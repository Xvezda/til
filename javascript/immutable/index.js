var Immutable = require('immutable');

var foo = { baz: 'foo' };
var bar = { baz: 'bar' };

foo.baz = 'test';
var baz = foo;
console.log('baz:', baz.baz);
console.log('foo:', foo);

baz = Immutable.fromJS(bar).set('baz', 'test');
console.log('baz:', baz.get('baz'));
console.log('bar:', bar);

