// __proto__ equivalent
const protoEquiv = Symbol.for('__proto__')

// This will emulate prototype chain lookup
// `foo.bar` is equivalent to `getprop(foo, 'bar)`
function getprop(obj, prop) {
  try {
    // Check object itself
    if (obj[prop]) throw obj[prop]

    // Lookup prototypes
    let proto = obj[protoEquiv]
    if (proto === null) return
    do {
      if (proto[prop]) throw proto[prop]
    } while ((proto=proto[protoEquiv]) !== null)
  } catch (o) {
    // Bind this to obj if callable
    if (o && o.constructor === Function && prop !== '$constructor') {
      return o.bind(obj)
    }
    return o
  }
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
const foo = funcwrap(function foo() {
  this.bar = 1
})
foo.$prototype.baz = 2
foo.$prototype.hello = function() {
  return `Hi, i'm ${getprop(this, '$constructor').name}`
}


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
// o.hello()
console.log(getprop(o, 'hello')())


// Equivalent to extends keyword
function inherits(ctor, superctor) {
  for (const prop in superctor.$prototype) {
    ctor.$prototype[prop] = superctor.$prototype[prop]
  }
  ctor.$prototype['$constructor'] = ctor
  ctor.$prototype['$superctor'] = superctor
}

// Equivalent to super
function parent(thisArg, supercls, method) {
  supercls.call(thisArg)

  if (!method) return
  return supercls.$prototype[method].bind(thisArg)
}


const egg = funcwrap(function egg() {
  // super()
  parent(this, foo)

  this.spam = 42
})
// class egg extends foo
inherits(egg, foo)

egg.$prototype.hello = function() {
  // super.hello()
  return parent(this, foo, 'hello')() + ' and this is inherted method!'
}


// o2 = new egg
const o2 = newop(egg)
// o2.bar
console.log(getprop(o2, 'bar'))
// o2.baz
console.log(getprop(o2, 'baz'))
// o2.spam
console.log(getprop(o2, 'spam'))
// o2.hello()
console.log(getprop(o2, 'hello')())

