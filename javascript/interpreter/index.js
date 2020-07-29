/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


const readline = require('readline')
const { Color } = require('./common.js')
const Interpreter = require('./interpreter.js')

const interpreter = new Interpreter()
const PS1 = '> '

const isDev = process.env.NODE_ENV === 'development'

if (typeof console === 'object' && 'debug' in console) {
  if (!isDev) {
    global.console.debug = new Function
  } else {
    global.console.debug = console.debug.bind(null, Color.red`DEBUG:`)
  }
}



rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  prompt: PS1
})

rl.prompt()
rl.on('line', input => {
  if (input) {
    if (isDev) {
      var timeout = setTimeout(() => {
        console.log('timeout!')
        process.exit(1)
      }, 1000)
    }

    let result = interpreter.feedline(input)
    if (result) {
      console.log(result)
    }

    if (isDev) {
      clearTimeout(timeout)
    }
  }
  rl.prompt()
}).on('close', () => {
  process.exit(0)
})
