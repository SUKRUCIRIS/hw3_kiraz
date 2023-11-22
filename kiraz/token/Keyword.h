#ifndef KIRAZ_TOKEN_KEYWORD_H
#define KIRAZ_TOKEN_KEYWORD_H

#include <kiraz/token/Base.h>

namespace kiraz {
namespace token {

class Keyword : public Token {
protected:
    Keyword(token::Id type) : m_type(type) {}

public:
    // Token interface
    Id get_id() const override { return m_type; }

protected:
    token::Id m_type;
};

class KeywordImport : public Keyword {
public:
    KeywordImport() : Keyword(KW_IMPORT) {}
};

class KeywordFunc : public Keyword {
public:
    KeywordFunc() : Keyword(KW_FUNC) {}
};

class KeywordIf : public Keyword {
public:
    KeywordIf() : Keyword(KW_IF) {}
};

class KeywordWhile : public Keyword {
public:
    KeywordWhile() : Keyword(KW_WHILE) {}
};

class KeywordClass : public Keyword {
public:
    KeywordClass() : Keyword(KW_CLASS) {}
};

class KeywordLet : public Keyword {
public:
    KeywordLet() : Keyword(KW_LET) {}
};

}
}
#endif // REJECTED_H
