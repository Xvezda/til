let _AbortController,
    _AbortSignal;

if (typeof AbortController !== 'undefined') {
  const setAborted = Symbol.for('setAborted')

  class AbortSignal extends EventTarget {
    constructor() {
      this.$handler = null
      this.$aborted = false
    }

    get aborted() {
      return this.$aborted
    }

    [setAborted](value) {
      if (this.$aborted = value) {
        this.dispatchEvent(new CustomEvent('abort'))
      }
    }

    set onabort(handler) {
      if (this.$handler) {
        this.removeEventListener('abort', handler, false)
      }
      this.addEventListener('abort', handler, false)
      this.$handler = handler
    }
  }

  class AbortController {
    constructor() {
      this.$signal = new AbortSignal()
    }

    get signal() {
      return this.$signal
    }

    abort() {
      this.$signal[setAborted](true);
    }
  }
}
_AbortController = AbortController
_AbortSignal = AbortSignal


export {
  _AbortController as AbortController,
  _AbortSignal as AbortSignal,
}

