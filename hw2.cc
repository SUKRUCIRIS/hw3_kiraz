
#include <kiraz/stmt.h>

#include <kiraz/hw2-lexer.hpp>
#include <kiraz/hw2-parser.hpp>

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fmt::print("Usage: {} <input_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "rb");
    if (! yyin) {
        perror(argv[1]);
        return 2;
    }

    yyparse();

    if (auto root = kiraz::Stmt::get_root()) {
        fmt::print("{}\n", *root);
    }

    return 0;
}
