/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


const fs = require('fs')
const readline = require('readline')
const { Color } = require('./common.js')
const { Lexer } = require('./lexer.js')
const { Parser } = require('./parser.js')
const { Interpreter } = require('./interpreter.js')

const PS1 = '> '

const isDev = process.env.NODE_ENV === 'development'

if (typeof console === 'object' && 'debug' in console) {
  if (!isDev) {
    global.console.debug = new Function
  } else {
    global.console.debug = console.debug.bind(null, Color.red`DEBUG:`)
  }
}


function processInput(input) {
  if (isDev) {
    var timeout = setTimeout(() => {
      console.log('timeout!')
      process.exit(1)
    }, 1000)
  }

  const tokens = new Lexer(input)
  const parser = new Parser(tokens)
  const ast = parser.parse()

  const interpreter = new Interpreter(ast)

  const result = interpreter.interpret()
  if (result !== undefined) {
    console.log(result)
  }
  console.log(interpreter.globals)

  if (isDev) {
    clearTimeout(timeout)
  }
}


if (process.argv[2]) {
  const filePath = process.argv[2]

  fs.readFile(filePath, 'utf8', (err, data) => {
    if (err) throw err
    processInput(data)
  })

} else {
  let rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: PS1
  })

  rl.prompt()
  rl.on('line', input => {
    processInput(input)
    rl.prompt()
  }).on('close', () => {
    process.exit(0)
  })
}


