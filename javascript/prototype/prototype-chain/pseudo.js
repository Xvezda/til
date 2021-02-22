// __proto__ equivalent
const protoEquiv = Symbol.for('__proto__')

// This will emulate prototype chain lookup
// `foo.bar` is equivalent to `getprop(foo, 'bar)`
function getprop(obj, prop) {
  // Check object itself
  if (obj[prop]) return obj[prop]

  // Lookup prototypes
  let proto = obj[protoEquiv]
  if (proto === null) return
  do {
    if (proto[prop]) return proto[prop]
  } while ((proto=proto[protoEquiv]) !== null)
}

// new ctor(...args) is equivalent to newop(ctor, ...args)
function newop(ctor, ...args) {
  const obj = {}
  ctor.call(obj, ...args)

  // ctor.$prototype is equivalent to ctor.prototype
  const proto = ctor.$prototype

  obj[protoEquiv] = {}
  obj[protoEquiv][protoEquiv] = null
  for (const key in proto) {
    obj[protoEquiv][key] = ctor.$prototype[key]
  }
  // constructor equivalent
  obj[protoEquiv]['$constructor'] = ctor

  return obj
}

// To emulate default prototype when function defined
function funcwrap(func) {
  func.$prototype = {
    '$constructor': func
  }
  return func
}


// Equivalent to function foo() { ... }
const foo = funcwrap(function() {
  this.bar = 1
})
foo.$prototype.baz = 2


// o = new foo
const o = newop(foo)
// o.bar
console.log(getprop(o, 'bar'))
// o.baz
console.log(getprop(o, 'baz'))
// o.lol
console.assert(getprop(o, 'lol') === undefined)
// o.constructor
console.assert(getprop(o, '$constructor') === foo)
