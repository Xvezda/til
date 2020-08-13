/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


require('./globals.js')

const fs = require('fs')
const readline = require('readline')
const { Color } = require('./common.js')
const { Lexer } = require('./lexer.js')
const { Parser } = require('./parser.js')
const { SemanticAnalyzer, Interpreter } = require('./interpreter.js')


const PS1 = '> '


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


