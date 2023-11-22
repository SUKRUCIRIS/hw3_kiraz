#ifndef KIRAZ_TOKEN_IDENTIFIER_H
#define KIRAZ_TOKEN_IDENTIFIER_H

#include <kiraz/token/Base.h>

namespace kiraz {
namespace token {

class Identifier: public Token {
public:
    Identifier(const std::string &text) : m_value(text) {}

    auto get_value() const { return m_value; }

    // Token interface
    Id get_id() const override { return IDENTIFIER; }
    std::string get_repr() const override { return fmt::format("{}({})", get_id(), get_value()); }

private:
    std::string m_value;
};
}
}
#endif // REJECTED_H
