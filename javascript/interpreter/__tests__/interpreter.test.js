const { Lexer } = require('../lexer.js')
const { Parser } = require('../parser.js')
const {
  SemanticAnalyzer,
  Interpreter,
  Translator
} = require('../interpreter.js')


describe('SemanticAnalyzer', () => {
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
    const semanticAnalyzer = new SemanticAnalyzer()
    console.log('before visit:', semanticAnalyzer.symbolTable)

    semanticAnalyzer.visit(ast)
    console.log('after visit:', semanticAnalyzer.symbolTable)
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
    let semanticAnalyzer = new SemanticAnalyzer()

    expect(() => {
      semanticAnalyzer.visit(ast)
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
    semanticAnalyzer = new SemanticAnalyzer()

    expect(() => {
      semanticAnalyzer.visit(ast)
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
    let semanticAnalyzer = new SemanticAnalyzer()

    semanticAnalyzer.visit(ast)
    console.log(semanticAnalyzer)

    let interpreter = new Interpreter(ast)
    interpreter.interpret()
    console.log(interpreter)
  })

  test('check duplicated identifier', () => {
    let text = `
    program SymTab6;
       var x, y : integer;
       var y : real;
    begin
       x := x + y;
    end.
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()
    let semanticAnalyzer = new SemanticAnalyzer()

    expect(() => {
      semanticAnalyzer.visit(ast)
    }).toThrow(SyntaxError)
  })

  test('procedure formal parameter declarations', () => {
    let text = `
    program Main;
       var x, y: real;

       procedure Alpha(a : integer);
          var y : integer;
       begin
          x := a + x + y;
       end;

    begin { Main }

    end.  { Main }
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()

    console.log(ast)
  })

  test('procedure scope', () => {
    let text = `
    program Main;
       var x, y: real;

       procedure Alpha(a : integer);
          var y : integer;
       begin

       end;

    begin { Main }

    end.  { Main }
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()
    console.log(ast)
    let semanticAnalyzer = new SemanticAnalyzer()

    semanticAnalyzer.visit(ast)
    console.log(semanticAnalyzer)
  })

  test('nested procedures', () => {
    let text = `
    program Main;
       var x, y : real;

       procedure AlphaA(a : integer);
          var y : integer;
       begin { AlphaA }

       end;  { AlphaA }

       procedure AlphaB(a : integer);
          var b : integer;
       begin { AlphaB }

       end;  { AlphaB }

    begin { Main }

    end.  { Main }
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()
    console.log(ast)
    let semanticAnalyzer = new SemanticAnalyzer()

    semanticAnalyzer.visit(ast)
    console.log(semanticAnalyzer)
  })

  test(`nested procedure's name resolution`, () => {
    let text = `
    program Main;
       var x, y: real;

       procedure Alpha(a : integer);
          var y : integer;
       begin
          x := a + x + y;
       end;

    begin { Main }

    end.  { Main }
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()
    console.log(ast)
    let semanticAnalyzer = new SemanticAnalyzer()

    semanticAnalyzer.visit(ast)
    console.log(semanticAnalyzer)
  })

  test('name resolution error', () => {
    let text = `
    program Main;
       var x, y: real;

       procedure Alpha(a : integer);
          var y : integer;
       begin
          x := b + x + y; { ERROR here! }
       end;

    begin { Main }

    end.  { Main }
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()
    console.log(ast)
    let semanticAnalyzer = new SemanticAnalyzer()

    expect(() => {
      semanticAnalyzer.visit(ast)
    }).toThrow(ReferenceError)
  })


  test('source to source translator', () => {
    let text = `
    program Main;
       var x, y : real;
       var z : integer;

       procedure AlphaA(a : integer);
          var y : integer;
       begin { AlphaA }
          x := a + x + y;
       end;  { AlphaA }

       procedure AlphaB(a : integer);
          var b : integer;
       begin { AlphaB }
       end;  { AlphaB }

    begin { Main }
    end.  { Main }
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()
    let translator = new Translator()

    translator.visit(ast)
    console.log(translator.result)
  })

  test('translate nested procedure', () => {
    let text = `
    program Main;
       var b, x, y : real;
       var z : integer;

       procedure AlphaA(a : integer);
          var b : integer;

          procedure Beta(c : integer);
             var y : integer;

             procedure Gamma(c : integer);
                var x : integer;
             begin { Gamma }
                x := a + b + c + x + y + z;
             end;  { Gamma }

          begin { Beta }

          end;  { Beta }

       begin { AlphaA }

       end;  { AlphaA }

       procedure AlphaB(a : integer);
          var c : real;
       begin { AlphaB }
          c := a + b;
       end;  { AlphaB }

    begin { Main }
    end.  { Main }
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()
    let translator = new Translator()

    translator.visit(ast)
    console.log(translator.result)
  })

  test('parameter duplicated identifier', () => {
    let text = `
    program Main;
       var x, y: real;

       procedure Alpha(a : integer);
          var y : integer;
          var a : real;  { ERROR here! }
       begin
          x := a + x + y;
       end;

    begin { Main }

    end.  { Main }
    `
    let parser = new Parser(new Lexer(text))
    let ast = parser.parse()
    let semanticAnalyzer = new SemanticAnalyzer()

    expect(() => {
      semanticAnalyzer.visit(ast)
    }).toThrow(SyntaxError)
  })
})
