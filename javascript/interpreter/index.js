/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


const fs = require('fs')
const readline = require('readline')
const { Color } = require('./common.js')
const { Lexer } = require('./lexer.js')
const { Parser } = require('./parser.js')
const { SemanticAnalyzer, Interpreter } = require('./interpreter.js')

const yargs = require('yargs')


const PS1 = '> '

const isDev = process.env.NODE_ENV === 'development'

const argv = yargs
  .usage('Usage: $0 [options...] [file]')
  .option('scope', {
    alias: 's',
    description: 'Print information about scopes',
    type: 'boolean'
  })
  .option('file', {
    alias: 'f',
    description: 'Pascal source code file to execute',
    type: 'string'
  })
  .help()
  .alias('help', 'h')
  .argv

// Overwrite console loggers
if (typeof console !== 'undefined') {
  if (!isDev) {
    global.console.debug = new Function
  } else {
    global.console.debug = console.debug.bind(null, Color.red`DEBUG:`)
  }

  if (!!argv.scope) {
    global.console.info = console.info.bind(null, Color.blue`INFO:`)
  } else {
    global.console.info = new Function
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

  try {
    const analyzer = new SemanticAnalyzer()
    analyzer.visit(ast)

    const interpreter = new Interpreter(ast)
    const result = interpreter.interpret()

    if (result !== undefined) {
      console.log(result)
    }
    console.log(interpreter.globals)
  } catch (e) {
    console.error(e)
  }

  if (isDev) {
    clearTimeout(timeout)
  }
}


const filePath = argv.file || argv._[0]

if (!!filePath) {
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


