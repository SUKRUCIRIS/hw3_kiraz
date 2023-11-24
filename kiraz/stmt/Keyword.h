#ifndef KIRAZ_STMT_KEYWORD_H
#define KIRAZ_STMT_KEYWORD_H

#include <kiraz/stmt/Base.h>

namespace kiraz {
namespace stmt {

class KeyLet : public Stmt {
private:
    Stmt::Ptr m_type = nullptr;
    Stmt::Ptr m_iden = nullptr;
    Stmt::Ptr m_init = nullptr;

public:
    KeyLet(Stmt::Ptr type, Stmt::Ptr iden, Stmt::Ptr init)
            : m_type(type), m_iden(iden), m_init(init) {}
    std::string get_repr() const override {
        if (m_type == nullptr) {
            return fmt::format("Let(n={}, i={})", m_iden->get_repr(), m_init->get_repr());
        }
        else if (m_init == nullptr) {
            return fmt::format("Let(n={}, t={})", m_iden->get_repr(), m_type->get_repr());
        }
        else {
            return fmt::format("Let(n={}, t={}, i={})", m_iden->get_repr(), m_type->get_repr(),
                    m_init->get_repr());
        }
    }
};

class funcargs : public Stmt {
private:
    std::vector<Stmt::Ptr> m_iden;
    std::vector<Stmt::Ptr> m_type;

public:
    funcargs(Stmt::Ptr iden, Stmt::Ptr type) {
        m_iden.push_back(iden);
        m_type.push_back(type);
    }
    funcargs(funcargs *x) { *this = *x; }
    funcargs *push_iden(Stmt::Ptr iden, Stmt::Ptr type) {
        m_iden.push_back(iden);
        m_type.push_back(type);
        return this;
    }
    std::string get_repr() const override {
        std::string res = "FuncArgs([";
        for (int i = 0; i < m_iden.size(); i++) {
            res += "Arg(n=" + m_iden[i]->get_repr() + ", t=" + m_type[i]->get_repr() + ")";
            if (i != m_iden.size() - 1) {
                res += ", ";
            }
        }
        res += "])";
        return res;
    }
};

class lines : public Stmt {
private:
    std::vector<Stmt::Ptr> v_line;

public:
    lines(Stmt::Ptr line) { v_line.push_back(line); }
    lines(lines *x) { *this = *x; }
    lines *push_line(Stmt::Ptr line) {
        v_line.push_back(line);
        return this;
    }
    std::string get_repr() const override {
        std::string res = "StmtList([";
        for (int i = 0; i < v_line.size(); i++) {
            res += v_line[i]->get_repr();
            if (i != v_line.size() - 1) {
                res += ", ";
            }
        }
        res += "])";
        return res;
    }
};

class KeyFunc : public Stmt {
private:
    Stmt::Ptr n = nullptr, a = nullptr, r = nullptr, s = nullptr;

public:
    KeyFunc(Stmt::Ptr name, Stmt::Ptr args, Stmt::Ptr ret, Stmt::Ptr lines)
            : n(name), a(args), r(ret), s(lines) {}
    std::string get_repr() const override {
        std::string res = "Func(n=";
        res += n->get_repr();
        res += ", a=";
        if (a == nullptr) {
            res += "[]";
        }
        else {
            res += a->get_repr();
        }
        res += ", r=" + r->get_repr();
        res += ", s=";
        if (s == nullptr) {
            res += "[]";
        }
        else {
            res += s->get_repr();
        }
        res += ")";
        return res;
    }
};

} // namespace stmt
} // namespace kiraz

#endif
