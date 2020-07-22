const scope = 'test-serviceworker'

try {
  if ('serviceWorker' in window.navigator) {
    (async () => {
      const register = await window.navigator.serviceWorker
        .register(`/${scope}/sw.js`)
      register.addEventListener('updatefound', () => {
        console.log('update found!')
      })
      console.log(register)
      if (register.installing) {
        console.log('worker installing')
      } else if (register.waiting) {
        console.log('worker waiting')
        register.unregister()  // Check for update
      } else if (register.active) {
        console.log('worker active')
        register.update()  // Check for update
      }
    })()
  } else {
    throw new Error('ServiceWorker not supported browser')
  }
} catch (e) {
  if ('error' in console) {
    console.error(e)
  } else {
    throw e
  }
}

(async () => {
  const request = new Request('./data.json')
  const response = await fetch(request)
  const data = await response.json()

  try {
    console.log(data.message)
    document.querySelector('#output').textContent = JSON.stringify(data)
  } catch (e) {}
})()
