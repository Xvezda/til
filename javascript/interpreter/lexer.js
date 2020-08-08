/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const { Base, isAlpha, isDigit, isAlnum, isSpace } = require('./common.js')


class Token extends Base {
  #type = ""

  constructor(name, value) {
    super()
    this.name = name
    if (value) {
      this.value = value
    } else {
      this.value = this.name
    }
  }

  get type() {
    if (!this.#type) {
      this.#type = Symbol.for(this.name.toUpperCase())
    }
    return this.#type
  }
}


const EOF = new Token('EOF', 'EOF')

const BEGIN = new Token('BEGIN', 'BEGIN')
const END = new Token('END', 'END')

const PROGRAM = new Token('PROGRAM', 'PROGRAM')
const PROCEDURE = new Token('PROCEDURE', 'PROCEDURE')
const VAR = new Token('VAR', 'VAR')

const INTEGER = new Token('INTEGER', 'INTEGER')
const REAL = new Token('REAL', 'REAL')

const DOT = new Token('DOT', '.')
const COLON = new Token('COLON', ':')
const COMMA = new Token('COMMA', ',')
const SEMI = new Token('SEMI', ';')
const LPAREN = new Token('LPAREN', '(')
const RPAREN = new Token('RPAREN', ')')

const ASSIGN = new Token('ASSIGN', ':=')
const ADD = new Token('ADD', '+')
const SUB = new Token('SUB', '-')
const MUL = new Token('MUL', '*')
const FLOAT_DIV = new Token('FLOAT_DIV', '/')
const DIV = new Token('DIV', 'DIV')

const ID = new Token('ID')
const REAL_CONST = new Token('REAL_CONST')
const INTEGER_CONST = new Token('INTEGER_CONST')


/* Pseudo-enum */
const UniqueTokens = {
  EOF,
  BEGIN,
  END,
  PROGRAM,
  PROCEDURE,
  VAR,
  INTEGER,
  REAL,
  DOT,
  COLON,
  COMMA,
  SEMI,
  LPAREN,
  RPAREN,
  ASSIGN,
  ADD,
  SUB,
  MUL,
  FLOAT_DIV,
  DIV,
  ID,
  REAL_CONST,
  INTEGER_CONST,
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

  skipComment() {
    let c
    while ((c=this.readchar()) !== undefined) {
      if (c === '}') {
        break
      }
      this.forward()
    }
    this.forward()
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

  number() {
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
    if (c === '.') {
      result += c
      this.forward()

      while ((c=this.readchar()) !== undefined) {
        if (isDigit(c)) {
          result += c
          this.forward()
          continue
        }
        break
      }
      return new Token('REAL_CONST', result)
    }
    return new Token('INTEGER_CONST', result)
  }

  identifier() {
    let c = this.readchar()
    let result = c
    this.forward()

    const reserved = [
      UniqueTokens.BEGIN,
      UniqueTokens.END,
      UniqueTokens.PROGRAM,
      UniqueTokens.PROCEDURE,
      UniqueTokens.VAR,
      UniqueTokens.DIV,
      UniqueTokens.INTEGER,
      UniqueTokens.REAL,
    ]

    while ((c=this.readchar()) !== undefined) {
      if (isAlnum(c)) {
        result += c
        this.forward()
        continue
      }
      break
    }

    for (const token of reserved) {
      if (token.name.toUpperCase() === result.toUpperCase()) {
        return token
      }
    }
    return new Token('ID', result)
  }

  nextToken() {
    let c
    while ((c=this.readchar()) !== undefined) {
      if (c === '{') {
        this.forward()
        this.skipComment()
        continue
      }

      if (isSpace(c)) {
        this.skipWhiteSpace()
        continue
      }

      if (isAlpha(c) || c === '_') return this.identifier()
      if (isDigit(c)) return this.number()

      switch (c) {
        case '(':
          this.forward()
          return UniqueTokens.LPAREN
        case ')':
          this.forward()
          return UniqueTokens.RPAREN
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
          return UniqueTokens.FLOAT_DIV
        case ':':
          switch (this.peek()) {
            case '=':
              this.forward()
              this.forward()
              return UniqueTokens.ASSIGN
            default:
              this.forward()
              return UniqueTokens.COLON
          }
          break
        case ';':
          this.forward()
          return UniqueTokens.SEMI
        case ',':
          this.forward()
          return UniqueTokens.COMMA
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
