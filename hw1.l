
%{
#include <kiraz/token.h>
using namespace kiraz::token;
using kiraz::Token;
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

KW_IMPORT  import
KW_FUNC    func
KW_IF      if
KW_WHILE   while
KW_CLASS   class

LC_DEC     [0-9]
LC_HEX     [0-9A-Fa-f]

IDENTIFIER [a-zA-Z_][0-9a-zA-Z_]*
IGNORED    [ \t]

%%

{KW_IMPORT}     { return Token::feed(KeywordImport()); }
{KW_FUNC}       { return Token::feed(KeywordFunc()); }
{KW_IF}         { return Token::feed(KeywordIf()); }
{KW_WHILE}      { return Token::feed(KeywordWhile()); }
{KW_CLASS}      { return Token::feed(KeywordClass()); }

\"[^\"]+\"      { return Token::feed(String(yytext)); }

{OP_RETURNS}    { return Token::feed(OperatorReturns()); }
{OP_EQUALS}     { return Token::feed(OperatorEquals()); }
{OP_ASSIGN}     { return Token::feed(OperatorAssign()); }
{OP_GT}         { return Token::feed(OperatorGt()); }
{OP_LT}         { return Token::feed(OperatorLt()); }
{OP_GE}         { return Token::feed(OperatorGe()); }
{OP_LE}         { return Token::feed(OperatorLe()); }
{OP_LPAREN}     { return Token::feed(OperatorLParen()); }
{OP_RPAREN}     { return Token::feed(OperatorRParen()); }
{OP_LBRACE}     { return Token::feed(OperatorLBrace()); }
{OP_RBRACE}     { return Token::feed(OperatorRBrace()); }
{OP_PLUS}       { return Token::feed(OperatorPlus()); }
{OP_MINUS}      { return Token::feed(OperatorMinus()); }
{OP_MULT}       { return Token::feed(OperatorMult()); }
{OP_DIVF}       { return Token::feed(OperatorDivF()); }
{OP_COMMA}      { return Token::feed(OperatorComma()); }
{OP_NEWLINE}+   { return Token::feed(OperatorNewline()); }
{OP_COLON}      { return Token::feed(OperatorColon()); }
{OP_SCOLON}+    { return Token::feed(OperatorScolon()); }
{OP_DOT}        { return Token::feed(OperatorDot()); }

{IDENTIFIER}    { return Token::feed(Identifier(yytext)); }
{LC_DEC}+       { return Token::feed(Integer(10, yytext)); }

{IGNORED}+      { return -1; }
.               { return Token::feed(Rejected(yytext)); }
