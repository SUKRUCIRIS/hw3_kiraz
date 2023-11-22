
%{
#include <kiraz/token.h>
using namespace kiraz::token;
using kiraz::Token;
using kiraz::colno;
%}

OP_RETURNS ->
OP_EQUALS  ==
OP_ASSIGN  =
OP_GT      >
OP_LT      <
OP_GE      >=
OP_LE      <=
OP_LPAREN  \(
OP_RPAREN  \)
OP_LBRACE  \{
OP_RBRACE  \}
OP_PLUS    \+
OP_MINUS   \-
OP_MULT    \*
OP_DIVF    \/
OP_COMMA   ,
OP_NEWLINE \n
OP_COLON   :
OP_SCOLON  ;
OP_DOT     \.
OP_NOT     !

KW_IMPORT  import
KW_FUNC    func
KW_IF      if
KW_WHILE   while
KW_CLASS   class

LC_DEC     [0-9]
LC_HEX     [0-9A-Fa-f]
LC_TRUE    true
LC_FALSE   false

IDENTIFIER [a-zA-Z_][0-9a-zA-Z_]*
IGNORED    [ \t]

%%

{KW_IMPORT}     { colno += yyleng; return Token::feed(KeywordImport()); }
{KW_FUNC}       { colno += yyleng; return Token::feed(KeywordFunc()); }
{KW_IF}         { colno += yyleng; return Token::feed(KeywordIf()); }
{KW_WHILE}      { colno += yyleng; return Token::feed(KeywordWhile()); }
{KW_CLASS}      { colno += yyleng; return Token::feed(KeywordClass()); }
{LC_TRUE}       { colno += yyleng; return Token::feed(Boolean(true)); }
{LC_FALSE}      { colno += yyleng; return Token::feed(Boolean(false)); }

{LC_DEC}+       { colno += yyleng; return Token::feed(Integer(10, yytext)); }
0x{LC_HEX}+     { colno += yyleng; return Token::feed(Integer(16, yytext)); }
\"[^\"]+\"      { colno += yyleng; return Token::feed(String(yytext)); }

{OP_RETURNS}    { colno += yyleng; return Token::feed(OperatorReturns()); }
{OP_EQUALS}     { colno += yyleng; return Token::feed(OperatorEquals()); }
{OP_ASSIGN}     { colno += yyleng; return Token::feed(OperatorAssign()); }
{OP_GT}         { colno += yyleng; return Token::feed(OperatorGt()); }
{OP_LT}         { colno += yyleng; return Token::feed(OperatorLt()); }
{OP_GE}         { colno += yyleng; return Token::feed(OperatorGe()); }
{OP_LE}         { colno += yyleng; return Token::feed(OperatorLe()); }
{OP_LPAREN}     { colno += yyleng; return Token::feed(OperatorLParen()); }
{OP_RPAREN}     { colno += yyleng; return Token::feed(OperatorRParen()); }
{OP_LBRACE}     { colno += yyleng; return Token::feed(OperatorLBrace()); }
{OP_RBRACE}     { colno += yyleng; return Token::feed(OperatorRBrace()); }
{OP_PLUS}       { colno += yyleng; return Token::feed(OperatorPlus()); }
{OP_MINUS}      { colno += yyleng; return Token::feed(OperatorMinus()); }
{OP_MULT}       { colno += yyleng; return Token::feed(OperatorMult()); }
{OP_DIVF}       { colno += yyleng; return Token::feed(OperatorDivF()); }
{OP_COMMA}      { colno += yyleng; return Token::feed(OperatorComma()); }
{OP_NEWLINE}+   { colno = 0;       return Token::feed(OperatorNewline()); }
{OP_COLON}      { colno += yyleng; return Token::feed(OperatorColon()); }
{OP_SCOLON}+    { colno += yyleng; return Token::feed(OperatorScolon()); }
{OP_DOT}        { colno += yyleng; return Token::feed(OperatorDot()); }
{OP_NOT}        { colno += yyleng; return Token::feed(OperatorNot()); }

{IDENTIFIER}    { colno += yyleng; return Token::feed(Identifier(yytext)); }

{IGNORED}+      { colno += yyleng; }
.               { return Token::feed(Rejected(yytext)); }
