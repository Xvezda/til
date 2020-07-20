module.exports = (function() {
  /* constructor */
  function MyPromise(callback) {
    /* private */
    this._chains = [];

    var _resolve = (function(value) {
      var chain, retval;
      do {
        chain = this._chains.shift();
        if (!chain) return;
      } while (chain.type === 'reject')

      try {
        retval = chain.handler(value);
        if (retval instanceof MyPromise) {
          return retval.then(_resolve);
        }
        _resolve(retval);
      } catch (err) {
        _reject(err);
      }
    }).bind(this);

    var _reject = (function(reason) {
      var chain, retval;
      do {
        chain = this._chains.shift();
        if (!chain) return;
      } while (chain.type !== 'reject')

      try {
        retval = chain.handler(reason);
        _finally();
      } catch (err) {
        _reject(err);
      }
    }).bind(this);

    var _finally = (function() {
      var chain, retval;
      do {
        chain = this._chains.shift();
        if (!chain) return;
        retval = chain.handler();
      } while (chain.type === 'finally');

      if (chain) _resolve(retval);
    }).bind(this);

    callback(_resolve, _reject);
  }

  /* public */
  MyPromise.prototype.then = function(onFulfilled, onRejected) {
    this._chains.push({handler: onFulfilled, type: 'resolve'});
    if (onRejected) this.catch(onRejected);

    return this;
  };

  MyPromise.prototype.catch = function(onRejected) {
    this._chains.push({handler: onRejected, type: 'reject'});

    return this;
  };

  MyPromise.prototype.finally = function(onFinally) {
    this._chains.push({handler: onFinally, type: 'finally'});

    return this;
  };

  return MyPromise;
})();
