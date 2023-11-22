
#include <gtest/gtest.h>

#include <kiraz/stmt.h>

#include <kiraz/hw2-lexer.hpp>
#include <kiraz/hw2-parser.hpp>

extern int yydebug;

namespace kiraz {

TEST(hw2, add) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("1 + 2;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    // fmt::print("{}\n", *root); // uncomment to your heart's content

    // structural verification
    auto stmt_l = static_cast<stmt::OpBinary &>(*root).get_left();
    auto stmt_r = static_cast<stmt::OpBinary &>(*root).get_right();

    ASSERT_TRUE(stmt_l);
    ASSERT_TRUE(stmt_r);

    auto &left = static_cast<stmt::Integer &>(*stmt_l);
    auto &right = static_cast<stmt::Integer &>(*stmt_r);

    ASSERT_EQ(left.get_base(), 10);
    ASSERT_EQ(left.get_value(), "1");

    ASSERT_EQ(right.get_base(), 10);
    ASSERT_EQ(right.get_value(), "2");

    // or simply verify the root repr
    ASSERT_EQ(fmt::format("{}", *root), "OP_PLUS(l=Int(10, 1), r=Int(10, 2))");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

TEST(hw2, add_signed) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("1 + -2;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root), "OP_PLUS(l=Int(10, 1), r=Signed(OP_MINUS, Int(10, 2)))");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

TEST(hw2, signed_add) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("-1 + 2;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root), "OP_PLUS(l=Signed(OP_MINUS, Int(10, 1)), r=Int(10, 2))");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

TEST(hw2, add_mul) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("1 + 2 * 3;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "OP_PLUS("
            "l=Int(10, 1), "
            "r=OP_MULT(l=Int(10, 2), r=Int(10, 3))"
            ")");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

TEST(hw2, mul_add) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("1 * 2 + 3;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "OP_PLUS("
            "l=OP_MULT(l=Int(10, 1), r=Int(10, 2)), "
            "r=Int(10, 3)"
            ")");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

TEST(hw2, add__paren_mul) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("1 + (2 * 3);");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "OP_PLUS("
            "l=Int(10, 1), "
            "r=OP_MULT(l=Int(10, 2), r=Int(10, 3))"
            ")");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

TEST(hw2, paren_mul__add) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("(1 * 2) + 3;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "OP_PLUS("
            "l=OP_MULT(l=Int(10, 1), r=Int(10, 2)), "
            "r=Int(10, 3)"
            ")");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

TEST(hw2, mul__paren_add) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("1 * (2 + 3);");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "OP_MULT("
            "l=Int(10, 1), "
            "r=OP_PLUS(l=Int(10, 2), r=Int(10, 3))"
            ")");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

TEST(hw2, paren_add__mul) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("(1 + 2) * 3;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "OP_MULT("
            "l=OP_PLUS(l=Int(10, 1), r=Int(10, 2)), "
            "r=Int(10, 3)"
            ")");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

TEST(hw2, paren_add__mul__paren_add) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("(1 + 2) * (3 + 4);");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "OP_MULT("
            "l=OP_PLUS(l=Int(10, 1), r=Int(10, 2)), "
            "r=OP_PLUS(l=Int(10, 3), r=Int(10, 4))"
            ")");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

TEST(hw2, paren_mul__sub__paren_mul) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("(1 * 2) - (3 * 4);");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "OP_MINUS("
            "l=OP_MULT(l=Int(10, 1), r=Int(10, 2)), "
            "r=OP_MULT(l=Int(10, 3), r=Int(10, 4))"
            ")");

    /* cleanup */
    yy_delete_buffer(buffer);
    Token::clear();
    Stmt::reset_root();
    yydebug = 0;
}

} // namespace kiraz
