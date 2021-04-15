import { AbortController } from './abort.polyfill.js'

const memoize = new Map()

// Use original prototype of event target
// to prevent recursion when invoked inside polyfill
const addEventListener = EventTarget.prototype.addEventListener
const removeEventListener = EventTarget.prototype.removeEventListener

export const checkSupport = (name) => {
  if (typeof memoize[name] !== 'undefined')
    return memoize[name]

  let isSupport = false
  const dummy = document.createElement('div')

  try {
    const options = {
      get [name]() {
        isSupport = true
        if (name === 'signal') {
          // Signal needs to be object
          const controller = new AbortController()
          return controller.signal
        }
        return isSupport
      }
    }
    addEventListener.call(dummy, 'click', (evt) => false, options)
    removeEventListener.call(dummy, 'click', (evt) => false, options)
  } catch (e) {
    console.error(e)
    isSupport = false
  } finally {
    memoize[name] = isSupport
    return isSupport
  }
}
