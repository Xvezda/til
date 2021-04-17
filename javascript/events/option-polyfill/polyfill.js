import { checkSupport } from './detect.js'

if (EventTarget.prototype.addEventListener) {
  const shims = {
    once: function (type, listener, options) {
      const onceHandler = () => {
        // Remove listener
        this.removeEventListener(type, listener, options)
        // Then remove itself
        this.removeEventListener(type, onceHandler, options)
      }
      this.addEventListener(type, onceHandler, options)
    },
    signal: function (type, listener, options) {
      const signal = options.signal
      signal.addEventListener('abort', (evt) => {
        this.removeEventListener(type, listener, options)
      }, {capture: false, once: true})
    }
  }

  const original = EventTarget.prototype.addEventListener
  function addEventListener(type, listener, useCapture) {
    console.debug('addEventListener:', this, type, listener, useCapture)

    if (typeof useCapture !== 'boolean') {
      const options = useCapture
      Object.keys(options).forEach(key => {
        if (!checkSupport(key) && shims[key] !== undefined) {
          const shim = shims[key]
          shim.call(this, type, listener, options)
        }
      })
    }
    return original.call(this, type, listener, useCapture)
  }
  // Replace original prototype
  EventTarget.prototype.addEventListener = addEventListener
}
