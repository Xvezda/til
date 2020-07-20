module.exports = (function() {
  /* constructor */
  function MyPromise(callback) {
    /* private */
    this._chains = [];

    var _resolve = (function(data) {
      var chain, retval;
      do {
        chain = this._chains.shift();
        if (!chain) return;
      } while (chain.type === 'reject')

      try {
        retval = chain.handler(data);
        if (retval instanceof MyPromise) {
          return retval.then(_resolve);
        }
        _resolve(retval);
      } catch (err) {
        _reject(err);
      }
    }).bind(this);

    var _reject = (function(err) {
      var chain, retval;
      do {
        chain = this._chains.shift();
        if (!chain) return;
      } while (chain.type !== 'reject')

      try {
        retval = chain.handler(err);
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
  MyPromise.prototype.then = function(callback) {
    this._chains.push({handler: callback, type: 'resolve'});

    return this;
  };

  MyPromise.prototype.catch = function(callback) {
    this._chains.push({handler: callback, type: 'reject'});

    return this;
  };

  MyPromise.prototype.finally = function(callback) {
    this._chains.push({handler: callback, type: 'finally'});

    return this;
  };

  return MyPromise;
})();
