const WebSocket = require('websocket').w3cwebsocket
const readline  = require('readline')

const config = require('./package.json').config

const ws = new WebSocket('ws://' + config.host + ':' + config.port)

ws.onopen = function (event) {
  console.log('connected')

  let rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: 'ws> '
  })

  ws.onmessage = function (event) {
    /*
    readline.moveCursor(process.stdout, 0, -1)
    readline.clearLine(process.stdout, 0)
    readline.cursorTo(process.stdout, 0)
    */

    console.log('server>', event.data)
    rl.prompt()
  }

  rl.prompt()
  rl.on('line', function (line) {
    ws.send(line)
    /*
    rl.prompt()
    */
  })
}

ws.onclose = function (event) {
  console.log('disconnected')
  process.exit(0)
}

