/* ws server */
const util = require('util')
const http = require('http')
const WebSocketServer = require('websocket').server

const config = require('./package.json').config

const server = http.createServer(function (req, res) {
  console.log((new Date) + ' received request for ' + req.url)
  res.writeHead(404)
  res.end()
})
server.listen(config.port, function () {
  console.log((new Date) + ' server is listening')
})

const wsServer = new WebSocketServer({
  httpServer: server,
  autoAcceptConnection: true
})


let pool = []  // connection pool

wsServer.on('request', function (req) {
  const connection = req.accept(null, req.origin)
  pool.push(connection)

  console.log((new Date) + ' client connected')
  // connection.sendUTF('hello world')

  connection.on('message', function (msg) {
    if (msg.type === 'utf8') {
      console.log((new Date) + ' received message: ' + msg.utf8Data)
      if (msg.utf8Data.startsWith('/')) {
        switch (msg.utf8Data.slice(1)) {
          case 'exit':
            connection.close()
            break
          default:
            connection.sendUTF(util.format("unknown command '%s'", msg.utf8Data))
            break
        }
      } else {
        // broadcasting
        pool.forEach(function (conn) {
          conn.sendUTF(msg.utf8Data)
        })
      }
    } else if (msg.type === 'binary') {
      // ignore
    }
  })

  connection.on('close', function (code, desc) {
    console.log((new Date) + ' client ' + connection.remoteAddress + ' disconnect')
    pool.splice(pool.indexOf(connection), 1)
  })
})

/* web server */
const fs = require('fs')
const express = require('express')
const app = express()

app.get('/', function (req, res) {
  fs.readFile('index.html', function (err, data) {
    res.send(data.toString())
  })
})
app.listen(config.port+1)
