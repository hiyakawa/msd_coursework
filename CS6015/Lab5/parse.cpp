/**
 * \file parse.cpp
 * \brief Definitions of methods to parse input string
 * \author Laura Zhang
 */

#include "parse.h"
#include "expr.h"
#include <sstream>

Expr* parse(std::istream &in) {
    Expr* e = parse_expr(in);
    skip_whitespace(in);

    if (! in.eof()) {
        throw std::runtime_error("invalid input");
    }

    return e;
}

Expr* parse_str(const std::string& s) {
    std::stringstream ss(s);

    return parse(ss);
}

static Expr* parse_expr(std::istream &in) {
    Expr* e = parse_addend(in);
    skip_whitespace(in);

    if (in.peek() == '+') {
        consume(in, '+');
        Expr* rhs = parse_expr(in);

        return new AddExpr(e, rhs);
    }

    return e;
}

static Expr* parse_addend(std::istream &in) {
    Expr* e = parse_multicand(in);
    skip_whitespace(in);

    if (in.peek() == '*') {
        consume(in, '*');
        Expr* rhs = parse_addend(in);

        return new MultExpr(e, rhs);
    }

    return e;
}

static Expr* parse_multicand(std::istream &in) {
    Expr* e = parse_inner(in);
    skip_whitespace(in);

    while (in.peek() == '(') {
        consume(in, '(');
        skip_whitespace(in);

        if (in.get() != ')') {
            throw std::runtime_error("bad input");
        }
    }

    return e;
}

static Expr* parse_inner(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();

    if (c == '-' || isdigit(c)) {
        return parse_num(in);
    }
    if (c == '(') {
        consume(in, '(');
        Expr* e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();

        if (c != ')') {
            throw std::runtime_error("bad input");
        }

        return e;
    }
    if (isalpha(c)) {
        return parse_var(in);
    }
    if (c == '_') {
        consume(in, '_');
        std::string keyword = parse_keyword(in);

        if (keyword == "let") {
            return parse_let(in);
        }
        else {
            throw std::runtime_error("bad input");
        }
    }
    else {
        consume(in, c);
        throw std::runtime_error("bad input");
    }
}

static NumExpr* parse_num(std::istream &in) {
    int n = 0;
    bool negative = false;

    if (in.peek() == '-') {
        negative = true;
        consume(in, '-');

        if (! isdigit(in.peek())) {
            throw std::runtime_error("invalid input");
        }
    }

    while (true) {
        int c = in.peek();
        if (isdigit(c)) {
            consume(in, c);
            n = 10 * n + (c - '0');
        }
        else {
            break;
        }
    }

    if (negative) {
        n = -n;
    }

    return new NumExpr(n);
}

static VarExpr* parse_var(std::istream &in) {
    std::string s = "";

    while (true) {
        int c = in.peek();

        if (isalpha(c)) {
            consume(in, c);
            s += c;
        }
        else {
            break;
        }
    }

    return new VarExpr(s);
}

static LetExpr* parse_let(std::istream &in) {
    skip_whitespace(in);
    std::string lhs = parse_var(in)->var_;
    skip_whitespace(in);

    if (in.peek() == '=') {
        consume(in, '=');
    }
    else {
        throw std::runtime_error("bad input");
    }

    Expr* rhs = parse_expr(in);
    skip_whitespace(in);

    if (parse_keyword(in) != "_in") {
        throw std::runtime_error("bad input");
    }

    Expr* body = parse_expr(in);

    return new LetExpr(lhs, rhs, body);
}

static std::string parse_keyword(std::istream &in) {
    std::string s = "";

    while (true) {
        int c = in.peek();

        if (isalpha(c) || c == '_') {
            consume(in, c);
            s += c;
        }
        else {
            break;
        }
    }

    return s;
}

static void skip_whitespace(std::istream &in) {
    while(true) {
        int c = in.peek();

        if (! isspace(c)) {
            break;
        }

        consume(in, c);
    }
}

static void consume(std::istream &in, int expect) {
    int c = in.get();
    
    if (c != expect) {
        throw std::runtime_error("unexpected consume");
    }
}
