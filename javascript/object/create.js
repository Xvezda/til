var foo = {a: 1};

console.log('foo:', foo);
console.log('='.repeat(process.stdout.columns));

var bar = Object.create(foo);
bar.a = 42;

console.log('foo:', foo);
console.log('bar:', bar);
console.log('bar.__proto__:', bar.__proto__.a);


