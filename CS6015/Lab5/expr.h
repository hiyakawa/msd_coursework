/**
 * \file expr.h
 * \brief Declarations of methods in Expr and its child classes
 * \author Laura Zhang
 */

#pragma once

#include <string>
#include <ostream>

typedef enum {
    prec_none,
    prec_add,
    prec_mult,
} precedence_t;

class Expr {
public:
    virtual bool  equals(Expr *e) = 0;
    virtual int   interp() = 0;
    virtual bool  has_variable() = 0;
    virtual Expr* subst(std::string parameter, Expr* expr) = 0;
    virtual void  print(std::ostream &ot) = 0;
    virtual void  pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos) = 0;
    void          pretty_print(std::ostream &ot);
    std::string   to_string();
    std::string   pretty_print_to_string();
};

class NumExpr : public Expr {
public:
    int val_;

    NumExpr(int val);
    bool  equals(Expr *e);
    int   interp();
    bool  has_variable();
    Expr* subst(std::string parameter, Expr* expr);
    void  print(std::ostream &ot);

private:
    void  pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos);
};

class AddExpr : public Expr {
public:
    Expr *lhs_;
    Expr *rhs_;

    AddExpr(Expr *lhs, Expr *rhs);
    bool  equals(Expr *e);
    int   interp();
    bool  has_variable();
    Expr* subst(std::string parameter, Expr* expr);
    void  print(std::ostream &ot);

private:
    void  pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos);
};

class MultExpr : public Expr {
public:
    Expr *lhs_;
    Expr *rhs_;

    MultExpr(Expr *lhs, Expr *rhs);
    bool  equals(Expr *e);
    int   interp();
    bool  has_variable();
    Expr* subst(std::string parameter, Expr* expr);
    void  print(std::ostream &ot);

private:
    void  pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos);
};

class VarExpr : public Expr {
public:
    std::string var_;

    VarExpr(std::string var);
    bool  equals(Expr *e);
    int   interp();
    bool  has_variable();
    Expr* subst(std::string parameter, Expr* expr);
    void  print(std::ostream &ot);

private:
    void  pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos);
};

class LetExpr : public Expr {
public:
    std::string var_;
    Expr *rhs_;
    Expr *body_;

    LetExpr(std::string var, Expr* rhs, Expr* body);
    bool  equals(Expr *e);
    int   interp();
    bool  has_variable();
    Expr* subst(std::string parameter, Expr* expr);
    void  print(std::ostream &ot);

private:
    void  pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos);
};