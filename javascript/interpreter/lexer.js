/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const { Base, isAlpha, isDigit, isSpace } = require('./common.js')


class Token extends Base {
  #type = ""

  constructor(name, value) {
    super()
    this.name = name
    if (value) {
      this.value = value
    }
  }

  get type() {
    if (!this.#type) {
      this.#type = Symbol.for(this.name)
    }
    return this.#type
  }
}


const EOF = new Token('EOF', 'EOF')

const BEGIN = new Token('BEGIN', 'BEGIN')
const END = new Token('END', 'END')
const DOT = new Token('DOT', '.')
const ID = new Token('ID')
const ASSIGN = new Token('ASSIGN', ':=')
const SEMI = new Token('SEMI', ';')
const LPAREN = new Token('LPAREN', '(')
const RPAREN = new Token('RPAREN', ')')

const ADD = new Token('ADD', '+')
const SUB = new Token('SUB', '-')
const MUL = new Token('MUL', '*')
// const DIV = new Token('DIV', '/')
const DIV = new Token('DIV', 'DIV')

const INT = new Token('INT')

/* Pseudo-enum */
const UniqueTokens = {
  EOF,
  BEGIN,
  END,
  DOT,
  ID,
  ASSIGN,
  SEMI,
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

    const reserved = [
      UniqueTokens.BEGIN,
      UniqueTokens.END,
      UniqueTokens.DIV
    ]

    while ((c=this.readchar()) !== undefined) {
      if (isAlpha(c) || (!result && c === '_')) {
        result += c
        this.forward()
        continue
      }
      break
    }
    // case insensitive
    result = result.toUpperCase()

    for (const token of reserved) {
      if (token.name === result) {
        return token
      }
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

      if (isAlpha(c) || c === '_') return this.identifier()
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
        /*
        case '/':
          this.forward()
          return UniqueTokens.DIV
        */
        case ':':
          switch (this.peek()) {
            case '=':
              this.forward()
              this.forward()
              return UniqueTokens.ASSIGN
            default:
              break
          }
          break
        case ';':
          this.forward()
          return UniqueTokens.SEMI
        case '.':
          this.forward()
          return UniqueTokens.DOT
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
