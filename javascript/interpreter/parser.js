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


class Compound extends Ast {
  constructor() {
    super()
    this.childrens = []
  }
}


class Assign extends Ast {
  constructor(left, operator, right) {
    super()
    this.left = left
    this.operator = operator
    this.right = right
  }
}


class Variable extends Ast {
  constructor(token) {
    super()
    this.token = token
    this.value = token.value
  }
}


class Nop extends Ast {
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
}


class UnaryOperator extends Ast {
  constructor(operator, value) {
    super()
    this.operator = operator
    this.value = value
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

  parse() {
    // https://ruslanspivak.com/lsbasi-part9/
    /*
    program : compound_statement DOT

    compound_statement : BEGIN statement_list END

    statement_list : statement
                   | statement SEMI statement_list

    statement : compound_statement
              | assignment_statement
              | empty

    assignment_statement : variable ASSIGN expr

    empty :

    expr: term ((PLUS | MINUS) term)*

    term: factor ((MUL | DIV) factor)*

    factor : PLUS factor
           | MINUS factor
           | INTEGER
           | LPAREN expr RPAREN
           | variable

    variable: ID
    */

    const node = this.program()  // Start symbol
    if (this.token.type !== UniqueTokens.EOF.type) {
      throw new SyntaxError()
    }
    return node
  }

  /* program : compound_statement DOT */
  program() {
    let node = this.compoundStatement()
    this.eat('DOT')
    return node
  }

  /* compound_statement: BEGIN statement_list END */
  compoundStatement() {
    this.eat('BEGIN')
    let nodes = this.statementList()
    this.eat('END')

    let root = new Compound()
    for (const node of nodes) {
      root.childrens.push(node)
    }
    return root
  }

  /* statement_list : statement
   *                | statement SEMI statement_list
   */
  statementList() {
    let node = this.statement()
    const results = [node]

    while (this.token.type === UniqueTokens.SEMI.type) {
      this.eat('SEMI')
      results.push(this.statement())
    }

    if (this.token.type === UniqueTokens.ID.type)
      throw new SyntaxError()

    return results
  }

  /*
   * statement : compound_statement
   *           | assignment_statement
   *           | empty
   */
  statement() {
    let node
    if (this.token.type === UniqueTokens.BEGIN.type) {
      node = this.compoundStatement()
    } else if (this.token.type === UniqueTokens.ID.type) {
      node = this.assignmentStatement()
    } else {
      node = this.empty()
    }
    return node
  }

  /*
   * assignment_statement : variable ASSIGN expr
   */
  assignmentStatement() {
    const left = this.variable()
    const token = this.token
    this.eat('ASSIGN')
    const right = this.expr()
    const node = new Assign(left, token, right)
    return node
  }

  /* empty: */
  empty() {
    return new Nop()
  }

  expr() {
    let node = this.term()

    while ([UniqueTokens.ADD, UniqueTokens.SUB].some(op => (
      op.type === this.token.type
    ))) {
      const token = this.token
      this.eat(token.name)
      node = new BinaryOperator(node, token.value, this.term())
    }
    return node
  }

  term() {
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

  /* factor: ADD factor
   *       | SUB factor
   *       | INT
   *       | LPAREN expr RPAREN
   *       | variable
   */
  factor() {
    let node
    if (this.token.type === UniqueTokens.ADD.type) {
      const token = this.token
      this.eat('ADD')
      return new UnaryOperator(token.value, this.factor())
    } else if (this.token.type === UniqueTokens.SUB.type) {
      const token = this.token
      this.eat('SUB')
      return new UnaryOperator(token.value, this.factor())
    } else if (this.token.type === UniqueTokens.INT.type) {
      node = new Integer(this.token.value)
      this.eat('INT')
      return node
    } else if (this.token.type === UniqueTokens.LPAREN.type) {
      this.eat('LPAREN')

      node = this.expr()

      this.eat('RPAREN')
      return node
    } else {
      node = this.variable()
      return node
    }
  }

  /* variable: ID */
  variable() {
    const node = new Variable(this.token)
    this.eat('ID')
    return node
  }
}

module.exports = {
  Parser,
}

