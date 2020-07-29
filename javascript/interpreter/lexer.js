/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const { Base, isAlpha, isDigit, isSpace } = require('./common.js')


class Token extends Base {
  #name = ""
  #value = ""
  #type = ""

  constructor(name, value) {
    super()
    this.#name = name
    if (value) {
      this.#value = value
    }
  }

  get type() {
    if (!this.#type) {
      this.#type = Symbol.for(this.name)
    }
    return this.#type
  }

  get name() {
    return this.#name
  }

  get value() {
    if (this.#value) {
      return this.#value
    }
    throw new ReferenceError(`Tried to reference undefined value ` +
      `of token ${this.name}`)
  }
}


const EOF = new Token('EOF', 'EOF')

const LPAREN = new Token('LPAREN', '(')
const RPAREN = new Token('RPAREN', ')')

const ADD = new Token('ADD', '+')
const SUB = new Token('SUB', '-')
const MUL = new Token('MUL', '*')
const DIV = new Token('DIV', '/')

const INT = new Token('INT')

/* Pseudo-enum */
const UniqueTokens = {
  EOF,
  LPAREN,
  RPAREN,
  ADD,
  SUB,
  MUL,
  DIV,
  INT,
}


class Lexer extends Base {
  constructor(text) {
    super()

    this.cursor = 0
    this.text = text
  }

  /* FIXME: this is test function
   * remove me when finish
   */
  print() {
    console.log(this.nextToken().value)
  }

  readchar() {
    return this.text[this.cursor]
  }

  forward() {
    return this.text[++this.cursor]
  }

  peek() {
    return this.text[this.cursor+1]
  }

  skipWhiteSpace() {
    let c
    while ((c=this.readchar()) !== undefined) {
      if (isSpace(c)) {
        this.forward()
        continue
      }
      break
    }
  }

  integer() {
    let c
    let result = ''

    while ((c=this.readchar()) !== undefined) {
      if (isDigit(c)) {
        result += c
        this.forward()
        continue
      }
      break
    }
    return new Token('INT', result)
  }

  identifier() {
    let c
    let result = ''

    while ((c=this.readchar()) !== undefined) {
      if (isAlpha(c)) {
        result += c
        this.forward()
        continue
      }
      break
    }
    return new Token('ID', result)
  }

  nextToken() {
    let c
    while ((c=this.readchar()) !== undefined) {
      if (isSpace(c)) {
        this.skipWhiteSpace()
        continue
      }

      if (isAlpha(c)) return this.identifier()
      if (isDigit(c)) return this.integer()

      switch (c) {
        case '(':
          this.forward()
          return UniqueTokens.LPAREN
          break
        case ')':
          this.forward()
          return UniqueTokens.RPAREN
          break
        case '+':
          this.forward()
          return UniqueTokens.ADD
        case '-':
          this.forward()
          return UniqueTokens.SUB
        case '*':
          this.forward()
          return UniqueTokens.MUL
        case '/':
          this.forward()
          return UniqueTokens.DIV
        default:
          break
      }
      throw new SyntaxError(`Invalid character: ${c}`)
    }
    return EOF
  }

  tokenize() {
    const tokens = []

    let token
    do {
      token = this.nextToken()
      if (!token) break
      tokens.push(token)
    } while (token.type !== EOF.type)

    return tokens
  }
}


module.exports = {
  Lexer,
  Token,
  UniqueTokens,
  ...UniqueTokens
}
