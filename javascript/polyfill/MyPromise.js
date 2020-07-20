
module.exports = (function() {
  /* private */
  var _resolve = new Function,
      _reject  = new Function;

  /* constructor */
  function MyPromise(callback) {
    function resolve(data) {
      _resolve(data);
    }

    function reject(err) {
      _reject(err);
    }

    callback(resolve, reject)
  }

  /* public */
  MyPromise.prototype.then = (function(callback) {
    _resolve = callback;
  }).bind(this);

  MyPromise.prototype.catch = (function(callback) {
    _reject = callback;
  }).bind(this);

  return MyPromise;
})();
