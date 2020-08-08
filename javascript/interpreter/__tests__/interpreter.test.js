const { Lexer } = require('../lexer.js')
const { Parser } = require('../parser.js')
const { SymbolTableBuilder, Interpreter } = require('../interpreter.js')


describe('SymbolTableBuilder', () => {
  test('build symbol table', () => {
    const text = `
    PROGRAM Part11;
    VAR
      x : INTEGER;
      y : REAL;

    BEGIN

    END.
    `
    const lexer = new Lexer(text)
    const parser = new Parser(lexer)
    const ast = parser.parse()
    const symtabBuilder = new SymbolTableBuilder()
    console.log('before visit:', symtabBuilder.symbolTable)

    symtabBuilder.visit(ast)
    console.log('after visit:', symtabBuilder.symbolTable)
  })

  test('verify symbol', () => {
    let text = `
    PROGRAM NameError1;
    VAR
       a : INTEGER;

    BEGIN
       a := 2 + b;
    END.
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()
    let symtabBuilder = new SymbolTableBuilder()

    expect(() => {
      symtabBuilder.visit(ast)
    }).toThrow(ReferenceError)

    text = `
    PROGRAM NameError2;
    VAR
       b : INTEGER;

    BEGIN
       b := 1;
       a := b + 2;
    END.
    `
    parser = new Parser(new Lexer(text))
    ast = parser.parse()
    symtabBuilder = new SymbolTableBuilder()

    expect(() => {
      symtabBuilder.visit(ast)
    }).toThrow(ReferenceError)
  })

  test('procedure declaration', () => {
    let text = `
    PROGRAM Part12;
    VAR
       a : INTEGER;

    PROCEDURE P1;
    VAR
       a : REAL;
       k : INTEGER;

       PROCEDURE P2;
       VAR
          a, z : INTEGER;
       BEGIN {P2}
          z := 777;
       END;  {P2}

    BEGIN {P1}

    END;  {P1}

    BEGIN {Part12}
       a := 10;
    END.  {Part12}
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()
    let symtabBuilder = new SymbolTableBuilder()

    symtabBuilder.visit(ast)
    console.log(symtabBuilder)

    let interpreter = new Interpreter(ast)
    interpreter.interpret()
    console.log(interpreter)
  })
})
