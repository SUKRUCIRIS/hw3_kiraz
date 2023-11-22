%{
#include <kiraz/stmt.h>
#include <kiraz/hw2-lexer.hpp>

using namespace kiraz;
using kiraz::Stmt;
using kiraz::Token;
int yyerror(const char *s);

#define YYSTYPE std::shared_ptr<Stmt>
#define YYDEBUG 1
%}

%token    IDENTIFIER

// Operators
%token    OP_RETURNS
%token    OP_EQUALS
%token    OP_ASSIGN
%token    OP_GT
%token    OP_LT
%token    OP_GE
%token    OP_LE
%token    OP_LPAREN
%token    OP_RPAREN
%token    OP_LBRACE
%token    OP_RBRACE
%token    OP_COLON
%token    OP_PLUS
%token    OP_MINUS
%token    OP_MULT
%token    OP_DIVF
%token    OP_COMMA
%token    OP_NEWLINE
%token    OP_SCOLON
%token    OP_DOT
%token    OP_NOT

// Literals
%token    L_INTEGER
%token    L_STRING
%token    L_BOOLEAN

// Keywords
%token    KW_IF
%token    KW_FUNC
%token    KW_WHILE
%token    KW_CLASS
%token    KW_IMPORT

%left OP_PLUS OP_MINUS
%left OP_MULT OP_DIVF

%%

stmtlist
    : stmtlist stmt OP_NEWLINE
    | stmtlist stmt OP_SCOLON
    |          stmt OP_NEWLINE
    |          stmt OP_SCOLON
    ;

stmt
    : OP_LPAREN stmt OP_RPAREN { $$ = $2; }
    | addsub
    ;

addsub
    : muldiv
    | stmt OP_PLUS  stmt { $$ = Stmt::add<stmt::OpAdd>($1, $3); }
    | stmt OP_MINUS stmt { $$ = Stmt::add<stmt::OpSub>($1, $3); }
    ;

muldiv
    : posneg
    | stmt OP_MULT stmt { $$ = Stmt::add<stmt::OpMult>($1, $3); }
    | stmt OP_DIVF stmt { $$ = Stmt::add<stmt::OpDivF>($1, $3); }
    ;

posneg
    : OP_PLUS  literal { $$ = Stmt::add<stmt::SignedStmt>(token::OP_PLUS, $2); }
    | OP_MINUS literal { $$ = Stmt::add<stmt::SignedStmt>(token::OP_MINUS, $2); }
    | literal
    ;

literal
    : L_INTEGER { $$ = Stmt::add<stmt::Integer>(Token::last()); }
    ;

%%

int yyerror(const char *s) {
    fmt::print("** Parser Error at {}:{} at token: {}\n",
        yylineno, colno, Token::last().get_repr());
    colno = 0;
    Stmt::reset_root();
    return 1;
}
