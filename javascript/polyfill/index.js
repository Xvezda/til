var MyPromise = require('./MyPromise.js');


function testPromiseResolve(delay) {
  return new MyPromise(function(resolve, reject) {
    setTimeout(function() {
      resolve('test');
    }, delay);
  });
}

function testPromiseReject(delay) {
  return new MyPromise(function(resolve, reject) {
    setTimeout(function() {
      reject(new Error('some error blah blah...'));
    }, delay);
  });
}

function testPromiseCatch(delay) {
  return new MyPromise(function(resolve, reject) {
    setTimeout(function() {
      resolve('resolved?');
    }, delay);
  });
}

function testPromiseChain(delay) {
  return new MyPromise(function(resolve, reject) {
    setTimeout(function() {
      resolve(1);
    }, delay);
  });
}


testPromiseResolve(1000)
  .then(function(data) {
    console.log(data);
  })
  .finally(function() {
    console.log('done');
  });

testPromiseReject(2000)
  .then(function(data) {
    console.log(data);
  }).catch(function(err) {
    console.log(err.message);
  })
  .finally(function() {
    console.log('done');
  });

testPromiseChain(3000)
  .then(function(data) {
    console.log('first: ' + data);
    return data * 2;
  })
  .then(function(data) {
    console.log('second: ' + data);
    return data * 2;
  })
  .then(function(data) {
    console.log('third: ' + data);
  })
  .finally(function() {
    console.log('done');
  })

testPromiseCatch(4000)
  .then(function(data) {
    throw new Error('error!');
    console.log(data);
  })
  .catch(function(err) {
    console.log(err.message);
  })
  .finally(function() {
    console.log('done');
  });

testPromiseCatch(5000)
  .then(function(data) {
    console.log(data);
    throw new Error('error!');
  })
  .catch(function(err) {
    console.log(err.message);
    throw new Error('error!');
  })
  .catch(function(err) {
    console.log(err.message);
  })
  .finally(function() {
    console.log('done');
  });

testPromiseChain(6000)
  .then(function(data) {
    console.log('first: ' + data);
    return new MyPromise(function(resolve, reject) {
      setTimeout(function() {
        resolve(data * 2);
      }, 2000);
    });
  })
  .then(function(data) {
    console.log('second: ' + data);
    return new MyPromise(function(resolve, reject) {
      setTimeout(function() {
        resolve(data * 2);
      }, 3000);
    });
  })
  .then(function(data) {
    console.log('third: ' + data);
  })
  .finally(function() {
    console.log('done');
  })


console.log('start');

