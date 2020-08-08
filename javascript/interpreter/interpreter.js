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

  [util.inspect.custom]() {
    return this.toString()
  }
}


class BuiltinTypeSymbol extends BaseSymbol {
  constructor(name) {
    super(name)
  }

  toString() {
    return `[${this.getClassName()}(${this.name})]`
  }
}


class VarSymbol extends BaseSymbol {
  constructor(name, type) {
    super(name, type)
  }

  toString() {
    return `[${this.getClassName()}(name=${this.name}, type=${this.type})]`
  }
}


class ProcSymbol extends BaseSymbol {
  constructor(name, params) {
    super(name)
    this.params = params || []
  }

  toString() {
    return `[${this.getClassName()}(name=${this.name},
      params=${this.params.length > 0 ? this.params : '[]'})]`
  }
}


class ProgSymbol extends BaseSymbol {
  constructor(name) {
    super(name)
  }

  toString() {
    return `[${this.getClassName()}(name=${this.name})]`
  }
}


const initBuiltins = Symbol('initBuiltins')

class ScopedSymbolTable extends Base {
  constructor(scopeName, scopeLevel, enclosingScope) {
    super()
    this.symbols = {}
    this.scopeName = scopeName
    this.scopeLevel = scopeLevel
    this.enclosingScope = enclosingScope

    // this[initBuiltins]()
  }

  [initBuiltins]() {
    this.define(new BuiltinTypeSymbol('INTEGER'))
    this.define(new BuiltinTypeSymbol('REAL'))
  }

  define(symbol) {
    console.debug('define:', symbol.name)
    // if (symbol.name in this.symbols)
    //   throw new SyntaxError(`Redefining symbol ${symbol.name}`)
    this.symbols[symbol.name] = symbol
  }

  lookup(name, currentScopeOnly) {
    console.debug(`lookup: ${name} (scope: ${this.scopeName})`)
    const symbol = this.symbols[name]
    if (symbol !== undefined) return symbol

    if (!!currentScopeOnly) return

    if (this.enclosingScope !== undefined) {
      return this.enclosingScope.lookup(name)
    }
  }

  [util.inspect.custom]() {
    let lines = [
      `Scope name: ${this.scopeName}`,
      `Scope level: ${this.scopeLevel}`,
      `Enclosing scope: ${
        this.enclosingScope !== undefined
          ? this.enclosingScope.scopeName
          : 'None'
      }`
    ]
    Object.entries(this.symbols).forEach(([k, v]) => {
      lines.push(`${k}: ${v}`)
    })
    lines = lines.map(v => ' '.repeat(2) + v)
    return `{\n${lines.join('\n')}\n}`
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

    // console.debug(`visit -> ${visitorName}`)

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
      console.debug(`visitBlock -> ${declaration.getClassName()}`)
      this.visit(declaration)
    }
    this.visit(node.compoundStatement)
  }
}


class SemanticAnalyzer extends AstVisitor {
  constructor() {
    super()
    const globalScope = new ScopedSymbolTable('Global', 0)
    globalScope[initBuiltins]()
    this.currentScope = globalScope
  }

  visitProgram(node) {
    const progSymbol = new ProgSymbol(node.name)
    this.currentScope.define(progSymbol)

    console.debug(`visitProgram -> Entering scope ${node.name}`)

    const programScope =
      new ScopedSymbolTable(node.name,
        this.currentScope.scopeLevel + 1,
        this.currentScope)
    this.currentScope = programScope

    this.visit(node.block)

    console.debug(programScope)
    this.currentScope = this.currentScope.enclosingScope
    console.debug(`visitProgram -> Leaving scope ${node.name}`)
  }

  visitProcDecl(node) {
    const procSymbol = new ProcSymbol(node.procName)
    this.currentScope.define(procSymbol)

    console.debug(`visitProcDecl -> Entering scope ${node.procName}`)

    const procedureScope =
      new ScopedSymbolTable(node.procName,
        this.currentScope.scopeLevel + 1,
        this.currentScope)
    this.currentScope = procedureScope

    // Passing variables to parameter
    for (const param of node.params) {
      console.debug(`param:`, param)
      const paramName = param.varNode.value
      const paramType = this.currentScope.lookup(param.typeNode.value)
      const varSymbol = new VarSymbol(paramName, paramType)

      this.currentScope.define(varSymbol)
      procSymbol.params.push(varSymbol)
    }

    this.visit(node.blockNode)

    console.debug(procedureScope)
    this.currentScope = this.currentScope.enclosingScope
    console.debug(`visitProcDecl -> Leaving scope ${node.procName}`)
  }

  visitVarDecl(node) {
    console.debug('symbol table: visitVarDecl')
    console.debug(node)

    const typeName = node.typeNode.value
    const typeSymbol = this.currentScope.lookup(typeName)
    const varName = node.varNode.value
    const varSymbol = new VarSymbol(varName, typeSymbol)

    if (this.currentScope.lookup(varName, true) !== undefined)
      throw new SyntaxError(`Symbol name ${varName} already exists`)

    this.currentScope.define(varSymbol)
  }

  visitAssign(node) {
    console.debug(`symbol table: visitAssign(${node.left.value} := ?)`)
    /*
    const varName = node.left.value
    const varType = this.currentScope.lookup(varName)
    if (varType === undefined)
      throw new ReferenceError(`Variable name ${varName} not exists`)
      */
    this.visit(node.right)
    this.visit(node.left)
  }

  visitVariable(node) {
    console.debug(`symbol table: visitVariable -> ${node.value}`)
    const varName = node.value
    const varSymbol = this.currentScope.lookup(varName)
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
  constructor(tree) {
    super()
    this.tree = tree
    this.globals = {}
  }

  visitVarDecl(node) {
    // TODO
  }

  visitProcDecl(node) {
    console.debug(`visitProcDecl -> ${node.procName}`)
    // FIXME
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

  interpret() {
    if (!this.tree) return
    return this.visit(this.tree)
  }
}


class Translator extends SemanticAnalyzer {
  constructor(indent) {
    super()
    this.result = ''
    this.indent = indent || 4
  }

  append(text, prepend, adjust) {
    prepend = prepend || false
    adjust = adjust || 0
    if (prepend && !!this.currentScope) {
      this.result += ' '.repeat((this.currentScope.scopeLevel+adjust)
        * this.indent)
    }
    this.result += text
  }

  visitProgram(node) {
    this.append(`program ${node.name + this.currentScope.scopeLevel};\n`, true)

    super.visitProgram(node)

    this.append(`. {END OF ${node.name}}\n`)
  }

  visitCompound(node) {
    this.append('\n')
    this.append(`begin\n`, true, -1)

    super.visitCompound(node)

    this.append(`end`, true, -1)
  }

  visitVarDecl(node) {
    const varName = node.varNode.value + this.currentScope.scopeLevel
    this.append(`var ${varName} : ${node.typeNode.value};\n`, true)

    super.visitVarDecl(node)
  }

  visitProcDecl(node) {
    const procName = node.procName + this.currentScope.scopeLevel
    this.append(`procedure ${procName}`, true)

    if (node.params.length > 0) {
      this.append('(')
      const params = {}
      node.params.forEach(({varNode, typeNode}) => {
        const varName = varNode.value + (this.currentScope.scopeLevel+1)
        if (params[typeNode.value] !== undefined) {
          params[typeNode.value].push(varName)
        } else {
          params[typeNode.value] = [varName]
        }
      })
      const groups = []
      Object.entries(params).forEach(([k, v]) => {
        groups.push(v.join(', ') + ' : ' + k)
      })
      this.append(groups.join('; '))
      this.append(')')
    }
    this.append(';\n')

    super.visitProcDecl(node)

    this.append(`; {END OF ${node.procName}}\n`)
  }

  visitAssign(node) {
    this.append(`${this.visit(node.left)} := ${this.visit(node.right)};\n`, true)
    super.visitAssign(node)
  }

  visitVariable(node) {
    const varNode = this.currentScope.lookup(node.value)
    let scope = this.currentScope
    while (scope && !(node.value in scope.symbols)) {
      scope = scope.enclosingScope
    }
    super.visitVariable(node)

    const varName = varNode.name + scope.scopeLevel
    const typeName = varNode.type.name

    return `<${varName}:${typeName}>`
  }

  visitBinaryOperator(node) {
    super.visitBinaryOperator(node)
    return `${this.visit(node.left)} ${node.operator} ${this.visit(node.right)}`
  }
}


module.exports = {
  SemanticAnalyzer,
  Interpreter,
  Translator,
}
