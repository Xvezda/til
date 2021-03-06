/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const util = require('util')


class Base {
  getClassName() {
    return this.constructor.name
  }

  [util.inspect.custom]() {
    return this.toString()
  }

  toString() {
    return util.inspect(this, {customInspect: false})
  }
}


class Stack extends Base {
  #items = null

  constructor() {
    super()
    this.#items = []
  }

  push(item) {
    this.#items.push(item)
  }

  pop() {
    return this.#items.pop()
  }

  peek() {
    return this.#items.slice(-1)[0]
  }

  get items() {
    return this.#items.slice()
  }
}


const ESC = '\x1b'
function ansiEscapeControlSequence(...args) {
  return `${ESC}[${args.join('')}`
}

const hasColors = process.stdout.hasColors()

function controlSequenceColor(...args) {
  // return ansiEscapeControlSequence(args.join(';'), 'm')
  return ansiEscapeControlSequence(args[0], 'm')
}

const RESET = hasColors ? controlSequenceColor('0') : ''
function colorTemplate(modifier) {
  if (!hasColors) modifier = ''
  return (strings, ...args) => {
    let result = modifier + strings[0]
    args.forEach((v, i) => {
      result += v
      result += strings[i]
    })
    if (!result.includes(RESET)) {
      result += RESET
    }
    return result
  }
}


const Color = {
  ...Object.fromEntries(
    Object.entries(util.inspect.colors).map(([k, v]) => {
      const csi = controlSequenceColor(...v)
      return [k, colorTemplate(csi)]
    })
  ),
  // Add color here
}


function isWrapper(pattern) {
  return text => {
    return !!(text || '').match(pattern)
  }
}


function isAlpha(text) {
  const func = isWrapper(/[a-z]+/i)
  return func(text)
}


function isDigit(text) {
  const func = isWrapper(/[0-9]+/)
  return func(text)
}


function isSpace(text) {
  const func = isWrapper(/\s+/)
  return func(text)
}


function isAlnum(text) {
  return isAlpha(text) || isDigit(text)
}


module.exports = {
  Base,
  Stack,
  Color,
  isAlpha,
  isDigit,
  isSpace,
  isAlnum,
}
