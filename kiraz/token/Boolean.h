#ifndef KIRAZ_TOKEN_BOOLEAN_H
#define KIRAZ_TOKEN_BOOLEAN_H

#include <kiraz/token/Base.h>

namespace kiraz {
namespace token {

class Boolean : public Token {
public:
    explicit Boolean(bool value) : m_value(value) {}
    auto get_value() const { return m_value; }

    // Token interface
    token::Id get_id() const override { return L_BOOLEAN; }
    std::string get_repr() const override { return fmt::format("{}({})", get_id(), get_value()); }

private:
    bool m_value;
};

} // namespace kiraz::token
} // namespace kiraz
#endif
