function foo() {
  ham = 'egg'
  console.log(ham)

  var ham
}

function bar() {
  ham = 'egg'
  console.log(ham)

  // Now, without declaration
  // var ham
}

console.log('call foo')
foo()

// Error or Not?
try {
  console.log(ham)
} catch (e) {
  console.log('error')
}

console.log('call bar')
bar()

// Error or Not?
try {
  console.log(ham)
} catch (e) {
  console.log('error')
}

