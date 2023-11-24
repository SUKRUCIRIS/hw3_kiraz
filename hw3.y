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
%token    KW_LET

%left OP_PLUS OP_MINUS
%left OP_MULT OP_DIVF

%%

input
	: lines
	| %empty
	;

func
	: KW_FUNC iden OP_LPAREN func_args OP_RPAREN OP_COLON iden OP_LBRACE func_lines OP_RBRACE { 
		$$ = Stmt::add<stmt::KeyFunc>($2, $4, $7, $9); }
	| KW_FUNC iden OP_LPAREN func_args OP_RPAREN OP_COLON iden OP_LBRACE OP_RBRACE { 
		$$ = Stmt::add<stmt::KeyFunc>($2, $4, $7, nullptr); }
	| KW_FUNC iden OP_LPAREN OP_RPAREN OP_COLON iden OP_LBRACE OP_RBRACE { 
		$$ = Stmt::add<stmt::KeyFunc>($2, nullptr, $6, nullptr); }
	| KW_FUNC iden OP_LPAREN OP_RPAREN OP_COLON iden OP_LBRACE func_lines OP_RBRACE { 
		$$ = Stmt::add<stmt::KeyFunc>($2, nullptr, $6, $8); }
	;

func_args
	: iden OP_COLON iden { 
		auto y= stmt::funcargs(); 
		$$.reset(y.push_iden($1,$3)); }
	| func_args OP_COMMA iden OP_COLON iden {
		stmt::funcargs* x=(stmt::funcargs*)$1.get();
		$$.reset(x->push_iden($3,$5)); }
	;

func_lines
    : func_lines line OP_NEWLINE {
		stmt::lines* x=(stmt::lines*)$1.get();
		$$.reset(x->push_line($2)); }
    | func_lines line OP_SCOLON {
		stmt::lines* x=(stmt::lines*)$1.get();
		$$.reset(x->push_line($2)); }
    |       line OP_NEWLINE {
		auto x=stmt::lines();
		$$.reset(x.push_line($1)); }
    |       line OP_SCOLON	{
		auto x=stmt::lines();
		$$.reset(x.push_line($1)); }
    ;

lines
    : lines line OP_NEWLINE
    | lines line OP_SCOLON
    |       line OP_NEWLINE
    |       line OP_SCOLON	
	| 		func OP_SCOLON
	| 		func OP_NEWLINE
	| lines	func OP_SCOLON
	| lines	func OP_NEWLINE
	| 		func
	| lines func
    ;

let
	: KW_LET iden OP_ASSIGN literal { $$ = Stmt::add<stmt::KeyLet>(nullptr, $2, $4); }
	| KW_LET iden OP_ASSIGN OP_PLUS literal { $$ = Stmt::add<stmt::KeyLet>(nullptr, $2, $5); }
	| KW_LET iden OP_ASSIGN OP_MINUS literal {
		$$ = Stmt::add<stmt::KeyLet>(nullptr, $2, Stmt::add<stmt::SignedStmt>(token::OP_MINUS, $5)); }
	| KW_LET iden OP_COLON iden { $$ = Stmt::add<stmt::KeyLet>($4, $2, nullptr); }
	| KW_LET iden OP_COLON iden OP_ASSIGN stmt { $$ = Stmt::add<stmt::KeyLet>($4, $2, $6); }
	;

line
	: stmt
	| iden OP_ASSIGN stmt { $$ = Stmt::add<stmt::OpAss>($1, $3); }
	| let
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
    : OP_PLUS  stmt { $$ = Stmt::add<stmt::SignedStmt>(token::OP_PLUS, $2); }
    | OP_MINUS stmt { $$ = Stmt::add<stmt::SignedStmt>(token::OP_MINUS, $2); }
    | literal
	| iden
    ;

literal
    : L_INTEGER { $$ = Stmt::add<stmt::Integer>(Token::last()); }
    ;

iden
	: IDENTIFIER { $$ = Stmt::add<stmt::Identifier>(Token::last()); }
	;

%%

int yyerror(const char *s) {
    fmt::print("** Parser Error at {}:{} at token: {}\n",
        yylineno, colno, Token::last().get_repr());
    colno = 0;
    Stmt::reset_root();
    return 1;
}
