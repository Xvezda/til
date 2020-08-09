/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const { Base, isAlpha, isDigit, isAlnum, isSpace } = require('./common.js')
const { LexerError } = require('./errors.js')


class Token extends Base {
  #type = ""

  constructor(name, value, lineno, column) {
    super()
    this.name = name
    if (value) {
      this.value = value
    } else {
      this.value = this.name
    }
    this.lineno = lineno
    this.column = column
  }

  get type() {
    if (!this.#type) {
      this.#type = Symbol.for(this.name.toUpperCase())
    }
    return this.#type
  }

  toString() {
    const attrs = [this.name]
    if (this.value) attrs.push(this.value)
    attrs.push(`position=${[this.lineno, this.column].join(':')}`)
    return `Token(${attrs.join(', ')})`
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
  /* Start Reserved */
  BEGIN,
  END,
  PROGRAM,
  PROCEDURE,
  VAR,
  INTEGER,
  REAL,
  DIV,
  /* End of Reserved */
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
  ID,
  REAL_CONST,
  INTEGER_CONST,
}

const RESERVED_KEYWORDS = buildReservedKeywords()

function buildReservedKeywords() {
  const reserved = {}

  const keys = Object.keys(UniqueTokens)
  const startIdx = keys.indexOf('BEGIN')
  const endIdx = keys.indexOf('DIV')

  Object.entries(UniqueTokens).forEach(([k, v], i) => {
    if (startIdx <= i && i <= endIdx) {
      reserved[k] = v
    }
  })

  return reserved
}


function getTokenNameByValue(value) {
  for (const v of Object.values(UniqueTokens)) {
    if (v.value === value) return v.name
  }
}


class Lexer extends Base {
  constructor(text) {
    super()

    this.cursor = 0
    this.text = text

    this.lineno = 1
    this.column = 1
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
    if (this.readchar() === '\n') {
      ++this.lineno
      this.column = 0
    }
    const ret = this.text[++this.cursor]
    if (ret !== undefined) {
      ++this.column
    }
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

    const reserved = Object.values(RESERVED_KEYWORDS)

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
        case ':':
          switch (this.peek()) {
            case '=':
              this.forward()
              this.forward()
              return UniqueTokens.ASSIGN
            default:
              break
          }
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case ';':
        case ',':
        case '.':
        {
          const name = getTokenNameByValue(c)
          if (name !== undefined) {
            this.forward()
            return new Token(name, c,
              this.lineno, this.column)
          }
        }
        default:
          break
      }
      this.error()
    }
    return EOF
  }

  error() {
    throw new LexerError(`Lexer error on '${this.readchar()}'` +
      ` line: ${this.lineno} column: ${this.column}`)
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
