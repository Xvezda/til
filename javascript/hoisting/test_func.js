function foo() {
  console.log('foo');
}

foo();  // foo or foo2?

function foo() {
  console.log('foo2');
}

// ===================================================

var bar = () => {
  console.log('bar');
};

bar();  // bar or bar2?

var bar = () => {
  console.log('bar2');
};
