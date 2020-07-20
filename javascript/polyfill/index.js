var MyPromise = require('./MyPromise.js');


function testPromiseResolve() {
  return new MyPromise(function(resolve, reject) {
    setTimeout(function() {
      resolve('test');
    }, 1000);
  });
}

testPromiseResolve().then(function(data) {
  console.log(data);
});
