const connections = []

self.onconnect = function(event) {
  console.log('connected')
  const port = event.ports[0]

  connections.push(port)

  port.onmessage = function(event) {
    connections.forEach(connection => {
      connection.postMessage(event.data)
    })
  }
}
