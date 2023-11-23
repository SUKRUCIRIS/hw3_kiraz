#ifndef KIRAZ_STMT_OPERATOR_H
#define KIRAZ_STMT_OPERATOR_H

#include <kiraz/stmt/Base.h>

namespace kiraz {
namespace stmt {

class OpBinary : public Stmt {
protected:
    explicit OpBinary(token::Id op, const Stmt::Ptr &left, const Stmt::Ptr &right)
            : m_op(op), m_left(left), m_right(right) {
        assert(left);
        assert(right);
    }

public:
    auto get_op() const { return m_op; }
    auto get_left() const { return m_left; }
    auto get_right() const { return m_right; }

    std::string get_repr() const override {
        return fmt::format("{}(l={}, r={})", get_op(), *get_left(), *get_right());
    }

private:
    token::Id m_op;
    Stmt::Ptr m_left, m_right;
};

class OpAdd : public OpBinary {
public:
    OpAdd(const Stmt::Ptr &left, const Stmt::Ptr &right) : OpBinary(token::OP_PLUS, left, right) {}
};

class OpSub : public OpBinary {
public:
    OpSub(const Stmt::Ptr &left, const Stmt::Ptr &right) : OpBinary(token::OP_MINUS, left, right) {}
};

class OpMult : public OpBinary {
public:
    OpMult(const Stmt::Ptr &left, const Stmt::Ptr &right) : OpBinary(token::OP_MULT, left, right) {}
};

class OpDivF : public OpBinary {
public:
    OpDivF(const Stmt::Ptr &left, const Stmt::Ptr &right) : OpBinary(token::OP_DIVF, left, right) {}
};

class OpAss : public OpBinary {
public:
    OpAss(const Stmt::Ptr &left, const Stmt::Ptr &right)
            : OpBinary(token::OP_ASSIGN, left, right) {}
};

} // namespace stmt
} // namespace kiraz

#endif
