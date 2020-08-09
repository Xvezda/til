const { Lexer } = require('../lexer.js')
const { Parser } = require('../parser.js')
const {
  SemanticAnalyzer,
  Interpreter,
  Translator
} = require('../interpreter.js')
const {
  ErrorCode,
  LexerError,
  ParserError,
  SemanticError
} = require('../errors.js')


describe('SemanticAnalyzer', () => {
  function buildAst(source) {
    const lexer = new Lexer(source)
    const parser = new Parser(lexer)
    return parser.parse()
  }

  function semanticAnalysis(ast) {
    const semanticAnalyzer = new SemanticAnalyzer()
    semanticAnalyzer.visit(ast)

    return semanticAnalyzer
  }

  function translate(ast) {
    const translator = new Translator()
    translator.visit(ast)

    return translator.result
  }

  beforeAll(() => {
    // jest.spyOn(console, 'debug').mockImplementation(jest.fn())
    // jest.spyOn(console, 'info').mockImplementation(jest.fn())
  })

  test('build symbol table', () => {
    const text = `
    PROGRAM Part11;
    VAR
      x : INTEGER;
      y : REAL;

    BEGIN

    END.
    `
    const ast = buildAst(text)

    expect(() => {
      semanticAnalysis(ast)
    }).not.toThrow()
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
    const ast = buildAst(text)

    expect(() => {
      semanticAnalysis(ast)
    }).toThrow(ErrorCode.ID_NOT_FOUND)

    text = `
    PROGRAM NameError2;
    VAR
       b : INTEGER;

    BEGIN
       b := 1;
       a := b + 2;
    END.
    `
    expect(() => {
      semanticAnalysis(buildAst(text))
    }).toThrow(ErrorCode.ID_NOT_FOUND)
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
    let ast = buildAst(text)
    expect(() => {
      semanticAnalysis(ast)
    }).not.toThrow()

    let interpreter = new Interpreter(ast)
    expect(() => {
      interpreter.interpret()
    }).not.toThrow()
    console.info(interpreter)
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
    let ast = buildAst(text)

    expect(() => {
      semanticAnalysis(ast)
    }).toThrow(ErrorCode.DUPLICATE_ID)
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
    expect(() => {
      console.info(buildAst(text))
    }).not.toThrow()
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
    let ast = buildAst(text)
    console.info(ast)

    expect(() => {
      semanticAnalysis(ast)
    }).not.toThrow()
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
    let ast = buildAst(text)

    expect(() => {
      semanticAnalysis(ast)
    }).not.toThrow()
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
    let ast = buildAst(text)
    console.info(ast)

    let result
    expect(() => {
      console.info(semanticAnalysis(ast))
    }).not.toThrow()
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
    let ast = buildAst(text)

    expect(() => {
      semanticAnalysis(ast)
    }).toThrow(ErrorCode.ID_NOT_FOUND)
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
    expect(() => {
      console.info(translate(buildAst(text)))
    }).not.toThrow()
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
    expect(() => {
      console.info(translate(buildAst(text)))
    }).not.toThrow()
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
    expect(() => {
      semanticAnalysis(buildAst(text))
    }).toThrow(ErrorCode.DUPLICATE_ID)
  })

  test('assignment nestedscopes04', () => {
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
    expect(() => {
      console.info(translate(buildAst(text)))
    }).not.toThrow()
  })

  test('procedure call', () => {
    let text = `
    program Main;

    procedure Alpha(a : integer; b : integer);
    var x : integer;
    begin
       x := (a + b ) * 2;
    end;

    begin { Main }

       Alpha(3 + 5, 7);  { procedure call }

    end.  { Main }
    `
    console.info(semanticAnalysis(buildAst(text)))
  })
})
