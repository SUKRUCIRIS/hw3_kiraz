
#include <gtest/gtest.h>

#include <kiraz/token.h>

#include <kiraz/hw1-lexer.hpp>

namespace kiraz {
TEST(hw1, multi_id_ign_id) {
    // init
    auto buffer = yy_scan_string("test string");

    // perform
    auto tok1 = yylex();
    auto tok2 = yylex();
    auto tok3 = yylex();

    // verify
    ASSERT_EQ(tok1, token::IDENTIFIER);
    ASSERT_EQ(tok2, token::IGNORED);
    ASSERT_EQ(tok3, token::IDENTIFIER);

    // cleanup
    yy_delete_buffer(buffer);
    Token::clear();
}

TEST(hw1, l_integer) {
    // init
    auto buffer = yy_scan_string("123");

    // perform
    auto tok = yylex();

    // verify
    ASSERT_EQ(tok, token::L_INTEGER);
    ASSERT_EQ(Token::all().size(), 1);
    ASSERT_EQ(Token::all().front()->get_id(), tok);
    ASSERT_EQ(static_cast<token::Integer *>(Token::all().front().get())->get_value(), "123");
    ASSERT_EQ(static_cast<token::Integer *>(Token::all().front().get())->get_base(), 10);

    // cleanup
    yy_delete_buffer(buffer);
    Token::clear();
}

TEST(hw1, rejected) {
    // init
    auto buffer = yy_scan_string("`");

    // perform
    auto tok = yylex();

    // verify
    ASSERT_EQ(tok, token::REJECTED);
    ASSERT_EQ(Token::all().size(), 1);
    ASSERT_EQ(Token::all().front()->get_id(), tok);

    // cleanup
    yy_delete_buffer(buffer);
    Token::clear();
}
} // namespace kiraz
