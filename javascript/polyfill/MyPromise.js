module.exports = (function() {
  /* constructor */
  function MyPromise(callback) {
    /* private */
    this._resolve_chains = [];
    this._reject_chains = [];
    this._finally_chains = [];

    var resolve = (function(data) {
      var callback = this._resolve_chains.shift();
      if (!callback) return finally_();

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

    var reject = (function(err) {
      var callback = this._reject_chains.shift();
      if (!callback) return finally_();
      try {
        callback(err);
        return finally_();
      } catch (err) {
        reject(err);
      }
    }).bind(this);

    var finally_ = (function() {
      var callback = this._finally_chains.shift();
      if (!callback) return;
      try {
        callback();
      } catch (err) {
        reject(err);
      }
    }).bind(this);

    callback(resolve, reject);
  }

  /* public */
  MyPromise.prototype.then = function(callback) {
    this._resolve_chains.push(callback);

    return this;
  };

  MyPromise.prototype.catch = function(callback) {
    this._reject_chains.push(callback);

    return this;
  };

  MyPromise.prototype.finally = function(callback) {
    this._finally_chains.push(callback);

    return this;
  };

  return MyPromise;
})();
