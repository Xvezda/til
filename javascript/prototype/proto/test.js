function foo() {}

var o = new foo;
o.__proto__.bar = 42;

console.log(foo.prototype.bar);

