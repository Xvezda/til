/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const assert = require('assert')

const { Base } = require('./common.js')
const { Token, UniqueTokens } = require('./lexer.js')


class Tree extends Base {
  constructor() {
    super()
  }
}


class Ast extends Tree {
  constructor() {
    super()
  }
}


class BinaryOperator extends Ast {
  constructor(left, operator, right) {
    super()

    this.left = left
    this.operator = operator
    this.right = right
  }

  get value() {
    return this.operator
  }
}


class Integer extends Ast {
  constructor(value) {
    super()
    this.value = value
  }
}


class Parser extends Base {
  #token = null

  constructor(lexer) {
    super()

    this.lexer = lexer
    this.token = this.lexer.nextToken()
  }

  set token(value) {
    this.#token = value
  }

  get token() {
    return this.#token
  }

  parse() {
    /*
     * expr2: expr1 (( ADD | SUB) expr1)*
     * expr1: factor (( MUL | DIV ) factor)*
     * factor: LPAREN expr2 RPAREN | INT
     */
    return this.expr2()
  }

  expr2() {
    let node = this.expr1()

    while ([UniqueTokens.ADD, UniqueTokens.SUB].some(op => (
      op.type === this.token.type
    ))) {
      const token = this.token
      this.eat(token.name)
      node = new BinaryOperator(node, token.value, this.expr1())
    }
    return node
  }

  expr1() {
    let node = this.factor()

    while ([UniqueTokens.MUL, UniqueTokens.DIV].some(op => (
      op.type === this.token.type
    ))) {
      const token = this.token
      this.eat(token.name)
      node = new BinaryOperator(node, token.value, this.factor())
    }
    return node
  }

  eat(type) {
    try {
      if (this.token.type === UniqueTokens[type].type) {
        this.token = this.lexer.nextToken()
        return
      }
    } catch (e) {
      console.error(e)
    }
    throw new Error(`Current token ${this.token.value} is not type ${type}`)
  }

  factor() {
    let node
    if (this.token.type === UniqueTokens.LPAREN.type) {
      this.eat('LPAREN')

      node = this.expr2()

      this.eat('RPAREN')
      return node
    }

    if (this.token.type === UniqueTokens.INT.type) {
      node = new Integer(this.token.value)
      this.eat('INT')
      return node
    }
    throw new SyntaxError(`Unexpected token ${this.token.value}`)
  }
}

module.exports = {
  Parser,
}

