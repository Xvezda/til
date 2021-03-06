module.exports = (function() {
  /* constructor */
  function MyPromise(callback) {
    /* private */
    this._chains = [];

    /* TODO: Process thenable object */
    var _resolve = (function(value) {
      var chain, retval;
      do {
        chain = this._chains.shift();
        if (!chain) return _finally();
      } while (chain.type === 'reject')

      try {
        retval = chain.handler(value);
        if (retval instanceof MyPromise) {
          return retval
            .then(_resolve)
            .catch(_reject)
            .finally(_finally);
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
        if (!chain) return _finally();
      } while (chain.type !== 'reject')

      try {
        retval = chain.handler(reason);
        if (retval instanceof MyPromise) {
          return retval
            .then(_resolve)
            .catch(_reject)
            .finally(_finally);
        }
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

      if (chain) {
        if (retval instanceof MyPromise) {
          return retval
            .then(_resolve)
            .catch(_reject)
            .finally(_finally);
        }
        _resolve(retval);
      }
    }).bind(this);

    setTimeout(function() {
      callback(_resolve, _reject);
    }, 0);
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

  /* static */
  MyPromise.resolve = function(value) {
    return new MyPromise(function(resolve) {
      resolve(value);
    });
  };

  MyPromise.reject = function(reason) {
    return new MyPromise(function(_, reject) {
      reject(reason);
    });
  };

  return MyPromise;
})();
