#ifndef KIRAZ_TOKEN_OPERATOR_H
#define KIRAZ_TOKEN_OPERATOR_H

#include <kiraz/token/Base.h>

namespace kiraz {
namespace token {

class Operator : public Token {
protected:
    Operator(token::Id type) : m_type(type) {}

public:
    // Token interface
    Id get_id() const override { return m_type; }

protected:
    token::Id m_type;
};

class OperatorReturns : public Operator {
public:
    OperatorReturns() : Operator(OP_RETURNS) {}
};

class OperatorEquals : public Operator {
public:
    OperatorEquals() : Operator(OP_EQUALS) {}
};

class OperatorAssign : public Operator {
public:
    OperatorAssign() : Operator(OP_ASSIGN) {}
};

class OperatorGt : public Operator {
public:
    OperatorGt() : Operator(OP_GT) {}
};

class OperatorLt : public Operator {
public:
    OperatorLt() : Operator(OP_LT) {}
};

class OperatorGe : public Operator {
public:
    OperatorGe() : Operator(OP_GE) {}
};

class OperatorLe : public Operator {
public:
    OperatorLe() : Operator(OP_LE) {}
};

class OperatorLParen : public Operator {
public:
    OperatorLParen() : Operator(OP_LPAREN) {}
};

class OperatorRParen : public Operator {
public:
    OperatorRParen() : Operator(OP_RPAREN) {}
};

class OperatorLBrace : public Operator {
public:
    OperatorLBrace() : Operator(OP_LBRACE) {}
};

class OperatorRBrace : public Operator {
public:
    OperatorRBrace() : Operator(OP_RBRACE) {}
};

class OperatorPlus : public Operator {
public:
    OperatorPlus() : Operator(OP_PLUS) {}
};

class OperatorMinus : public Operator {
public:
    OperatorMinus() : Operator(OP_MINUS) {}
};

class OperatorMult : public Operator {
public:
    OperatorMult() : Operator(OP_MULT) {}
};

class OperatorDivF : public Operator {
public:
    OperatorDivF() : Operator(OP_DIVF) {}
};

class OperatorComma : public Operator {
public:
    OperatorComma() : Operator(OP_COMMA) {}
};

class OperatorNewline : public Operator {
public:
    OperatorNewline() : Operator(OP_NEWLINE) {}
};

class OperatorColon : public Operator {
public:
    OperatorColon() : Operator(OP_COLON) {}
};

class OperatorScolon : public Operator {
public:
    OperatorScolon() : Operator(OP_SCOLON) {}
};

class OperatorDot : public Operator {
public:
    OperatorDot() : Operator(OP_DOT) {}
};

class OperatorNot : public Operator {
public:
    OperatorNot() : Operator(OP_NOT) {}
};

}
}
#endif // REJECTED_H
