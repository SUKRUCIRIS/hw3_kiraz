
#include "Base.h"

namespace kiraz {
std::vector<std::unique_ptr<Token>> Token::s_tokens;
int colno;
Token::~Token() {}
}
