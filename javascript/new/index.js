// Copyright (C) 2020 Xvezda <xvezda@naver.com>

function is_new_or_call () {
  var ctor;
  if ('getPrototypeOf' in Object) {
    ctor = Object.getPrototypeOf(this).constructor
  } else {
    ctor = this.__proto__.constructor
  }
  if (arguments.callee === ctor) {
    console.log('this is new operator');
  } else {
    console.log('this is function call');
  }
}


// Function call
is_new_or_call();

// New operator
new is_new_or_call();
