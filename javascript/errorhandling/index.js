function throwSomeErrors() {
  var errors = [
    SyntaxError('fake syntax error'),
    TypeError('fake type error'),
    Error(':)')
  ];
  throw errors[Math.floor(Math.random() * errors.length)];
}

try {
  throwSomeErrors();
} catch (e) {
  if (e instanceof SyntaxError) {
    console.log('this is syntax error');
  } else if (e instanceof TypeError) {
    console.log('this is type error')
  } else {
    console.log('this is unknown error');
    // Re-throw
    throw e;
  }
}
