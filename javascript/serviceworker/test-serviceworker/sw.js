const cacheVersion = 'v9'

self.addEventListener('install', event => {
  console.log(event)
  /*
  event.waitUntil(caches.open(cacheVersion).then(cache => {
    return cache.addAll([
      './data.json',
    ])
  }))
  */
})

self.addEventListener('fetch', event => {
  console.log(event)
  event.respondWith(caches.match(event.request).then(response => {
    if (response === undefined) {
      return fetch(event.request).then(response => {
        return response
      })
    } else {
      if (event.request.url.endsWith('/data.json')) {
        return new Response(`
        {
          "message": "This is hijacked message!"
        }
        `.trim(), {
          headers: {
            'Content-Type': 'application/json'
          }
        })
      }
      return response
    }
  }))
})

self.addEventListener('activate', event => {
  console.log(event);
  /*
  let keepCaches = ['v5', cacheVersion]
  event.waitUntil(caches.keys().then(keys => {
    return Promise.all(keys.map(key => {
      if (!keepCaches.includes(key)) {
        return caches.delete(key)
      }
    }))
  }))
  */
})
