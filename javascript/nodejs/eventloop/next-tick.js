const process = require('process')


function foo () {
  process.nextTick(function () {
    console.log('foo')
  })
  console.log('bar')
}

foo()
console.log('baz')

