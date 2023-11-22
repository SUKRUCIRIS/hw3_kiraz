#ifndef KIRAZ_TOKEN_REJECTED_H
#define KIRAZ_TOKEN_REJECTED_H

#include <kiraz/token/Base.h>

namespace kiraz {
namespace token {

class Rejected : public Token {
public:
    Rejected(const std::string &text) : m_text(text) {}

    // Token interface
    Id get_id() const override { return REJECTED; }
    std::string get_repr() const override { return fmt::format("Rejected('{}')", m_text); }

private:
    std::string m_text;
};
}
}
#endif // REJECTED_H
