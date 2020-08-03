/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const util = require('util')

const { Base } = require('./common.js')
const { Lexer } = require('./lexer.js')
const { Parser } = require('./parser.js')


class BaseSymbol extends Base {
  constructor(name, type) {
    super()
    this.name = name
    this.type = type
  }
}


class BuiltinTypeSymbol extends BaseSymbol {
  constructor(name) {
    super(name)
  }

  [util.inspect.custom]() {
    return `[${this.getClassName()}(${this.name})]`
  }
}


class VarSymbol extends BaseSymbol {
  constructor(name, type) {
    super(name, type)
  }
}


class SymbolTable extends Base {
  constructor() {
    super()
    this.symbols = {}

    this.define(new BuiltinTypeSymbol('INTEGER'))
    this.define(new BuiltinTypeSymbol('REAL'))
  }

  define(symbol) {
    console.debug('define:', symbol)
    this.symbols[symbol.name] = symbol
  }

  lookup(name) {
    console.debug('lookup:', name)
    return this.symbols[name]
  }
}



class Visitor extends Base {
  constructor() {
    super()
  }
}


class TreeVisitor extends Visitor {
  constructor() {
    super()
  }
}


class NodeVisitor extends TreeVisitor {
  constructor() {
    super()
  }

  visit(node) {
    const visitorName = `visit${node.getClassName()}`
    let visitorFunc = this[visitorName]
    if (!visitorFunc)
      throw new ReferenceError(`${this.getClassName()} has no method ` +
        `name ${visitorName}`)

    // We need to bind `this` to visitor function
    // If not, visitor function containing `this` will cause error.
    visitorFunc = visitorFunc.bind(this)
    return visitorFunc(node)
  }
}


class AstVisitor extends NodeVisitor {
  constructor() {
    super()
  }

  visitProgram(node) {
    this.visit(node.block)
  }

  visitBlock(node) {
    for (const declaration of node.declarations) {
      this.visit(declaration)
    }
    this.visit(node.compoundStatement)
  }
}


class SymbolTableBuilder extends AstVisitor {
  constructor() {
    super()
    this.symbolTable = new SymbolTable()
  }

  visitVarDecl(node) {
    console.debug('symbol table: visitVarDecl')
    console.debug(node)

    const typeName = node.typeNode.value
    const typeSymbol = this.symbolTable.lookup(typeName)
    const varName = node.varNode.value
    const varSymbol = new VarSymbol(varName, typeSymbol)

    this.symbolTable.define(varSymbol)
  }

  visitAssign(node) {
    const varName = node.left.value
    const varType = this.symbolTable.lookup(varName)
    if (varType === undefined)
      throw new ReferenceError(`Variable name ${varName} not exists`)

    this.visit(node.right)
  }

  visitVariable(node) {
    const varName = node.value
    const varSymbol = this.symbolTable.lookup(varName)
    if (varSymbol === undefined)
      throw new ReferenceError(`Variable name ${varName} not exists`)
  }

  visitNop(node) {
    // TODO
  }

  visitNum(node) {
    // TODO
  }

  visitCompound(node) {
    for (const children of node.childrens) {
      this.visit(children)
    }
  }

  visitUnaryOperator(node) {
    this.visit(node.value)
  }

  visitBinaryOperator(node) {
    this.visit(node.left)
    this.visit(node.right)
  }
}


class Interpreter extends AstVisitor {
  constructor() {
    super()
    this.globals = {}
  }

  visitVarDecl(node) {
    // TODO
  }

  visitType(node) {
    // TODO
  }

  visitCompound(node) {
    console.debug(`visitCompound -> `
      + `${node.childrens.map(s => s.getClassName()).join(', ')}`)
    for (const children of node.childrens) {
      this.visit(children)
    }
  }

  visitAssign(node) {
    console.debug(`visitAssign -> `
      + `${node.left.value} := ${node.right.getClassName()}`)
    this.globals[node.left.value] = this.visit(node.right)
  }

  visitVariable(node) {
    console.debug(`visitVariable -> ${node.value}`)
    if (node.token.value in this.globals) {
      return this.globals[node.token.value]
    }
    throw new ReferenceError(`variable name ${node.token.value} `
      + `is not defined`)
  }

  visitNop(node) {
    console.debug(`visitNop`)
  }

  visitNum(node) {
    console.debug(`visitNum -> ${node.value}`)
    return Number(node.value)
  }

  visitUnaryOperator(node) {
    console.debug(`visitUnaryOperator -> ${node.operator}`)
    return (node.operator === '+' ? 1 : -1)
      * Number(this.visit(node.value))
  }

  visitBinaryOperator(node) {
    let result
    console.debug(`visitBinaryOperator -> ${node.operator}`)
    switch (node.operator) {
      case '+':
        result = this.visit(node.left) + this.visit(node.right)
        break
      case '-':
        result = this.visit(node.left) - this.visit(node.right)
        break
      case '/': {
        let rval = this.visit(node.right)
        if (rval === 0) throw new Error('Divide by zero')

        result = this.visit(node.left) / rval
        break
      }
      case 'DIV': {
        let rval = this.visit(node.right)
        if (rval === 0) throw new Error('Divide by zero')

        result = this.visit(node.left) / rval
        break
      }
      case '*':
        result = this.visit(node.left) * this.visit(node.right)
        break
      default:
        throw new Error(`${node.operator} is not a valid operator`)
    }
    return result
  }

  execute(text) {
    try {
      var lexer = new Lexer(text)
    } catch (e) {
      console.error(`Tokenizing failure: ${e.message}`)
      console.debug(e)
      return
    }

    try {
      var parser = new Parser(lexer)
      var ast = parser.parse()
    } catch (e) {
      console.error(`Parsing failure: ${e.message}`)
      console.debug(e)
      return
    }
    return this.visit(ast)
  }
}


module.exports = {
  SymbolTableBuilder,
  Interpreter,
}
