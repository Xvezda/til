/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const { Base } = require('./common.js')
const { Lexer } = require('./lexer.js')
const { Parser } = require('./parser.js')


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


class AstVisitor extends TreeVisitor {
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


class Interpreter extends AstVisitor {
  constructor() {
    super()
  }

  visitInteger(node) {
    console.debug(`visitInteger -> ${node.value}`)
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
      case '*':
        result = this.visit(node.left) * this.visit(node.right)
        break
      default:
        throw new Error(`${node.operator} is not a valid operator`)
    }
    return result
  }

  // Process input line by line
  feedline(input) {
    return this.execute(input)
  }

  execute(text) {
    try {
      var lexer = new Lexer(text)
    } catch (e) {
      console.error(`Tokenizing failure: ${e.message}`)
      return
    }

    try {
      var parser = new Parser(lexer)
      var ast = parser.parse()
    } catch (e) {
      console.error(`Parsing failure: ${e.message}`)
      return
    }
    return this.visit(ast)
  }
}


module.exports = Interpreter
