#ifndef KIRAZ_STMT_LITERAL_H
#define KIRAZ_STMT_LITERAL_H

#include <kiraz/stmt/Base.h>

namespace kiraz {
namespace stmt {
class Identifier : public Stmt {
public:
    Identifier(const std::string &name) : m_name(name) {}
    Identifier(const Token &t) {
        assert(t.get_id() == token::IDENTIFIER);

        const auto &ti = static_cast<const token::Identifier &>(t);
        m_name = ti.get_value();
    }

    template <typename T>
    static auto New(const T &name) {
        return std::make_shared<Identifier>(name);
    }

    auto get_name() const { return m_name; }
    std::string get_repr() const override { return fmt::format("Id({})", get_name()); }

private:
    std::string m_name;
};

class Integer : public Stmt {
public:
    Integer(int base, const std::string &value) : m_base(base), m_value(value) {}
    Integer(const Token &t) {
        assert(t.get_id() == token::L_INTEGER);

        const auto &ti = static_cast<const token::Integer &>(t);
        m_base = ti.get_base();
        m_value = ti.get_value();
    }

    static auto New(int base, const std::string &value) {
        return std::make_shared<Integer>(base, value);
    }

    auto get_base() const { return m_base; }
    auto get_value() const { return m_value; }

    std::string get_repr() const override {
        return fmt::format("Int({}, {})", get_base(), get_value());
    }

private:
    int m_base;
    std::string m_value;
};

class SignedStmt : public Stmt {
public:
    SignedStmt(token::Id sign, Stmt::Ptr stmt) : m_sign(sign), m_stmt(stmt) { assert(stmt); }

    auto get_sign() const { return m_sign; }
    auto get_stmt() const { return m_stmt; }

    std::string get_repr() const override {
        return fmt::format("Signed({}, {})", get_sign(), *get_stmt());
    }

private:
    token::Id m_sign;
    Stmt::Ptr m_stmt;
};
} // namespace stmt
} // namespace kiraz

#endif
