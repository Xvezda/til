/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const assert = require('assert')

const { Base } = require('./common.js')
const { Token, UniqueTokens } = require('./lexer.js')
const { ErrorCode, ParserError } = require('./errors.js')


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


class Program extends Ast {
  constructor(name, block) {
    super()
    this.name = name
    this.block = block
  }
}


class Block extends Ast {
  constructor(declarations, compoundStatement) {
    super()
    this.declarations = declarations
    this.compoundStatement = compoundStatement
  }
}


class VarDecl extends Ast {
  constructor(varNode, typeNode) {
    super()
    this.varNode = varNode
    this.typeNode = typeNode
  }
}


class ProcDecl extends Ast {
  constructor(procName, params, blockNode) {
    super()
    this.procName = procName
    this.params = params
    this.blockNode = blockNode
  }
}


class Param extends Ast {
  constructor(varNode, typeNode) {
    super()
    this.varNode = varNode
    this.typeNode = typeNode
  }
}


class Type extends Ast {
  constructor(token) {
    super()
    this.token = token
    this.value = token.value
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


class Num extends Ast {
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

  error(errorCode, token) {
    throw new ParserError(`${errorCode}: ${token}`)
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
    this.error(ErrorCode.UNEXPECTED_TOKEN, this.token)
  }

  parse() {
    // https://ruslanspivak.com/lsbasi-part10/
    /*
    program : PROGRAM variable SEMI block DOT

    block : declarations compound_statement

    declarations : (VAR (variable_declaration SEMI)+)* procedure_declaration*

    procedure_declaration: PROCEDURE ID (LPAREN formal_parameter_list RPAREN)? SEMI block SEMI

    variable_declaration : ID (COMMA ID)* COLON type_spec

    formal_parameter_list : formal_parameters
                          | formal_parameters SEMI formal_parameter_list

    formal_parameters: ID (COMMA ID)* COLON type_spec

    type_spec : INTEGER | REAL

    compound_statement : BEGIN statement_list END

    statement_list : statement
                   | statement SEMI statement_list

    statement : compound_statement
              | assignment_statement
              | empty

    assignment_statement : variable ASSIGN expr

    empty :

    expr: term ((ADD | SUB) term)*

    term: factor ((MUL | INTEGER_DIV | FLOAT_DIV) factor)*

    factor : ADD factor
           | SUB factor
           | INTEGER_CONST
           | REAL_CONST
           | LPAREN expr RPAREN
           | variable

    variable: ID
    */

    const node = this.program()  // Start symbol
    if (this.token.type !== UniqueTokens.EOF.type) {
      throw new SyntaxError(`expect EOF, but ${this.token.value} found.`)
    }
    return node
  }

  /* program : PROGRAM variable SEMI block DOT */
  program() {
    this.eat('PROGRAM')
    const varNode = this.variable()
    const progName = varNode.value
    this.eat('SEMI')
    const blockNode = this.block()
    const progNode = new Program(progName, blockNode)
    this.eat('DOT')
    return progNode
  }

  /* block : declarations compound_statement */
  block() {
    const declarationsNode = this.declarations()
    const compoundNode = this.compoundStatement()
    return new Block(declarationsNode, compoundNode)
  }

  // declarations : (VAR (variable_declaration SEMI)+)* procedure_declaration*
  declarations() {
    let declarations = []
    while (this.token.type === UniqueTokens.VAR.type) {
      this.eat('VAR')
      do {
        declarations = declarations.concat(this.variableDeclarations())
        this.eat('SEMI')
      } while (this.token.type === UniqueTokens.ID.type)
    }

    while (this.token.type === UniqueTokens.PROCEDURE.type) {
      declarations.push(this.procedureDeclaration())
    }
    return declarations
  }

  // procedure_declaration: PROCEDURE ID (LPAREN formal_parameter_list RPAREN)? SEMI block SEMI
  procedureDeclaration() {
    this.eat('PROCEDURE')
    let procName = this.token.value
    this.eat('ID')

    let paramList = []
    if (this.token.type === UniqueTokens.LPAREN.type) {
      this.eat('LPAREN')
      paramList = this.formalParameterList()
      this.eat('RPAREN')
    }

    this.eat('SEMI')

    let blockNode = this.block()
    this.eat('SEMI')

    return new ProcDecl(procName, paramList, blockNode)
  }

  /* variable_declaration : ID (COMMA ID)* COLON type_spec */
  variableDeclarations() {
    let varNodes = [new Variable(this.token)]
    this.eat('ID')

    while (this.token.type === UniqueTokens.COMMA.type) {
      this.eat('COMMA')
      varNodes.push(new Variable(this.token))
      this.eat('ID')
    }
    this.eat('COLON')

    let typeNode = this.typeSpec()
    let varDecls = []
    for (const varNode of varNodes) {
      varDecls.push(new VarDecl(varNode, typeNode))
    }
    return varDecls
  }

  // formal_parameter_list : formal_parameters
  //                       | formal_parameters SEMI formal_parameter_list
  formalParameterList() {
    let params = this.formalParameters()
    if (this.token.type === UniqueTokens.SEMI.type) {
      this.eat('SEMI')
      params = params.concat(this.formalParameterList())
    }
    return params
  }

  // formal_parameters: ID (COMMA ID)* COLON type_spec
  formalParameters() {
    const paramNodes = []
    const varDecls = this.variableDeclarations()
    for (const varDecl of varDecls) {
      paramNodes.push(new Param(varDecl.varNode, varDecl.typeNode))
    }
    return paramNodes
  }

  /* type_spec : INTEGER | REAL */
  typeSpec() {
    const token = this.token
    if (token.type === UniqueTokens.INTEGER.type) {
      this.eat('INTEGER')
    } else {
      this.eat('REAL')
    }
    return new Type(token)
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
      throw new SyntaxError(`invalid token ${this.token.value}`)

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

  /* term: factor ((MUL | INTEGER_DIV | FLOAT_DIV) factor)*  */
  term() {
    let node = this.factor()

    while ([
      UniqueTokens.MUL,
      UniqueTokens.DIV,
      UniqueTokens.FLOAT_DIV
    ].some(op => (
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
   *       | INTEGER_CONST
   *       | REAL_CONST
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
    } else if (this.token.type === UniqueTokens.INTEGER_CONST.type) {
      node = new Num(this.token.value)
      this.eat('INTEGER_CONST')
      return node
    } else if (this.token.type === UniqueTokens.REAL_CONST.type) {
      node = new Num(this.token.value)
      this.eat('REAL_CONST')
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

