
#include <gtest/gtest.h>

#include <kiraz/stmt.h>

#include <kiraz/hw3-lexer.hpp>
#include <kiraz/hw3-parser.hpp>

extern int yydebug;

namespace kiraz {

void test_clear(YY_BUFFER_STATE buffer) {
    yy_delete_buffer(buffer);
    Token::clear();
    yydebug = 0;
    kiraz::colno = 0;
    // I reset the root until the count is 0
    while (Stmt::get_root().use_count() != 0) {
        Stmt::reset_root();
    }
}

TEST(hw3, add) {
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
    test_clear(buffer);
}

TEST(hw3, add_signed) {
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
    test_clear(buffer);
}

TEST(hw3, signed_add) {
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
    test_clear(buffer);
}

TEST(hw3, add_mul) {
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
    test_clear(buffer);
}

TEST(hw3, mul_add) {
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
    test_clear(buffer);
}

TEST(hw3, add__paren_mul) {
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
    test_clear(buffer);
}

TEST(hw3, paren_mul__add) {
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
    test_clear(buffer);
}

TEST(hw3, mul__paren_add) {
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
    test_clear(buffer);
}

TEST(hw3, paren_add__mul) {
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
    test_clear(buffer);
}

TEST(hw3, neg_paren_add__mul) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("-(1 + 2) * 3;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "Signed(OP_MINUS, "
            "OP_MULT("
            "l=OP_PLUS(l=Int(10, 1), r=Int(10, 2)), "
            "r=Int(10, 3)"
            ")"
            ")");

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, paren_add__mul__paren_add) {
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
    test_clear(buffer);
}

TEST(hw3, paren_mul__sub__paren_mul) {
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
    test_clear(buffer);
}

TEST(hw3, paren_mul__sub__paren_mul__with_iden) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("(a * b) - (c * d);");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "OP_MINUS(l=OP_MULT(l=Id(a), r=Id(b)), r=OP_MULT(l=Id(c), r=Id(d)))");

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, assignment) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("a = 5;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root), "OP_ASSIGN(l=Id(a), r=Int(10, 5))");

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, assignment_iden) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("a = b + 5;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root), "OP_ASSIGN(l=Id(a), r=OP_PLUS(l=Id(b), r=Int(10, 5)))");

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, assignment_iden_neg) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("a = -(b / 5);");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "OP_ASSIGN(l=Id(a), r=Signed(OP_MINUS, OP_DIVF(l=Id(b), r=Int(10, 5))))");

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, let_with_val) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("let a = 5;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root), "Let(n=Id(a), i=Int(10, 5))");

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, let_with_type) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("let a : Int64;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root), "Let(n=Id(a), t=Id(Int64))");

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, let_with_type_val) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("let a : Int64 = 5;");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root), "Let(n=Id(a), t=Id(Int64), i=Int(10, 5))");

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, let_invalid) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("let a;");

    /* perform */
    yyparse();
    yydebug = 0;

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_FALSE(root);

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, let_with_value_invalid) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("let a = b;");

    /* perform */
    yyparse();
    yydebug = 0;

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_FALSE(root);

    /* cleanup */
    test_clear(buffer);
}

#if 0
TEST(hw3, let_with_stmt_invalid) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("let a = 2 * 3;");

    /* perform */
    yyparse();
    yydebug = 0;

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_FALSE(root);

    /* cleanup */
    test_clear(buffer);
}
#endif

TEST(hw3, func) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("func f() : T {};");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root), "Func(n=Id(f), a=[], r=Id(T), s=[])");

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, func_args) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("func f(a1 : A1) : T {};");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "Func(n=Id(f), a=FuncArgs([Arg(n=Id(a1), t=Id(A1))]), r=Id(T), s=[])");

    /* cleanup */
    test_clear(buffer);
}

TEST(hw3, func_args_stmts) {
    /* init */
    // yydebug = 1; // uncomment to your heart's content
    auto buffer = yy_scan_string("func f(a1 : A1) : T { let v : A1 = 5; };");

    /* perform */
    yyparse();

    /* verify */
    auto root = Stmt::get_root();
    ASSERT_TRUE(root);
    ASSERT_EQ(fmt::format("{}", *root),
            "Func("
            "n=Id(f), "
            "a=FuncArgs([Arg(n=Id(a1), t=Id(A1))]), "
            "r=Id(T), "
            "s=StmtList([Let(n=Id(v), t=Id(A1), i=Int(10, 5))])"
            ")");

    /* cleanup */
    test_clear(buffer);
}

} // namespace kiraz
