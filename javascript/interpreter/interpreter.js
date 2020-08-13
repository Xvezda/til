/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const { Base, Stack } = require('./common.js')
const { Lexer } = require('./lexer.js')
const { Parser } = require('./parser.js')
const { ErrorCode, SemanticError } = require('./errors.js')


const PROGRAM = 'PROGRAM'
const PROCEDURE = 'PROCEDURE'
const ARType = {
  PROGRAM,
  PROCEDURE,
}

class ActivationRecord extends Base {
  constructor(name, type, nestingLevel) {
    super()
    this.name = name
    this.type = type
    this.nestingLevel = nestingLevel
    this.members = {}
  }

  set(key, value) {
    this.members[key] = value
  }

  get(key) {
    return this.members[key]
  }

  toString() {
    const lines = [`${this.nestingLevel}: ${this.type} ${this.name}`]
    for (const [k, v] of Object.entries(this.members)) {
      lines.push(`   ${k}: ${v}`)
    }
    return lines.join('\n') + '\n'
  }
}

class CallStack extends Stack {
  constructor() {
    super()
  }

  toString() {
    function banner(heading, char, count) {
      char = char || '='
      count = count || 3
      return char.repeat(count) + heading + char.repeat(count)
    }

    let output = banner(' CALLSTACK ') + '\n'
    output += this.items.reverse().join('\n') + '\n'
    output += banner(' END OF CALLSTACK ')

    return output
  }
}


class BaseSymbol extends Base {
  constructor(name, type) {
    super()
    this.name = name
    this.type = type
    this.scopeLevel = 0
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
    this.blockAst = null
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

  log(msg) {
    if (global.argv.scope) {
      console.info(msg)
    }
  }

  [initBuiltins]() {
    this.define(new BuiltinTypeSymbol('INTEGER'))
    this.define(new BuiltinTypeSymbol('REAL'))
  }

  define(symbol) {
    this.log('define:', symbol.name)
    // if (symbol.name in this.symbols)
    //   throw new SyntaxError(`Redefining symbol ${symbol.name}`)
    symbol.scopeLevel = this.scopeLevel
    this.symbols[symbol.name] = symbol
  }

  lookup(name, currentScopeOnly) {
    this.log(`lookup: ${name} (scope: ${this.scopeName})`)
    const symbol = this.symbols[name]
    if (symbol !== undefined) return symbol

    if (!!currentScopeOnly) return

    if (this.enclosingScope !== undefined) {
      return this.enclosingScope.lookup(name)
    }
  }

  toString() {
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
      throw new SemanticError(`${this.getClassName()} has no method ` +
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

  error(errorCode, token) {
    throw new SemanticError(`${errorCode}: ${token}`)
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

  visitProcCall(node) {
    console.debug(`visitProcCall -> ${node.procName}`)
    const procSymbol = this.currentScope.lookup(node.procName)
    const argsCount = procSymbol.params.length

    if (argsCount !== node.actualParams.length)
      throw new SemanticError()  // FIXME: Add error code

    for (const paramNode of node.actualParams) {
      this.visit(paramNode)
    }
    node.procSymbol = procSymbol
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

    // Define parameter variable symbols as procedure scope
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

    procSymbol.blockAst = node.blockNode
  }

  visitVarDecl(node) {
    console.debug('symbol table: visitVarDecl')
    console.debug(node)

    const typeName = node.typeNode.value
    const typeSymbol = this.currentScope.lookup(typeName)
    const varName = node.varNode.value
    const varSymbol = new VarSymbol(varName, typeSymbol)

    if (this.currentScope.lookup(varName, true) !== undefined)
      this.error(ErrorCode.DUPLICATE_ID, node.varNode.token)

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
      this.error(ErrorCode.ID_NOT_FOUND, node.token)
  }

  visitNop(node) {
    // TODO
  }

  visitNum(node) {
    console.debug(`visitNum -> ${node.value}`)
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
    console.debug(`visitBinaryOperator -> ${node.operator}`)
    this.visit(node.left)
    this.visit(node.right)
  }
}


class Interpreter extends AstVisitor {
  constructor(tree) {
    super()
    this.tree = tree
    this.callStack = new CallStack()
  }

  log(msg) {
    if (global.argv.stack) {
      console.info(msg)
    }
  }

  visitProgram(node) {
    const progName = node.name
    this.log(`ENTER: PROGRAM ${progName}`)
    const ar = new ActivationRecord(progName, ARType.PROGRAM, 1)
    this.callStack.push(ar)

    this.log(`${this.callStack}`)

    super.visitProgram(node)

    this.log(`LEAVE: PROGRAM ${progName}`)
    this.log(`${this.callStack}`)

    this.callStack.pop()
  }

  visitProcCall(node) {
    const procName = node.procName
    const procSymbol = node.procSymbol
    const ar = new ActivationRecord(procName,
      ARType.PROCEDURE,
      procSymbol.scopeLevel + 1)

    const formalParams = procSymbol.params
    const actualParams = node.actualParams

    for (let i = 0; i < formalParams.length; ++i) {
      // Evaluate and assign
      const paramSymbol = formalParams[i]
      const argumentNode = actualParams[i]
      ar.set(paramSymbol.name, this.visit(argumentNode))
    }
    // Put procedure activation record at the top of callstack
    this.callStack.push(ar)

    this.log(`ENTER: PROCEDURE ${procName}`)
    this.log(`${this.callStack}`)

    // Evaluate procedure body
    this.visit(procSymbol.blockAst)

    this.log(`LEAVE: PROCEDURE ${procName}`)
    this.log(`${this.callStack}`)

    // Restore callstack
    this.callStack.pop()
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
    // this.globals[node.left.value] = this.visit(node.right)
    const varName = node.left.value
    const varValue = this.visit(node.right)

    const ar = this.callStack.peek()
    ar.set(varName, varValue)
  }

  visitVariable(node) {
    console.debug(`visitVariable -> ${node.value}`)
    // if (node.token.value in this.globals) {
    //   return this.globals[node.token.value]
    // }
    const varName = node.value
    const ar = this.callStack.peek()
    const varValue = ar.get(varName)

    if (varValue !== undefined)
      return varValue

    // FIXME: Add error method
    return this.error(ErrorCode.ID_NOT_FOUND, node.token)
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

  visitProcCall(node) {
    // TODO
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
  CallStack,
  ARType,
  ActivationRecord,
  SemanticAnalyzer,
  Interpreter,
  Translator,
}
