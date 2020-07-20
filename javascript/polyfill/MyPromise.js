module.exports = (function() {
  /* constructor */
  function MyPromise(callback) {
    /* private */
    this._chains = [];
    this._finally = new Function;

    var resolve = (function(data) {
      var callback = this._chains.shift();
      if (!callback) return this._finally();

      try {
        var retval = callback(data);
        if (retval instanceof MyPromise) {
          return retval.then(resolve);
        }
        resolve(retval);
      } catch (err) {
        reject(err);
      }
    }).bind(this);

    this._reject = new Function;
    var reject = (function(err) {
      this._reject(err);
      this._finally();
    }).bind(this);

    callback(resolve, reject);
  }

  /* public */
  MyPromise.prototype.then = function(callback) {
    this._chains.push(callback);

    return this;
  };

  MyPromise.prototype.catch = function(callback) {
    this._reject = callback;

    return this;
  };

  MyPromise.prototype.finally = function(callback) {
    this._finally = callback;

    return this;
  };

  return MyPromise;
})();
