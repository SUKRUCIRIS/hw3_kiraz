#ifndef KIRAZ_TOKEN_STRING_H
#define KIRAZ_TOKEN_STRING_H

#include <kiraz/token/Base.h>

namespace kiraz {
namespace token {

class String : public Token {
public:
    String(std::string_view yytext) : m_value(yytext.data() + 1, yytext.size() - 2) {
        assert(yytext.size() >= 2);
    }

    auto get_value() const { return m_value; }

    // Token interface
    token::Id get_id() const override { return L_STRING; }
    std::string get_repr() const override {
        return fmt::format("{}(\"{}\")", get_id(), get_value());
    }

private:
    std::string m_value;
};

} // namespace kiraz::token
} // namespace kiraz
#endif
